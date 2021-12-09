cmake_minimum_required(VERSION 3.0)
project(cssmh)

add_compile_options(-g -Wall -Wextra -Wpedantic)
add_link_options(-pthread)

set(CSSMH_DIR ${PROJECT_SOURCE_DIR}/cssmh)
set(IMGUI_DIR ${CSSMH_DIR}/imgui)
file(GLOB_RECURSE CSSMH_SRC ${CSSMH_DIR}/*.cpp)

add_executable(cssmh ${CSSMH_SRC})
target_link_libraries(cssmh X11 glfw GL)
target_include_directories(cssmh PUBLIC ${IMGUI_DIR})
