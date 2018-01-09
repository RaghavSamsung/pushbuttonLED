# Project's name

project(exynosdds)

set(NDDSHOME /opt/rti/)

set(PATH ${PATH}:${NDDSHOME}/bin)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  set(ARCH "armv8Linux4.4gcc5.4.0")
  set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
else()
  set(ARCH "x64Linux3gcc5.4.0")
  set(CMAKE_C_COMPILER gcc)
endif()

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/idl)
include_directories(${PROJECT_SOURCE_DIR}/phidget/include)
link_directories(${PROJECT_SOURCE_DIR}/phidget/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

execute_process(COMMAND /opt/rti/bin/rtiddsgen -example ${ARCH} -language C ${PROJECT_SOURCE_DIR}/idl/button.idl)

add_definitions(-O2)
add_definitions(-DRTI_UNIX -DRTI_LINUX -DRTI_64BIT)

add_executable(buttonpub ${PROJECT_SOURCE_DIR}/buttonpub.c ${PROJECT_SOURCE_DIR}/idl/button.c ${PROJECT_SOURCE_DIR}/idl/buttonSupport.c ${PROJECT_SOURCE_DIR}/idl/buttonPlugin.c)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${NDDSHOME}/include )
include_directories(${NDDSHOME}/include/ndds)

link_directories("${NDDSHOME}/lib/${ARCH}/")
if(TARGET_ARCHITECTURE STREQUAL "arm")
  link_directories("${ARM_DDS}/lib/")
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

ADD_LIBRARY(nddscz STATIC IMPORTED)
SET_TARGET_PROPERTIES(nddscz PROPERTIES IMPORTED_LOCATION ${NDDSHOME}/lib/${ARCH}/libnddscz.a)

ADD_LIBRARY(nddscorez STATIC IMPORTED)
SET_TARGET_PROPERTIES(nddscorez PROPERTIES IMPORTED_LOCATION ${NDDSHOME}/lib/${ARCH}/libnddscorez.a)

add_library(phidget22 STATIC IMPORTED)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  set_target_properties(phidget22 PROPERTIES IMPORTED_LOCATION ${ARM_Phidget}/lib/libphidget22.a)
else()
  set_target_properties(phidget22 PROPERTIES IMPORTED_LOCATION /usr/local/lib/libphidget22.a)
endif()

ADD_LIBRARY(libusb STATIC IMPORTED)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  SET_TARGET_PROPERTIES(libusb PROPERTIES IMPORTED_LOCATION ${ARM_DDS}/lib/libusb-1.0.a)
else()
  SET_TARGET_PROPERTIES(libusb PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libusb-1.0.a)
endif()

ADD_LIBRARY(libudev SHARED IMPORTED)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  SET_TARGET_PROPERTIES(libudev PROPERTIES IMPORTED_LOCATION ${ARM_DDS}/lib/libudev.so.1)
else()
  SET_TARGET_PROPERTIES(libudev PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libudev.so)
endif()

ADD_LIBRARY(libdbus SHARED IMPORTED)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  SET_TARGET_PROPERTIES(libdbus PROPERTIES IMPORTED_LOCATION ${ARM_DDS}/lib/libdbus-1.so.3)
else()
  SET_TARGET_PROPERTIES(libdbus PROPERTIES IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libdbus-1.so)
endif()

target_link_libraries(buttonpub nddscz nddscorez phidget22 libusb libudev libdbus dl nsl m rt pthread)
