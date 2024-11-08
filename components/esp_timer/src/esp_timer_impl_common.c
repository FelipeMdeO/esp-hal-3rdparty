/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "esp_timer_impl.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_task.h"
#include "esp_attr.h"

#ifdef __NuttX__
#include <nuttx/spinlock.h>
#define ENTER_CRITICAL_SECTION(lock) do { \
            assert(g_flags == UINT32_MAX); \
            g_flags = spin_lock_irqsave(lock); \
        } while(0)
#define LEAVE_CRITICAL_SECTION(lock) do { \
            spin_unlock_irqrestore((lock), g_flags); \
            g_flags = UINT32_MAX; \
        } while(0)
#define LOCK_INITIALIZER_UNLOCKED       0
typedef spinlock_t lock_type_t;
static irqstate_t g_flags = UINT32_MAX;
#else
#define ENTER_CRITICAL_SECTION(lock)    portENTER_CRITICAL_SAFE(lock)
#define LEAVE_CRITICAL_SECTION(lock)    portEXIT_CRITICAL_SAFE(lock)
#define LOCK_INITIALIZER_UNLOCKED       portMUX_INITIALIZER_UNLOCKED

typedef portMUX_TYPE lock_type_t;
#endif

/* Spinlock used to protect access to the hardware registers. */
lock_type_t s_time_update_lock = LOCK_INITIALIZER_UNLOCKED;

/* Alarm values to generate interrupt on match
 * [0] - for ESP_TIMER_TASK alarms,
 * [1] - for ESP_TIMER_ISR alarms.
*/
uint64_t timestamp_id[2] = { UINT64_MAX, UINT64_MAX };

void esp_timer_impl_lock(void)
{
    ENTER_CRITICAL_SECTION(&s_time_update_lock);
}

void esp_timer_impl_unlock(void)
{
    LEAVE_CRITICAL_SECTION(&s_time_update_lock);
}

void esp_timer_private_lock(void) __attribute__((alias("esp_timer_impl_lock")));
void esp_timer_private_unlock(void) __attribute__((alias("esp_timer_impl_unlock")));

void IRAM_ATTR esp_timer_impl_set_alarm(uint64_t timestamp)
{
    esp_timer_impl_set_alarm_id(timestamp, 0);
}

#ifdef CONFIG_ESP_TIMER_SUPPORTS_ISR_DISPATCH_METHOD
void IRAM_ATTR esp_timer_impl_try_to_set_next_alarm(void) {
    portENTER_CRITICAL_ISR(&s_time_update_lock);
    unsigned now_alarm_idx;  // ISR is called due to this current alarm
    unsigned next_alarm_idx; // The following alarm after now_alarm_idx
    if (timestamp_id[0] < timestamp_id[1]) {
        now_alarm_idx = 0;
        next_alarm_idx = 1;
    } else {
        now_alarm_idx = 1;
        next_alarm_idx = 0;
    }

    if (timestamp_id[next_alarm_idx] != UINT64_MAX) {
        // The following alarm is valid and can be used.
        // Remove the current alarm from consideration.
        esp_timer_impl_set_alarm_id(UINT64_MAX, now_alarm_idx);
    } else {
        // There is no the following alarm.
        // Remove the current alarm from consideration as well.
        timestamp_id[now_alarm_idx] = UINT64_MAX;
    }
    portEXIT_CRITICAL_ISR(&s_time_update_lock);
}
#endif

/* FIXME: This value is safe for 80MHz APB frequency, should be modified to depend on clock frequency. */
uint64_t IRAM_ATTR esp_timer_impl_get_min_period_us(void)
{
    return 50;
}
