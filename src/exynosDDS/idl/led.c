

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from led.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "led.h"

/* ========================================================================= */
const char *IndicatorTYPENAME = "Indicator";

DDS_TypeCode* Indicator_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Indicator_g_tc_indicator_color_string = DDS_INITIALIZE_STRING_TYPECODE((255));
    static DDS_TypeCode_Member Indicator_g_tc_members[1]=
    {

        {
            (char *)"indicator_color",/* Member name */
            {
                0,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Indicator_g_tc =
    {{
            DDS_TK_STRUCT,/* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"Indicator", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            Indicator_g_tc_members, /* Members */
            DDS_VM_NONE  /* Ignored */         
        }}; /* Type code for Indicator*/

    if (is_initialized) {
        return &Indicator_g_tc;
    }

    Indicator_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&Indicator_g_tc_indicator_color_string;

    is_initialized = RTI_TRUE;

    return &Indicator_g_tc;
}

RTIBool Indicator_initialize(
    Indicator* sample) {
    return Indicator_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool Indicator_initialize_ex(
    Indicator* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return Indicator_initialize_w_params(
        sample,&allocParams);

}

RTIBool Indicator_initialize_w_params(
    Indicator* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory){
        sample->indicator_color= DDS_String_alloc ((255));
        if (sample->indicator_color == NULL) {
            return RTI_FALSE;
        }

    } else {
        if (sample->indicator_color!= NULL) { 
            sample->indicator_color[0] = '\0';
        }
    }

    return RTI_TRUE;
}

void Indicator_finalize(
    Indicator* sample)
{

    Indicator_finalize_ex(sample,RTI_TRUE);
}

void Indicator_finalize_ex(
    Indicator* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    Indicator_finalize_w_params(
        sample,&deallocParams);
}

void Indicator_finalize_w_params(
    Indicator* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if (sample->indicator_color != NULL) {
        DDS_String_free(sample->indicator_color);
        sample->indicator_color=NULL;

    }
}

void Indicator_finalize_optional_members(
    Indicator* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool Indicator_copy(
    Indicator* dst,
    const Indicator* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!RTICdrType_copyStringEx (
        &dst->indicator_color, src->indicator_color, 
        (255) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'Indicator' sequence class.
*/
#define T Indicator
#define TSeq IndicatorSeq

#define T_initialize_w_params Indicator_initialize_w_params

#define T_finalize_w_params   Indicator_finalize_w_params
#define T_copy       Indicator_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

/* ========================================================================= */
const char *AutoReadyTYPENAME = "AutoReady";

DDS_TypeCode* AutoReady_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode_Member AutoReady_g_tc_members[1]=
    {

        {
            (char *)"auto_ready",/* Member name */
            {
                0,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode AutoReady_g_tc =
    {{
            DDS_TK_STRUCT,/* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"AutoReady", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            1, /* Number of members */
            AutoReady_g_tc_members, /* Members */
            DDS_VM_NONE  /* Ignored */         
        }}; /* Type code for AutoReady*/

    if (is_initialized) {
        return &AutoReady_g_tc;
    }

    AutoReady_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;

    is_initialized = RTI_TRUE;

    return &AutoReady_g_tc;
}

RTIBool AutoReady_initialize(
    AutoReady* sample) {
    return AutoReady_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool AutoReady_initialize_ex(
    AutoReady* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return AutoReady_initialize_w_params(
        sample,&allocParams);

}

RTIBool AutoReady_initialize_w_params(
    AutoReady* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!RTICdrType_initBoolean(&sample->auto_ready)) {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

void AutoReady_finalize(
    AutoReady* sample)
{

    AutoReady_finalize_ex(sample,RTI_TRUE);
}

void AutoReady_finalize_ex(
    AutoReady* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    AutoReady_finalize_w_params(
        sample,&deallocParams);
}

void AutoReady_finalize_w_params(
    AutoReady* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

}

void AutoReady_finalize_optional_members(
    AutoReady* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool AutoReady_copy(
    AutoReady* dst,
    const AutoReady* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!RTICdrType_copyBoolean (
        &dst->auto_ready, &src->auto_ready)) { 
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'AutoReady' sequence class.
*/
#define T AutoReady
#define TSeq AutoReadySeq

#define T_initialize_w_params AutoReady_initialize_w_params

#define T_finalize_w_params   AutoReady_finalize_w_params
#define T_copy       AutoReady_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

