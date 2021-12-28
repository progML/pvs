cmake_minimum_required(VERSION 3.17)
project(system-design-lab3 C)

set(CMAKE_C_STANDARD 11)

add_definitions(-DUSE_HAL_DRIVER -DUSE_HAL_DRIVER -DUSE_HAL_DRIVER
        -DSTM32F407xx
        #-DSTM32F427xx
)
include_directories(Core/Inc Drivers/STM32F4xx_HAL_Driver/Inc Drivers/CMSIS/Device/ST/STM32F4xx/Include)

file(GLOB SOURCE_FILES LIST_DIRECTORIES false Core/Src/*.c)
add_executable(main
    Core/Src/stm32f4xx_it.c Core/Src/stm32f4xx_hal_msp.c
    ${SOURCE_FILES}
)

