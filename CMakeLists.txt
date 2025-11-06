cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchain.cmake)

project(mcu-template)

function(ihx_to_hex bin)
    add_custom_command(TARGET ${bin} POST_BUILD COMMAND  packihx ${bin}.ihx > ${bin}.hex)
endfunction(ihx_to_hex)

add_subdirectory(led-blink)
add_subdirectory(led-blink-int)
add_subdirectory(led-blink-by-timer)
