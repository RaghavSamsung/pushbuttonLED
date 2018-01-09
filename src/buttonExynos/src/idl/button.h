

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from button.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef button_357416480_h
#define button_357416480_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern const char *CarStateTYPENAME;

typedef struct CarState {

    DDS_Boolean   buttonState ;

} CarState ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* CarState_get_typecode(void); /* Type code */

DDS_SEQUENCE(CarStateSeq, CarState);

NDDSUSERDllExport
RTIBool CarState_initialize(
    CarState* self);

NDDSUSERDllExport
RTIBool CarState_initialize_ex(
    CarState* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool CarState_initialize_w_params(
    CarState* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void CarState_finalize(
    CarState* self);

NDDSUSERDllExport
void CarState_finalize_ex(
    CarState* self,RTIBool deletePointers);

NDDSUSERDllExport
void CarState_finalize_w_params(
    CarState* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void CarState_finalize_optional_members(
    CarState* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool CarState_copy(
    CarState* dst,
    const CarState* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* button */

