set(NDDSHOME /opt/rti/)

set(PATH ${PATH}:${NDDSHOME}/bin)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  set(ARCH "armv8Linux4.4gcc5.4.0")
  set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
  include_directories(${ARM_HIDAPI_INCLUDE_DIRS}/include/)
  include_directories(${ARM_DDS}/include/)
else()
  set(ARCH "x64Linux3gcc5.4.0")
  set(CMAKE_CXX_COMPILER g++)
endif()

include_directories(${COMMON_INCLUDES})
include_directories(${PROJECT_SOURCE_DIR}/idl)

execute_process(COMMAND /opt/rti/bin/rtiddsgen -example ${ARCH} -language C++ ${PROJECT_SOURCE_DIR}/idl/button.idl)
add_definitions(-DRTI_UNIX -DRTI_LINUX -DRTI_64BIT)

# LIBRARY
ADD_LIBRARY(libusb SHARED IMPORTED)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  SET_TARGET_PROPERTIES(libusb PROPERTIES IMPORTED_LOCATION ${ARM_DDS}/lib/libusb-1.0.so)
endif()

add_library(libblinkstick libblinkstick.cpp)
if(TARGET_ARCHITECTURE STREQUAL "arm")
  ADD_LIBRARY(hidapi-libusb STATIC IMPORTED)
  SET_TARGET_PROPERTIES(hidapi-libusb PROPERTIES IMPORTED_LOCATION ${ARM_DDS}/lib/libhidapi-libusb.a)
  target_link_libraries(libblinkstick hidapi-libusb libusb)
else()
  target_link_libraries(libblinkstick ${HIDAPI_LIBRARIES})
endif()
set_target_properties(libblinkstick PROPERTIES OUTPUT_NAME blinkstick)

# CLI TOOL
add_executable(blinkstick blinkstick.cpp ${PROJECT_SOURCE_DIR}/idl/button.cxx ${PROJECT_SOURCE_DIR}/idl/buttonSupport.cxx ${PROJECT_SOURCE_DIR}/idl/buttonPlugin.cxx)

include_directories(${NDDSHOME}/include )
include_directories(${NDDSHOME}/include/ndds)

link_directories("${NDDSHOME}/lib/${ARCH}")


set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

ADD_LIBRARY(nddscppz STATIC IMPORTED)
SET_TARGET_PROPERTIES(nddscppz PROPERTIES IMPORTED_LOCATION ${NDDSHOME}/lib/${ARCH}/libnddscppz.a)

ADD_LIBRARY(nddscz STATIC IMPORTED)
SET_TARGET_PROPERTIES(nddscz PROPERTIES IMPORTED_LOCATION ${NDDSHOME}/lib/${ARCH}/libnddscz.a)

ADD_LIBRARY(nddscorez STATIC IMPORTED)
SET_TARGET_PROPERTIES(nddscorez PROPERTIES IMPORTED_LOCATION ${NDDSHOME}/lib/${ARCH}/libnddscorez.a)

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

target_link_libraries(blinkstick libblinkstick nddscppz nddscz nddscorez pthread libudev libdbus dl nsl m rt)

install(TARGETS blinkstick libblinkstick
        RUNTIME DESTINATION "${EXECUTABLE_OUTPUT_PATH}"
        ARCHIVE DESTINATION "${EXECUTABLE_OUTPUT_PATH}"
        LIBRARY DESTINATION "${LIBRARY_OUTPUT_PATH}")

file(COPY libblinkstick.h DESTINATION "${INSTALL_INCLUDE_PATH}")
