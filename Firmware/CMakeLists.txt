cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)

cmake_policy(SET CMP0054 NEW)

list (APPEND    CMAKE_MODULE_PATH       "${CMAKE_CURRENT_SOURCE_DIR}")

# Dependencies.
# sdcc
find_program (SDCC_EXECUTABLE
    sdcc)

if (SDCC_EXECUTABLE)
    message (STATUS "SDCC found - ${SDCC_EXECUTABLE}")

else ()
    message (FATAL_ERROR    "Missing sdcc")

endif ()

# sdas8051
find_program (SDAS8051_EXECUTABLE
    sdas8051)

if (SDAS8051_EXECUTABLE)
    message (STATUS "SDAS8051 found - ${SDAS8051_EXECUTABLE}")

else ()
    message (FATAL_ERROR    "Missing sdas8051")

endif ()

# Python3
find_package (PythonInterp  3
    REQUIRED)

set (CMAKE_TOOLCHAIN_FILE   "")
set ("CMAKE_SYSTEM_NAME"    "Generic")
set ("CMAKE_C_COMPILER"     "${SDCC_EXECUTABLE}")
set ("CMAKE_ASM_COMPILER"   "${SDAS8051_EXECUTABLE}")
set (CMAKE_ASM_COMPILER_ID  "SDAS8051")
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE   "Debug")

endif ()

if (CMAKE_BUILD_TYPE  STREQUAL "Debug")
    add_compile_options (
        "-DDEBUG"
        )
endif ()

set (CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"  CACHE STRING "${CMAKE_BUILD_TYPE}" FORCE)

message (STATUS "Build Type - ${CMAKE_BUILD_TYPE}.")

# Output path.
set (OUTPUT_SUB_DIR "${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/lib/${OUTPUT_SUB_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/lib/${OUTPUT_SUB_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/bin/${OUTPUT_SUB_DIR}")

# Project
project (SmokeController  C ASM)

if (NOT CMAKE_C_COMPILER_ID STREQUAL "SDCC")
    message (FATAL_ERROR        "You should use sdcc to compile the firmware!")

endif ()

# Generic options.
add_compile_options (
    "--std-sdcc11" 
    "--use-non-free" 
    "--fsigned-char" 
    "-mmcs51" 
    "-DBUILD_FIRMWARE"
    )

include_directories (
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

include (power)
include (controller)
