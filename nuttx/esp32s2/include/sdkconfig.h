/*
 * Copyright (c) 2023 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <nuttx/config.h>

#define CONFIG_ESP_REV_MIN_FULL 0
#define CONFIG_ESP_REV_MAX_FULL 199
#define CONFIG_IDF_TARGET_ARCH_XTENSA 1
#define CONFIG_IDF_TARGET_ESP32S2 1
#define CONFIG_IDF_FIRMWARE_CHIP_ID 0x0002
#define CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ CONFIG_ESP32S2_DEFAULT_CPU_FREQ_MHZ
#define CONFIG_RTC_CLK_SRC_INT_RC 1
#define CONFIG_RTC_CLK_CAL_CYCLES 576
#define CONFIG_XTAL_FREQ 40
#define CONFIG_MMU_PAGE_SIZE 0x10000
#define CONFIG_LOG_TIMESTAMP_SOURCE_RTOS 1
#define CONFIG_ESPTOOLPY_FLASHMODE_DIO 1
#define CONFIG_BOOTLOADER_OFFSET_IN_FLASH 0x1000

#if (defined(CONFIG_UART0_SERIAL_CONSOLE) && defined(CONFIG_ESP32S2_UART0))
#define CONFIG_ESP_CONSOLE_UART_NUM 0
#elif defined(CONFIG_UART1_SERIAL_CONSOLE) && defined(CONFIG_ESP32S2_UART1)
#define CONFIG_ESP_CONSOLE_UART_NUM 1
#endif

#if defined(CONFIG_DEBUG_INFO)
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_MAXIMUM_LEVEL 3
#elif defined(CONFIG_DEBUG_WARN)
#define CONFIG_LOG_DEFAULT_LEVEL 2
#define CONFIG_LOG_MAXIMUM_LEVEL 2
#elif defined(CONFIG_DEBUG_ERROR)
#define CONFIG_LOG_DEFAULT_LEVEL 1
#define CONFIG_LOG_MAXIMUM_LEVEL 1
#else
#define CONFIG_LOG_DEFAULT_LEVEL 0
#define CONFIG_LOG_MAXIMUM_LEVEL 0
#endif

#ifdef CONFIG_ESPRESSIF_SIMPLE_BOOT
#  define CONFIG_ESP_CONSOLE_UART 1
#  define CONFIG_ESP_CONSOLE_UART_BAUDRATE 115200
#  define CONFIG_PARTITION_TABLE_OFFSET 0x1000
#  define IDF_VER 0
#  define CONFIG_FREERTOS_UNICORE 1
#  define CONFIG_SPI_FLASH_ROM_DRIVER_PATCH 1
#  define CONFIG_BOOTLOADER_FLASH_XMC_SUPPORT 1
#  define CONFIG_BOOTLOADER_REGION_PROTECTION_ENABLE 1
#endif
