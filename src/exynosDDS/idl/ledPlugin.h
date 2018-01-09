

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from led.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ledPlugin_51520685_h
#define ledPlugin_51520685_h

#include "led.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#define IndicatorPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define IndicatorPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define IndicatorPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define IndicatorPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define IndicatorPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern Indicator*
IndicatorPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern Indicator*
IndicatorPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern Indicator*
IndicatorPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
IndicatorPluginSupport_copy_data(
    Indicator *out,
    const Indicator *in);

NDDSUSERDllExport extern void 
IndicatorPluginSupport_destroy_data_w_params(
    Indicator *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
IndicatorPluginSupport_destroy_data_ex(
    Indicator *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
IndicatorPluginSupport_destroy_data(
    Indicator *sample);

NDDSUSERDllExport extern void 
IndicatorPluginSupport_print_data(
    const Indicator *sample,
    const char *desc,
    unsigned int indent);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
IndicatorPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
IndicatorPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
IndicatorPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
IndicatorPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
IndicatorPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    Indicator *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    Indicator *out,
    const Indicator *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const Indicator *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    Indicator *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
IndicatorPlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const Indicator *sample); 

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    Indicator **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
IndicatorPlugin_deserialize_from_cdr_buffer(
    Indicator *sample,
    const char * buffer,
    unsigned int length);    
NDDSUSERDllExport extern DDS_ReturnCode_t
IndicatorPlugin_data_to_string(
    const Indicator *sample,
    char *str,
    DDS_UnsignedLong *str_size, 
    const struct DDS_PrintFormatProperty *property);    

NDDSUSERDllExport extern RTIBool
IndicatorPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
IndicatorPlugin_get_serialized_sample_max_size_ex(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool * overflow,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);    

NDDSUSERDllExport extern unsigned int 
IndicatorPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
IndicatorPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
IndicatorPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const Indicator * sample);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
IndicatorPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
IndicatorPlugin_get_serialized_key_max_size_ex(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool * overflow,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
IndicatorPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const Indicator *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    Indicator * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
IndicatorPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    Indicator ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
IndicatorPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    Indicator *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
IndicatorPlugin_new(void);

NDDSUSERDllExport extern void
IndicatorPlugin_delete(struct PRESTypePlugin *);

#define AutoReadyPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define AutoReadyPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define AutoReadyPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

#define AutoReadyPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define AutoReadyPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern AutoReady*
AutoReadyPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern AutoReady*
AutoReadyPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern AutoReady*
AutoReadyPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
AutoReadyPluginSupport_copy_data(
    AutoReady *out,
    const AutoReady *in);

NDDSUSERDllExport extern void 
AutoReadyPluginSupport_destroy_data_w_params(
    AutoReady *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
AutoReadyPluginSupport_destroy_data_ex(
    AutoReady *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
AutoReadyPluginSupport_destroy_data(
    AutoReady *sample);

NDDSUSERDllExport extern void 
AutoReadyPluginSupport_print_data(
    const AutoReady *sample,
    const char *desc,
    unsigned int indent);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
AutoReadyPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
AutoReadyPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
AutoReadyPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
AutoReadyPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
AutoReadyPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady *out,
    const AutoReady *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const AutoReady *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
AutoReadyPlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const AutoReady *sample); 

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
AutoReadyPlugin_deserialize_from_cdr_buffer(
    AutoReady *sample,
    const char * buffer,
    unsigned int length);    
NDDSUSERDllExport extern DDS_ReturnCode_t
AutoReadyPlugin_data_to_string(
    const AutoReady *sample,
    char *str,
    DDS_UnsignedLong *str_size, 
    const struct DDS_PrintFormatProperty *property);    

NDDSUSERDllExport extern RTIBool
AutoReadyPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
AutoReadyPlugin_get_serialized_sample_max_size_ex(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool * overflow,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);    

NDDSUSERDllExport extern unsigned int 
AutoReadyPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
AutoReadyPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
AutoReadyPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const AutoReady * sample);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
AutoReadyPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
AutoReadyPlugin_get_serialized_key_max_size_ex(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool * overflow,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
AutoReadyPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const AutoReady *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
AutoReadyPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
AutoReadyPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    AutoReady *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
AutoReadyPlugin_new(void);

NDDSUSERDllExport extern void
AutoReadyPlugin_delete(struct PRESTypePlugin *);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ledPlugin_51520685_h */

