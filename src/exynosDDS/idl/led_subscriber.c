#include <stdio.h>
#include <stdlib.h>
#include "ndds/ndds_c.h"
#include "led.h"
#include "ledSupport.h"
#include "libblinkstick.h"

#define SLEEP 1000
#define COLORCOUNT 5
#define LEDSTRIPS 2

typedef enum names { CONSOLE, GLOVEBOX } names_;
typedef enum colors { NONE, GREEN, RED, BLUE, BLUE_FLASH } colors_;

blinkstick_device *list[LEDSTRIPS];
colors_ CURRENTCOLOR[LEDSTRIPS];
static rgb_color *colorIndex[COLORCOUNT];

static char* colorPalette[] = { \
                    "NONE", \
                    "GREEN", \
                    "RED_FLASH", \
                    "BLUE", \
                    "BLUE_FLASH"    // YELLOW
};

colors_ getIndex(char *color) {
    int i;
    for (i = 0; i < COLORCOUNT; i++) {
        if (!strcmp(color, colorPalette[i]))
            return i;
    }

    printf("Error Parsing Colors, received: %s\n", color);
    exit -1;
}

uint8_t setup () {
    colorIndex[RED] = rgb_color_factory(255, 0, 0);;
    colorIndex[GREEN] = rgb_color_factory(0, 255, 0);
    colorIndex[BLUE] = rgb_color_factory(0, 0, 255);
    colorIndex[BLUE_FLASH] = rgb_color_factory(255, 255, 0);
    colorIndex[NONE] = rgb_color_factory(0,0,0);

    int count = find_all_blinkstick(list);
    return count;
}

void setLED(char* color, names_ LEDID) {
    int i;

    colors_ index = getIndex(color);
    rgb_color *rgbColor = colorIndex[index];

    for (i = 0; i < 8; i++) {
        set_color(i, rgbColor, list[LEDID]);
        usleep(SLEEP);
    }
    CURRENTCOLOR[LEDID] = index;
}

void cleanup () {
    int i;
    for (i = 0; i < COLORCOUNT; i++) {
        if (colorIndex[i])
            destroy_color(colorIndex[i]);
    }
}

void led_messageListener_on_requested_deadline_missed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedDeadlineMissedStatus *status){}

void led_messageListener_on_requested_incompatible_qos(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedIncompatibleQosStatus *status){}

void led_messageListener_on_sample_rejected(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleRejectedStatus *status){}

void led_messageListener_on_liveliness_changed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_LivelinessChangedStatus *status){}

void led_messageListener_on_sample_lost(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleLostStatus *status){}

void led_messageListener_on_subscription_matched(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SubscriptionMatchedStatus *status){}


void led_messageListener_on_data_available_CONSOLE(
    void* listener_data,
    DDS_DataReader* reader) {
    IndicatorDataReader *Indicator_reader = NULL;
    struct IndicatorSeq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t retcode;
    struct DDS_SampleInfo info;
    int i;

    Indicator_reader = IndicatorDataReader_narrow(reader);
    if (Indicator_reader == NULL) {
        fprintf(stderr, "DataReader narrow error\n");
        return;
    }

    Indicator instance;
    retcode = IndicatorDataReader_read_next_sample (Indicator_reader, &instance, &info);

    if(retcode == DDS_RETCODE_NO_DATA) {
	return;
    } else if( retcode !=DDS_RETCODE_OK) {
        printf("No Data Available\n");
	return;
    }

    if(info.valid_data) {
        if (strcmp(instance.indicator_color, colorPalette[CURRENTCOLOR[CONSOLE]]))
            setLED(instance.indicator_color, CONSOLE);
    }
    return;
}


void led_messageListener_on_data_available_GLOVEBOX(
    void* listener_data,
    DDS_DataReader* reader)
{
    AutoReadyDataReader *AutoReady_reader = NULL;
    struct AutoReadySeq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t retcode;
    struct DDS_SampleInfo info;
    int i;

    AutoReady_reader = AutoReadyDataReader_narrow(reader);
    if (AutoReady_reader == NULL) {
        fprintf(stderr, "DataReader narrow error\n");
        return;
    }

    AutoReady instance;
    retcode = AutoReadyDataReader_take_next_sample (AutoReady_reader, &instance, &info);

    if(retcode == DDS_RETCODE_NO_DATA) {
	return;
    } else if( retcode !=DDS_RETCODE_OK) {
        printf("No Data Available\n");
	return;
    }

    if(info.valid_data) {
        if (instance.auto_ready != CURRENTCOLOR[GLOVEBOX])
            setLED(colorPalette[instance.auto_ready], GLOVEBOX);
    }
    return;
}

/* Delete all entities */
static int subscriber_shutdown(
    DDS_DomainParticipant *participant)
{
    DDS_ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = DDS_DomainParticipant_delete_contained_entities(participant);
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = DDS_DomainParticipantFactory_delete_participant(
            DDS_TheParticipantFactory, participant);
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_participant error %d\n", retcode);
            status = -1;
        }
    }
    cleanup();
    return status;
}

