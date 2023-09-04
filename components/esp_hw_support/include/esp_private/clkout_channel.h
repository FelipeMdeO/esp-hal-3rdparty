/*
 * SPDX-FileCopyrightText: 2010-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum clock_out_channel {
    CLKOUT_CHANNEL_1,
    CLKOUT_CHANNEL_2,
    CLKOUT_CHANNEL_3,
    CLKOUT_CHANNEL_MAX,
} clock_out_channel_t;

#if SOC_GPIO_CLOCKOUT_BY_IO_MUX
#if CONFIG_IDF_TARGET_ESP32
#define CLKOUT_CHANNEL1_GPIO    GPIO_NUM_0
#define CLKOUT_CHANNEL2_GPIO    GPIO_NUM_3
#define CLKOUT_CHANNEL3_GPIO    GPIO_NUM_1
#define FUNC_CLK_OUT1           FUNC_GPIO0_CLK_OUT1
#define FUNC_CLK_OUT2           FUNC_U0RXD_CLK_OUT2
#define FUNC_CLK_OUT3           FUNC_U0TXD_CLK_OUT3
#elif CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
#define CLKOUT_CHANNEL1_GPIO    GPIO_NUM_20
#define CLKOUT_CHANNEL2_GPIO    GPIO_NUM_19
#define CLKOUT_CHANNEL3_GPIO    GPIO_NUM_18
#define FUNC_CLK_OUT1           FUNC_GPIO20_CLK_OUT1
#define FUNC_CLK_OUT2           FUNC_GPIO19_CLK_OUT2
#define FUNC_CLK_OUT3           FUNC_DAC_2_CLK_OUT3
#endif
#define IS_VALID_CLKOUT_IO(gpio_num)    ((gpio_num == CLKOUT_CHANNEL1_GPIO) || (gpio_num == CLKOUT_CHANNEL2_GPIO) || (gpio_num == CLKOUT_CHANNEL3_GPIO))
#elif SOC_GPIO_CLOCKOUT_BY_GPIO_MATRIX
#define IS_VALID_CLKOUT_IO(gpio_num)    GPIO_IS_VALID_GPIO(gpio_num)
#endif

#define IONUM_TO_CLKOUT(gpio_num)       ((gpio_num == CLKOUT_CHANNEL1_GPIO) ? CLKOUT_CHANNEL_1 : \
                                         (gpio_num == CLKOUT_CHANNEL2_GPIO) ? CLKOUT_CHANNEL_2 : \
                                         (gpio_num == CLKOUT_CHANNEL3_GPIO) ? CLKOUT_CHANNEL_3 : 0)

#ifdef __cplusplus
}
#endif
