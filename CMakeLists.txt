cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME STM32F427VIT6)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
    Core/Src/sd.c)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)


file(GLOB_RECURSE OV5640_SOURCES "${CMAKE_SOURCE_DIR}/Drivers/BSP/OV5640/*.c")
file(GLOB_RECURSE OV2640_SOURCES "${CMAKE_SOURCE_DIR}/Drivers/BSP/OV2640/*.c")
file(GLOB CAMERA_SOURCES CONFIGURE_DEPENDS "Core/Src/camera/*.c")
file(GLOB LCD_SOURCES CONFIGURE_DEPENDS "Core/Src/lcd/*.c")
file(GLOB TCP_SERVER_SOURCES CONFIGURE_DEPENDS "Core/Src/tcp_server/*.c")


# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${TCP_SERVER_SOURCES}
    ${CAMERA_SOURCES}
    ${LCD_SOURCES}
    ${OV5640_SOURCES}
)


# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/Inc/lcd
    Drivers/BSP/OV5640
    # Core/Src/lvgl
    # Core/Src/ui
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    # Add user defined libraries
)

