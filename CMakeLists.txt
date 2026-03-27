cmake_minimum_required(VERSION 3.10)
project(BeeBusy)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(game PRIVATE lib)

file(GLOB SOURCES "src/*.cpp")

add_executable(BeeBusy ${SOURCES})

target_link_libraries(BeeBusy raylib opengl32 gdi32 winmm)

#target_link_options(BeeBusy PRIVATE -Wl,--subsystem,windows)

add_custom_command(TARGET BeeBusy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:BeeBusy>/assets
)