set (CMAKE_CXX_STANDARD 11)
project (libblinkstick)

#option(BUILD_DOC "Build documentation" ON)

if(TARGET_ARCHITECTURE STREQUAL "arm")
  set(HIDAPI_INCLUDE_DIRS ${ARM_HIDAPI_INCLUDE_DIRS}/include/hidapi)
else()
  set(HIDAPI_INCLUDE_DIRS /usr/include/hidapi)
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(HIDAPI REQUIRED hidapi-libusb)

include_directories(PUBLIC ${HIDAPI_INCLUDE_DIRS})

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/seatest ${HIDAPI_INCLUDE_DIRS})

add_subdirectory(src)
