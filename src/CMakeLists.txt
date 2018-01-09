cmake_minimum_required(VERSION 3.1)

SET(TARGET_ARCHITECTURE "x86" CACHE STRING "Default to x86")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
set(INSTALL_INCLUDE_PATH "${PROJECT_BINARY_DIR}/include")
set(INSTALL_PKGCONFIG_PATH "${PROJECT_BINARY_DIR}/pkgconfig")

set(ARM_DDS ${PROJECT_SOURCE_DIR}/exynosDDS/)
set(ARM_Phidget ${PROJECT_SOURCE_DIR}/phidget/)
set(ARM_HIDAPI_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/hidapi/out/)

add_subdirectory(buttonExynos)
add_subdirectory(libblinkstick)
