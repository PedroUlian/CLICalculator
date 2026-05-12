set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.15)
project(CLICalculator)

set(CMAKE_C_STANDARD 11)

set(MPDEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mpdecimal-4.0.1/libmpdec)

set(MPDEC_SOURCES
    ${MPDEC_PATH}/basearith.c
    ${MPDEC_PATH}/constants.c
    ${MPDEC_PATH}/context.c
    ${MPDEC_PATH}/convolute.c
    ${MPDEC_PATH}/crt.c
    ${MPDEC_PATH}/difradix2.c
    ${MPDEC_PATH}/fnt.c
    ${MPDEC_PATH}/fourstep.c
    ${MPDEC_PATH}/io.c
    ${MPDEC_PATH}/mpalloc.c
    ${MPDEC_PATH}/mpdecimal.c
    ${MPDEC_PATH}/mpsignal.c
    ${MPDEC_PATH}/numbertheory.c
    ${MPDEC_PATH}/sixstep.c
    ${MPDEC_PATH}/transpose.c
)

add_library(mpdecimal STATIC ${MPDEC_SOURCES})

target_compile_definitions(mpdecimal PUBLIC CONFIG_64 ANSI)
target_include_directories(mpdecimal PUBLIC ${MPDEC_PATH})

set(APP_SOURCES
    main.c
    calculator.c
    err.c
    lexer.c
    node.c
    number.c
    parser.c
)

add_executable(calc ${APP_SOURCES})

target_link_libraries(calc PRIVATE mpdecimal)

if(UNIX)
    target_link_libraries(calc PRIVATE m)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)