static int subscriber_main(int domainId, int sample_count)
{
    DDS_DomainParticipant *participant = NULL;
    DDS_Subscriber *subscriber = NULL;
    DDS_Topic *topic = NULL;
    struct DDS_DataReaderListener reader_listener =
    DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader = NULL;
    DDS_ReturnCode_t retcode;
    const char *type_name = NULL;
    int count = 0;

    DDS_DomainParticipant *participant1 = NULL;
    DDS_Subscriber *subscriber1 = NULL;
    DDS_Topic *topic1 = NULL;
    struct DDS_DataReaderListener reader_listener1 =
    DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader1 = NULL;
    DDS_ReturnCode_t retcode1;
    const char *type_name1 = NULL;
    int count1 = 0;

    /* To customize participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    participant = DDS_DomainParticipantFactory_create_participant(
        DDS_TheParticipantFactory, domainId, &DDS_PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        fprintf(stderr, "create_participant error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    participant1 = DDS_DomainParticipantFactory_create_participant(
        DDS_TheParticipantFactory, domainId, &DDS_PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant1 == NULL) {
        fprintf(stderr, "create_participant1 error\n");
        subscriber_shutdown(participant1);
        return -1;
    }

    /* To customize subscriber QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    subscriber = DDS_DomainParticipant_create_subscriber(
        participant, &DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        fprintf(stderr, "create_subscriber error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    subscriber1 = DDS_DomainParticipant_create_subscriber(
        participant1, &DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (subscriber1 == NULL) {
        fprintf(stderr, "create_subscriber1 error\n");
        subscriber_shutdown(participant1);
        return -1;
    }

    /* Register the type before creating the topic */
    type_name = IndicatorTypeSupport_get_type_name();
    retcode = IndicatorTypeSupport_register_type(participant, type_name);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "Indicator register_type error %d\n", retcode);
        subscriber_shutdown(participant);
        return -1;
    }

    type_name1 = AutoReadyTypeSupport_get_type_name();
    retcode1 = AutoReadyTypeSupport_register_type(participant1, type_name1);
    if (retcode1 != DDS_RETCODE_OK) {
        fprintf(stderr, "AutoReady register_type error1 %d\n", retcode1);
        subscriber_shutdown(participant1);
        return -1;
    }

    /* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = DDS_DomainParticipant_create_topic(
        participant, "ClusterLED",
        type_name, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        fprintf(stderr, "create_topic - LED error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    topic1 = DDS_DomainParticipant_create_topic(
        participant1, "BoxLED",
        type_name1, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic1 == NULL) {
        fprintf(stderr, "create_topic auto_ready error\n");
        subscriber_shutdown(participant1);
        return -1;
    }

    /* Set up a data reader listener */
    reader_listener.on_requested_deadline_missed  =
    led_messageListener_on_requested_deadline_missed;
    reader_listener.on_requested_incompatible_qos =
    led_messageListener_on_requested_incompatible_qos;
    reader_listener.on_sample_rejected =
    led_messageListener_on_sample_rejected;
    reader_listener.on_liveliness_changed =
    led_messageListener_on_liveliness_changed;
    reader_listener.on_sample_lost =
    led_messageListener_on_sample_lost;
    reader_listener.on_subscription_matched =
    led_messageListener_on_subscription_matched;
    reader_listener.on_data_available =
    led_messageListener_on_data_available_CONSOLE;

    /* Set up a data reader listener */
    reader_listener1.on_requested_deadline_missed  =
    led_messageListener_on_requested_deadline_missed;
    reader_listener1.on_requested_incompatible_qos =
    led_messageListener_on_requested_incompatible_qos;
    reader_listener1.on_sample_rejected =
    led_messageListener_on_sample_rejected;
    reader_listener1.on_liveliness_changed =
    led_messageListener_on_liveliness_changed;
    reader_listener1.on_sample_lost =
    led_messageListener_on_sample_lost;
    reader_listener1.on_subscription_matched =
    led_messageListener_on_subscription_matched;
    reader_listener1.on_data_available =
    led_messageListener_on_data_available_GLOVEBOX;


    /* To customize data reader QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    reader = DDS_Subscriber_create_datareader(
        subscriber, DDS_Topic_as_topicdescription(topic),
        &DDS_DATAREADER_QOS_DEFAULT, &reader_listener, DDS_STATUS_MASK_ALL);
    if (reader == NULL) {
        fprintf(stderr, "create_datareader error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    reader1 = DDS_Subscriber_create_datareader(
        subscriber1, DDS_Topic_as_topicdescription(topic1),
        &DDS_DATAREADER_QOS_DEFAULT, &reader_listener1, DDS_STATUS_MASK_ALL);
    if (reader1 == NULL) {
        fprintf(stderr, "create_datareader error\n");
        subscriber_shutdown(participant1);
        return -1;
    }

    /* Main loop */
    while (true) {
        sleep(1);
    }

    /* Cleanup and delete all entities */ 
    subscriber_shutdown(participant);
    subscriber_shutdown(participant1);
    return;
}

int main(int argc, char *argv[])
{
    int domainId = 0;
    int sample_count = 0; /* infinite loop */

    if (argc >= 2) {
        domainId = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    if (setup() < LEDSTRIPS) {
        printf("LED's NOT CONNECTED, EXITING !\n");
        return -1;
    }

    setLED(colorPalette[NONE], GLOVEBOX);
    setLED(colorPalette[BLUE], CONSOLE);

    return subscriber_main(domainId, sample_count);
}

