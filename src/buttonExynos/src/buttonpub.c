#include "ndds/ndds_c.h"
#include "idl/button.h"
#include "idl/buttonSupport.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <phidget22.h>


/* Defines the maximum number of consecutive write errors. */
#define MAX_CONSECUTIVE_WRITE_ERROR         10



static void CCONV ssleep(int);

static void CCONV
onAttachHandler(PhidgetHandle phid, void *ctx) {
	PhidgetReturnCode res;
	int hubPort;
	int channel;
	int serial;

	res = Phidget_getDeviceSerialNumber(phid, &serial);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get device serial number\n");
		return;
	}

	res = Phidget_getChannel(phid, &channel);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get channel number\n");
		return;
	}

	res = Phidget_getHubPort(phid, &hubPort);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get hub port\n");
		hubPort = -1;
	}

	if (hubPort == -1)
		printf("channel %d on device %d attached\n", channel, serial);
	else
		printf("channel %d on device %d hub port %d attached\n", channel, serial, hubPort);
}

static void CCONV
onDetachHandler(PhidgetHandle phid, void *ctx) {
	PhidgetReturnCode res;
	int hubPort;
	int channel;
	int serial;

	res = Phidget_getDeviceSerialNumber(phid, &serial);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get device serial number\n");
		return;
	}

	res = Phidget_getChannel(phid, &channel);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to get channel number\n");
		return;
	}

	res = Phidget_getHubPort(phid, &hubPort);
	if (res != EPHIDGET_OK)
		hubPort = -1;

	if (hubPort != -1)
		printf("channel %d on device %d detached\n", channel, serial);
	else
		printf("channel %d on device %d hub port %d detached\n", channel, hubPort, serial);
}

static void CCONV
errorHandler(PhidgetHandle phid, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {

	fprintf(stderr, "Error: %s (%d)\n", errorString, errorCode);
}


static void CCONV
onStateChangeHandler(PhidgetDigitalInputHandle ch, void *ctx, int state);

/*
* Creates and initializes the channel.
*/
static PhidgetReturnCode CCONV
initChannel(PhidgetHandle ch) {
	PhidgetReturnCode res;

	res = Phidget_setOnAttachHandler(ch, onAttachHandler, NULL);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to assign on attach handler\n");
		return (res);
	}

	res = Phidget_setOnDetachHandler(ch, onDetachHandler, NULL);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to assign on detach handler\n");
		return (res);
	}

	res = Phidget_setOnErrorHandler(ch, errorHandler, NULL);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to assign on error handler\n");
		return (res);
	}

	/*
	* Please review the Phidget22 channel matching documentation for details on the device
	* and class architecture of Phidget22, and how channels are matched to device features.
	*/

	/*
	* Specifies the serial number of the device to attach to.
	* For VINT devices, this is the hub serial number.
	*
	* The default is any device.
	*/
	// Phidget_setDeviceSerialNumber(ch, <YOUR DEVICE SERIAL NUMBER>); 

	/*
	* For VINT devices, this specifies the port the VINT device must be plugged into.
	*
	* The default is any port.
	*/
	// Phidget_setHubPort(ch, 0);

	/*
	* Specifies that the channel should only match a VINT hub port.
	* The only valid channel id is 0.
	*
	* The default is 0 (false), meaning VINT hub ports will never match
	*/
	// Phidget_setIsHubPortDevice(ch, 1);

	/*
	* Specifies which channel to attach to.  It is important that thechannel of
	* the device is the same class as the channel that is being opened.
	*
	* The default is any channel.
	*/
	// Phidget_setChannel(ch, 0);

	/*
	* In order to attach to a network Phidget, the program must connect to a Phidget22 Network Server.
	* In a normal environment this can be done automatically by enabling server discovery, which
	* will cause the client to discovery and connect to available servers.
	*
	* To force the channel to only match a network Phidget, set remote to 1.
	*/
	// PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICE);
	// Phidget_setIsRemote(ch, 1);

	return (EPHIDGET_OK);
}

	DDS_DomainParticipant * participant = NULL;
	DDS_Topic *             topic = NULL;

	DDS_Publisher *publisher             = NULL;
	DDS_DataWriter *data_writer          = NULL;
	CarStateDataWriter *hello_writer   = NULL;
	CarState *instance                 = NULL;
	DDS_Octet * payload_buffer           = NULL;
	DDS_Boolean return_value             = DDS_BOOLEAN_FALSE;
	DDS_Long i;
	DDS_ReturnCode_t rc;

	PhidgetDigitalInputHandle ch;
	PhidgetReturnCode res;

static int global_state=0;
int prev_state = -1;

