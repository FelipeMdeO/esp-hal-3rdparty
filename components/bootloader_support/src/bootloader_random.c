/*
 * SPDX-FileCopyrightText: 2010-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "sdkconfig.h"
#include "bootloader_random.h"
#include "hal/cpu_hal.h"
#include "soc/wdev_reg.h"

#ifndef BOOTLOADER_BUILD
#include "esp_system.h"
#include "driver/periph_ctrl.h"

 __attribute__((weak)) void bootloader_fill_random(void *buffer, size_t length)
{
    return esp_fill_random(buffer, length);
}

#else
 __attribute__((weak)) void bootloader_fill_random(void *buffer, size_t length)
{
    uint8_t *buffer_bytes = (uint8_t *)buffer;
    uint32_t random;
    uint32_t start, now;

    assert(buffer != NULL);

    for (size_t i = 0; i < length; i++) {
        if (i == 0 || i % 4 == 0) { /* redundant check is for a compiler warning */
            /* in bootloader with ADC feeding HWRNG, we accumulate 1
               bit of entropy per 40 APB cycles (==80 CPU cycles.)

               To avoid reading the entire RNG hardware state out
               as-is, we repeatedly read the RNG register and XOR all
               values.
            */
            random = REG_READ(WDEV_RND_REG);
            start = cpu_hal_get_cycle_count();
            do {
                random ^= REG_READ(WDEV_RND_REG);
                now = cpu_hal_get_cycle_count();
            } while (now - start < 80 * 32 * 2); /* extra factor of 2 is precautionary */
        }
        buffer_bytes[i] = random >> ((i % 4) * 8);
    }
}

#endif // BOOTLOADER_BUILD
