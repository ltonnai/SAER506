cmake_minimum_required(VERSION 3.20)
project(SAER506)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows")

include_directories("C:/vcpkg/installed/x64-windows/include")
link_directories("C:/vcpkg/installed/x64-windows/lib")

add_executable(SAER506 src/main.cpp
        src/app/Ground.cpp
        include/Creature.h
        include/Ground.h
        src/app/Creature.cpp
)

target_link_libraries(SAER506
        opengl32
        glu32
        freeglut
)

add_custom_command(TARGET SAER506 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/vcpkg/installed/x64-windows/bin/freeglut.dll"
        $<TARGET_FILE_DIR:SAER506>)