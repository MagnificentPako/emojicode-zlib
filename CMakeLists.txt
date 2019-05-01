cmake_minimum_required(VERSION 3.10)

project(zlib VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

file(GLOB EMOJIC_DEPEND "src/*.emojic")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(zlib STATIC src/zlib.cpp zlib_.o)

set_property(TARGET zlib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_options(zlib PUBLIC -Wall -Wno-unused-result -Wno-missing-braces -pedantic -lssl -lcrypto)

get_filename_component(MAIN_FILE src/zlib.emojic ABSOLUTE)

add_custom_command(OUTPUT zlib_.o COMMAND emojicodec -p zlib -o zlib_.o -i
    interface.emojii -c ${MAIN_FILE} --color DEPENDS ${EMOJIC_DEPEND})

install(FILES build/libzlib.a DESTINATION lib/emojicode/zlib)
install(FILES build/interface.emojii DESTINATION lib/emojicode/zlib)

#install(TARGETS sha
#    ARCHIVE DESTINATION lib/emojicode/sha)

#install(FILES src/interface.emojii
#    DESTINATION lib/emojicode/sha)
