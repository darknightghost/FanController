# Target.
set (TARGET_NAME        controller)
file (GLOB_RECURSE      ${TARGET_NAME}_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/source/${TARGET_NAME}/*.c"
    )
add_executable ("${TARGET_NAME}"
    "${${TARGET_NAME}_SRC}"
    )

set (DATA_SIZE              128)
set (IDATA_SIZE             128)
set (XDATA_SIZE             1024)
set (CODE_SIZE              17408)

target_compile_options (${TARGET_NAME}  PRIVATE
    "--iram-size"   "${IDATA_SIZE}"
    "--xram-size"   "${XDATA_SIZE}"
    "--code-size"   "${CODE_SIZE}"
    )

target_link_options (${TARGET_NAME}     PRIVATE
    "-mmcs51" 
    "--iram-size" "${IDATA_SIZE}"
    "--xram-size" "${XDATA_SIZE}"
    "--code-size" "${CODE_SIZE}"
    )

add_custom_command (
    DEPENDS     "${TARGET_NAME}"
    OUTPUT      "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.bin"
    COMMAND     "sdobjcopy" "-I" "ihex" "-O" "binary" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.ihx" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.bin"
    )

add_custom_target (
    "${TARGET_NAME}.bin"   ALL
    DEPENDS     "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}.bin"
    )