int main() {

	const char *errs;

	/*
	* Enable logging to stdout
	*/
	//PhidgetLog_enable(PHIDGET_LOG_INFO, NULL);

	res = PhidgetDigitalInput_create(&ch);
	if (res != EPHIDGET_OK) {
		fprintf(stderr, "failed to create digital input channel\n");
		exit(1);
	}

	res = initChannel((PhidgetHandle)ch);
	if (res != EPHIDGET_OK) {
		Phidget_getErrorDescription(res, &errs);
		fprintf(stderr, "failed to initialize channel:%s\n", errs);
		exit(1);
	}

	res = PhidgetDigitalInput_setOnStateChangeHandler(ch, onStateChangeHandler, NULL);
	if (res != EPHIDGET_OK) {
		Phidget_getErrorDescription(res, &errs);
		fprintf(stderr, "failed to set state change handler: %s\n", errs);
		goto clean_exit;
	}

	/*
	* Open the channel synchronously: waiting a maximum of 5 seconds.
	*/
	res = Phidget_openWaitForAttachment((PhidgetHandle)ch, 5000);
	if (res != EPHIDGET_OK) {
		if (res == EPHIDGET_TIMEOUT) {
			printf("Channel did not attach after 5 seconds: please check that the device is attached\n");
		} else {
			Phidget_getErrorDescription(res, &errs);
			fprintf(stderr, "failed to open channel:%s\n", errs);
		}
		goto clean_exit;
	}

	participant = DDS_DomainParticipantFactory_create_participant(
			DDS_TheParticipantFactory,
			0,                              /* Domain ID */
			&DDS_PARTICIPANT_QOS_DEFAULT,   /* QoS */
			NULL,                           /* Listener */
			DDS_STATUS_MASK_NONE);
	if (participant == NULL) {
		puts("Unable to create domain participant.");
		goto clean_exit;
	}

	rc = CarStateTypeSupport_register_type(
			participant,
			CarStateTypeSupport_get_type_name());
	if (rc != DDS_RETCODE_OK) {
		fprintf(stderr, "! Unable to register '%s' data type: %d\n",
				CarStateTypeSupport_get_type_name(),
				rc);
		goto exitFn;
	}



	/* Create the topic "CarState" for the short type */
	topic = DDS_DomainParticipant_create_topic(
			participant,
			"CarState",                        /* Topic name*/
			CarStateTypeSupport_get_type_name(), /* Type name */
			&DDS_TOPIC_QOS_DEFAULT,                /* Topic QoS */
			NULL,                                  /* Listener  */
			DDS_STATUS_MASK_NONE);
	if (topic == NULL) {
		puts("Unable to create topic.");
		goto clean_exit;
	}





	/* Create the publisher. 
	 * Just like the participant, if you want to customize the publisher QoS,
	 * use DDS_DomainParticipant_get_default_publisher_qos() to 
	 * initialize a local copy of the default QoS, modify them, then
	 * use them in the creation call below instead of 
	 * DDS_PUBLISHER_QOS_DEFAULT.
	 * For more info on publisher API, see:
	 *     $NDDSHOME/doc/html/api_c/group__DDSPublisherModule.html
	 */
	publisher = DDS_DomainParticipant_create_publisher(
			participant,
			&DDS_PUBLISHER_QOS_DEFAULT,
			NULL,           /* listener */
			DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		fprintf(stderr, "! Unable to create DDS Publisher\n");
		goto exitFn;
	}

	/* Creates the DDS Data writer. 
	 * Just like before, if you want to customize the writer QoS,
	 * use DDS_Publisher_get_default_datawriter_qos() to 
	 * initialize a local copy of the default QoS, modify them, then
	 * use them in the creation call below instead of 
	 * DDS_DATAWRITER_QOS_DEFAULT.
	 * For more data writer API info, see:
	 *     $NDDSHOME/doc/html/api_c/group__DDSWriterModule.html
	 */
	data_writer = DDS_Publisher_create_datawriter(
			publisher, 
			topic,
			&DDS_DATAWRITER_QOS_DEFAULT,
			NULL,           /* listener */
			DDS_STATUS_MASK_NONE);
	if (data_writer == NULL) {
		fprintf(stderr, "! Unable to create DDS data writer\n");
		goto exitFn;
	}


	/* The following narrow function should never fail, as it performs 
	 * only a safe cast of the generic data writer into a specific
	 * CarStateDataWriter.
	 * In our case the following cast would do the same job:
	 *     hello_writer = (CarStateDataWriter *)data_writer;
	 */
	hello_writer = CarStateDataWriter_narrow(data_writer);
	if (hello_writer == NULL) {
		fprintf(stderr, "! Unable to narrow data writer into CarStateDataWriter\n");
		goto exitFn;
	}

	/* Everything is ready, start writing the data.
	 * The create data function below simply allocates on the heap an 
	 * instance of the data to send.
	 * Alternatively you can allocate the CarState instance on the
	 * struct, and call the CarState_initialize_ex() function
	 * to initialize the field to a known value.
	 * For more information on the user data type support, see:
	 *     $NDDSHOME/doc/html/api_c/group__DDSUserDataModule.html
	 *
	 * In this case we create an instance of the data on the heap, but
	 * we tell the CarState_create_data_ex to skip allocation of the
	 * inner buffers (in our case, the 'prefix' string).
	 */
	instance = CarStateTypeSupport_create_data();

	if (instance == NULL) {
		fprintf(stderr, "! Unable to create an instance of the data\n");
		fprintf(stderr, "! This problem most likely is caused by "
				"out of memory\n");
		goto exitFn;
	}

	
	do {
		if(global_state !=prev_state) {
		if(global_state)
			instance->buttonState=DDS_BOOLEAN_TRUE;
		else
			instance->buttonState=DDS_BOOLEAN_FALSE;
		printf("Sending Button State\n");
		rc = CarStateDataWriter_write(hello_writer,instance, &DDS_HANDLE_NIL);

	        if (rc != DDS_RETCODE_OK) {
                	fprintf(stderr, "! Write error %d\n", rc);
               	 }
       		prev_state=global_state;
	 }
	
	sleep(0.1);
	}while(1);
	

clean_exit:
exitFn:
	printf("Kaboooooom\n");
	return_value = DDS_BOOLEAN_TRUE;
	Phidget_close((PhidgetHandle)ch);
	PhidgetDigitalInput_delete(&ch);

	return return_value;
}

static void CCONV
onStateChangeHandler(PhidgetDigitalInputHandle ch, void *ctx, int state) {

	printf("State Changed: %d\n", state);
	global_state = state;
}
