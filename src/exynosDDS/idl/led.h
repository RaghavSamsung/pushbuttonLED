

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from led.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef led_51520685_h
#define led_51520685_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern const char *IndicatorTYPENAME;

typedef struct Indicator {

    DDS_Char *   indicator_color ;

} Indicator ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* Indicator_get_typecode(void); /* Type code */

DDS_SEQUENCE(IndicatorSeq, Indicator);

NDDSUSERDllExport
RTIBool Indicator_initialize(
    Indicator* self);

NDDSUSERDllExport
RTIBool Indicator_initialize_ex(
    Indicator* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool Indicator_initialize_w_params(
    Indicator* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void Indicator_finalize(
    Indicator* self);

NDDSUSERDllExport
void Indicator_finalize_ex(
    Indicator* self,RTIBool deletePointers);

NDDSUSERDllExport
void Indicator_finalize_w_params(
    Indicator* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void Indicator_finalize_optional_members(
    Indicator* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool Indicator_copy(
    Indicator* dst,
    const Indicator* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

extern const char *AutoReadyTYPENAME;

typedef struct AutoReady {

    DDS_Boolean   auto_ready ;

} AutoReady ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* AutoReady_get_typecode(void); /* Type code */

DDS_SEQUENCE(AutoReadySeq, AutoReady);

NDDSUSERDllExport
RTIBool AutoReady_initialize(
    AutoReady* self);

NDDSUSERDllExport
RTIBool AutoReady_initialize_ex(
    AutoReady* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool AutoReady_initialize_w_params(
    AutoReady* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void AutoReady_finalize(
    AutoReady* self);

NDDSUSERDllExport
void AutoReady_finalize_ex(
    AutoReady* self,RTIBool deletePointers);

NDDSUSERDllExport
void AutoReady_finalize_w_params(
    AutoReady* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void AutoReady_finalize_optional_members(
    AutoReady* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool AutoReady_copy(
    AutoReady* dst,
    const AutoReady* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* led */

