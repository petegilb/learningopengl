cmake_minimum_required(VERSION 4.1)
project(learningopengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Compiler Optimizations ---
if(MSVC)
    # This sets the Runtime Library (Static vs Dynamic)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>")
    add_compile_options(/arch:AVX2)
endif()

# --- Dependencies (GLFW) ---
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# --- Paths ---
set(EXTERNAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(GLAD_PATH "${EXTERNAL_PATH}/glad")
set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")

# --- Find System OpenGL ---
# This finds libGL.so on Linux and opengl32.lib on Windows automatically.
find_package(OpenGL REQUIRED)

# --- Target Definition (The Core) ---
# Define the executable ONCE with all its source files
add_executable(${PROJECT_NAME}
        "${SRC_PATH}/main.cpp"
        "${GLAD_PATH}/src/glad.c"
        "${SRC_PATH}/shader.h"
        "${EXTERNAL_PATH}/stb_image.h"
)

# --- Include Directories ---
target_include_directories(${PROJECT_NAME} PRIVATE
        "${GLAD_PATH}/include"
        "${SRC_PATH}"
        "${EXTERNAL_PATH}"
)

# --- Linking (The "Why") ---
# 1. glfw: The windowing library we fetched
# 2. opengl32: The Windows system driver for OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        OpenGL::GL
        glm::glm
)

# System-specific tweaks
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa")
elseif (UNIX AND NOT APPLE)
    # Linux specifically needs the threading and dynamic loading libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
endif()

# --- Project Properties ---
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# --- Shaders ---
set(SHADER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADER_DEST_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SHADER_SOURCE_DIR}"
        "${SHADER_DEST_DIR}"
        COMMENT "Copying shaders to output directory"
)

# --- Assets ---
set(ASSET_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_DEST_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSET_SOURCE_DIR}"
        "${ASSET_DEST_DIR}"
        COMMENT "Copying assets to output directory"
)
