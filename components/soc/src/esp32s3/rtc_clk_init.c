// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "esp_rom_uart.h"
#include "esp32s3/rom/rtc.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/apb_ctrl_reg.h"
#include "i2c_rtc_clk.h"
#include "soc_log.h"
#include "xtensa/core-macros.h"
#include "rtc_clk_common.h"

static const char *TAG = "rtc_clk_init";

void rtc_clk_init(rtc_clk_config_t cfg)
{
    rtc_cpu_freq_config_t old_config, new_config;

    /* Set tuning parameters for 8M and 90k clocks.
     * Note: this doesn't attempt to set the clocks to precise frequencies.
     * Instead, we calibrate these clocks against XTAL frequency later, when necessary.
     * - SCK_DCAP value controls tuning of 90k clock.
     *   The higher the value of DCAP is, the lower is the frequency.
     * - CK8M_DFREQ value controls tuning of 8M clock.
     *   CLK_8M_DFREQ constant gives the best temperature characteristics.
     */
    REG_SET_FIELD(RTC_CNTL_REG, RTC_CNTL_SCK_DCAP, cfg.slow_clk_dcap);
    REG_SET_FIELD(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_CK8M_DFREQ, cfg.clk_8m_dfreq);

    /* Configure 90k clock division */
    rtc_clk_divider_set(cfg.clk_rtc_clk_div);

    /* Configure 8M clock division */
    rtc_clk_8m_divider_set(cfg.clk_8m_clk_div);

    /* Enable the internal bus used to configure PLLs */
    SET_PERI_REG_BITS(ANA_CONFIG_REG, ANA_CONFIG_M, ANA_CONFIG_M, ANA_CONFIG_S);
    CLEAR_PERI_REG_MASK(ANA_CONFIG_REG, I2C_APLL_M | I2C_BBPLL_M);

    rtc_xtal_freq_t xtal_freq = cfg.xtal_freq;
    esp_rom_uart_tx_wait_idle(0);
    rtc_clk_xtal_freq_update(xtal_freq);
    rtc_clk_apb_freq_update(xtal_freq * MHZ);

    /* Set CPU frequency */
    rtc_clk_cpu_freq_get_config(&old_config);
    uint32_t freq_before = old_config.freq_mhz;
    bool res = rtc_clk_cpu_freq_mhz_to_config(cfg.cpu_freq_mhz, &new_config);
    if (!res) {
        SOC_LOGE(TAG, "invalid CPU frequency value");
        abort();
    }
    rtc_clk_cpu_freq_set_config(&new_config);

    /* Re-calculate the ccount to make time calculation correct. */
    XTHAL_SET_CCOUNT( (uint64_t)XTHAL_GET_CCOUNT() * cfg.cpu_freq_mhz / freq_before );

    /* Slow & fast clocks setup */
    if (cfg.slow_freq == RTC_SLOW_FREQ_32K_XTAL) {
        rtc_clk_32k_enable(true);
    }
    if (cfg.fast_freq == RTC_FAST_FREQ_8M) {
        bool need_8md256 = cfg.slow_freq == RTC_SLOW_FREQ_8MD256;
        rtc_clk_8m_enable(true, need_8md256);
    }
    rtc_clk_fast_freq_set(cfg.fast_freq);
    rtc_clk_slow_freq_set(cfg.slow_freq);
}
