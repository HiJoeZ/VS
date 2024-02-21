#需求最低的cmake版本
cmake_minimum_required(VERSION 3.20)

#工程名称
project(OpenGL_learn VERSION 0.1)

#支持的C++版本
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DDEBUG_)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)
link_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)

add_subdirectory(wrapper)
add_subdirectory(application)

SET(SRC_LIST main.cpp glad.c)

#本工程所有cpp文件编译链接，生成exe
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} glfw3.lib wrapper application)