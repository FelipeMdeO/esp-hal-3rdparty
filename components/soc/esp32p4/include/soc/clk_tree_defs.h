/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 ************************* ESP32P4 Root Clock Source ****************************
 * 1) Internal 17.5MHz RC Oscillator: RC_FAST (may also referred as FOSC in TRM and reg. description)
 *
 *    This RC oscillator generates a ~17.5MHz clock signal output as the RC_FAST_CLK.
 *
 *    The exact frequency of RC_FAST_CLK can be computed in runtime through calibration.
 *
 * 2) External 40MHz Crystal Clock: XTAL
 *
 * 3) Internal 136kHz RC Oscillator: RC_SLOW (may also referrred as SOSC in TRM or reg. description)
 *
 *    This RC oscillator generates a ~136kHz clock signal output as the RC_SLOW_CLK. The exact frequency of this clock
 *    can be computed in runtime through calibration.
 *
 * 4) Internal 32kHz RC Oscillator: RC32K
 *
 *    The exact frequency of this clock can be computed in runtime through calibration.
 *
 * 5) External 32kHz Crystal Clock (optional): XTAL32K
 *
 *    The clock source for this XTAL32K_CLK should be a 32kHz crystal connecting to the XTAL_32K_P and XTAL_32K_N
 *    pins.
 *
 *    XTAL32K_CLK can also be calibrated to get its exact frequency.
 *
 * 6) External Slow Clock (optional): OSC_SLOW
 *
 *    A slow clock signal generated by an external circuit can be connected to GPIO1 to be the clock source for the
 *    RTC_SLOW_CLK.
 *
 *    OSC_SLOW_CLK can also be calibrated to get its exact frequency.
 *
 *
 * PLL Clocks:
 *
 * from 40MHz XTAL oscillator frequency multipliers:
 * 1) CPLL (400MHz), used for CPU clock source
 * 2) MPLL (500MHz), used for MSPI-PSRAM clock source; and is further divided to PLL_F50M, PLL_F25M, to be used for peripheral's clock sources
 * 3) SPLL (480MHz), directly used for MSPI-Flash, MSPI-PSRAM, GPSPI clock sources; and is further divided to PLL_F240M, PLL_F160M, PLL_F120M, PLL_F80M, PLL_F20M, to be used for peripherals' clock sources
 * 4) APLL (configurable), can be the clock source for peripherals (GPSPI, I2S, LCD, CAM, etc.)
 * 5) SDIO_PLL0/1/2
 *
 * from 32kHz slow clock oscillator frequency multiplier:
 * 6) LP_PLL (8MHz), used for RTC_FAST_CLK clock source and LP peripherals' clock sources
 */

/* With the default value of FOSC_DFREQ = 100, RC_FAST clock frequency is 17.5 MHz +/- 7% */ // TODO: check
#define SOC_CLK_RC_FAST_FREQ_APPROX         17500000                            /*!< Approximate RC_FAST_CLK frequency in Hz */
#define SOC_CLK_RC_SLOW_FREQ_APPROX         136000                              /*!< Approximate RC_SLOW_CLK frequency in Hz */
#define SOC_CLK_RC32K_FREQ_APPROX           32768                               /*!< Approximate RC32K_CLK frequency in Hz */
#define SOC_CLK_XTAL32K_FREQ_APPROX         32768                               /*!< Approximate XTAL32K_CLK frequency in Hz */
#define SOC_CLK_OSC_SLOW_FREQ_APPROX        32768                               /*!< Approximate OSC_SLOW_CLK (external slow clock) frequency in Hz */

// Naming convention: SOC_ROOT_CLK_{loc}_{type}_[attr]
// {loc}: EXT, INT
// {type}: XTAL, RC
// [attr] - optional: [frequency], FAST, SLOW
/**
 * @brief Root clock
 */
typedef enum {
    SOC_ROOT_CLK_INT_RC_FAST,          /*!< Internal 17.5MHz RC oscillator */
    SOC_ROOT_CLK_INT_RC_SLOW,          /*!< Internal 136kHz RC oscillator */
    SOC_ROOT_CLK_EXT_XTAL,             /*!< External 40MHz crystal */
    SOC_ROOT_CLK_EXT_XTAL32K,          /*!< External 32kHz crystal */
    SOC_ROOT_CLK_INT_RC32K,            /*!< Internal 32kHz RC oscillator */
    SOC_ROOT_CLK_EXT_OSC_SLOW,         /*!< External slow clock signal at pin1 */
} soc_root_clk_t;

/**
 * @brief CPU_CLK mux inputs, which are the supported clock sources for the CPU_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_CPU_CLK_SRC_XTAL = 0,              /*!< Select XTAL_CLK as CPU_CLK source */
    SOC_CPU_CLK_SRC_PLL = 1,               /*!< Select (C)PLL_CLK as CPU_CLK source (CPLL_CLK is the output of 40MHz crystal oscillator frequency multiplier, 400MHz) */
    SOC_CPU_CLK_SRC_RC_FAST = 2,           /*!< Select RC_FAST_CLK as CPU_CLK source */
    SOC_CPU_CLK_SRC_INVALID,               /*!< Invalid CPU_CLK source */
} soc_cpu_clk_src_t;

/**
 * @brief RTC_SLOW_CLK mux inputs, which are the supported clock sources for the RTC_SLOW_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_RTC_SLOW_CLK_SRC_RC_SLOW = 0,                 /*!< Select RC_SLOW_CLK as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_XTAL32K = 1,                 /*!< Select XTAL32K_CLK as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_RC32K = 2,                   /*!< Select RC32K_CLK as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_OSC_SLOW = 3,                /*!< Select OSC_SLOW_CLK (external slow clock) as RTC_SLOW_CLK source */
    SOC_RTC_SLOW_CLK_SRC_INVALID,                     /*!< Invalid RTC_SLOW_CLK source */
} soc_rtc_slow_clk_src_t;

/**
 * @brief RTC_FAST_CLK mux inputs, which are the supported clock sources for the RTC_FAST_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_RTC_FAST_CLK_SRC_RC_FAST = 0,      /*!< Select RC_FAST_CLK as RTC_FAST_CLK source */
    SOC_RTC_FAST_CLK_SRC_XTAL = 1,         /*!< Select XTAL_CLK as RTC_FAST_CLK source */
    SOC_RTC_FAST_CLK_SRC_XTAL_DIV = SOC_RTC_FAST_CLK_SRC_XTAL, /*!< Alias name for `SOC_RTC_FAST_CLK_SRC_XTAL` */
    SOC_RTC_FAST_CLK_SRC_LP_PLL = 2,       /*!< Select LP_PLL_CLK as RTC_FAST_CLK source (LP_PLL_CLK is a 8MHz clock sourced from RC32K or XTAL32K) */
    SOC_RTC_FAST_CLK_SRC_INVALID,          /*!< Invalid RTC_FAST_CLK source */
} soc_rtc_fast_clk_src_t;

/**
 * @brief LP_PLL_CLK mux inputs, which are the supported clock sources for the LP_PLL_CLK
 * @note Enum values are matched with the register field values on purpose
 */
typedef enum {
    SOC_LP_PLL_CLK_SRC_RC32K = 0,          /*!< Select RC32K_CLK as LP_PLL_CLK source */
    SOC_LP_PLL_CLK_SRC_XTAL32K = 1,        /*!< Select XTAL32K_CLK as LP_PLL_CLK source */
    SOC_LP_PLL_CLK_SRC_INVALID,            /*!< Invalid LP_PLL_CLK source */
} soc_lp_pll_clk_src_t;

// Naming convention: SOC_MOD_CLK_{[upstream]clock_name}_[attr]
// {[upstream]clock_name}: XTAL, (S/M/A)PLL, etc.
// [attr] - optional: FAST, SLOW, D<divider>, F<freq>
/**
 * @brief Supported clock sources for modules (CPU, peripherals, RTC, etc.)
 *
 * @note enum starts from 1, to save 0 for special purpose
 */
typedef enum {
    // For CPU domain
    SOC_MOD_CLK_CPU = 1,                       /*!< CPU_CLK can be sourced from XTAL, CPLL, or RC_FAST by configuring soc_cpu_clk_src_t */
    // For RTC domain
    SOC_MOD_CLK_RTC_FAST,                      /*!< RTC_FAST_CLK can be sourced from XTAL, RC_FAST, or LP_PLL by configuring soc_rtc_fast_clk_src_t */
    SOC_MOD_CLK_RTC_SLOW,                      /*!< RTC_SLOW_CLK can be sourced from RC_SLOW, XTAL32K, RC32K, or OSC_SLOW by configuring soc_rtc_slow_clk_src_t */
    // For digital domain: peripherals
    SOC_MOD_CLK_PLL_F80M,                      /*!< PLL_F80M_CLK is derived from SPLL (clock gating + fixed divider of 6), it has a fixed frequency of 80MHz */
    SOC_MOD_CLK_PLL_F160M,                     /*!< PLL_F160M_CLK is derived from SPLL (clock gating + fixed divider of 3), it has a fixed frequency of 160MHz */
    SOC_MOD_CLK_PLL_F240M,                     /*!< PLL_F240M_CLK is derived from SPLL (clock gating + fixed divider of 2), it has a fixed frequency of 240MHz */
    SOC_MOD_CLK_XTAL32K,                       /*!< XTAL32K_CLK comes from the external 32kHz crystal, passing a clock gating to the peripherals */
    SOC_MOD_CLK_RC_FAST,                       /*!< RC_FAST_CLK comes from the internal 20MHz rc oscillator, passing a clock gating to the peripherals */
    SOC_MOD_CLK_XTAL,                          /*!< XTAL_CLK comes from the external 40MHz crystal */
    SOC_MOD_CLK_INVALID,                       /*!< Indication of the end of the available module clock sources */
} soc_module_clk_t;

//////////////////////////////////////////////////SYSTIMER//////////////////////////////////////////////////////////////

//TODO: IDF-7486
/**
 * @brief Type of SYSTIMER clock source
 */
typedef enum {
    SYSTIMER_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,       /*!< SYSTIMER source clock is XTAL */
    SYSTIMER_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST, /*!< SYSTIMER source clock is RC_FAST */
    SYSTIMER_CLK_SRC_DEFAULT = SOC_MOD_CLK_XTAL,    /*!< SYSTIMER source clock default choice is XTAL */
} soc_periph_systimer_clk_src_t;

//////////////////////////////////////////////////GPTimer///////////////////////////////////////////////////////////////



//////////////////////////////////////////////////RMT///////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////Temp Sensor///////////////////////////////////////////////////////////



///////////////////////////////////////////////////UART/////////////////////////////////////////////////////////////////

//TODO: IDF-6511
/**
 * @brief Type of UART clock source, reserved for the legacy UART driver
 */
typedef enum {
    UART_SCLK_PLL_F80M = SOC_MOD_CLK_PLL_F80M,           /*!< UART source clock is PLL_F80M */
    UART_SCLK_RTC = SOC_MOD_CLK_RC_FAST,                /*!< UART source clock is RC_FAST */
    UART_SCLK_XTAL = SOC_MOD_CLK_XTAL,                  /*!< UART source clock is XTAL */
    UART_SCLK_DEFAULT = SOC_MOD_CLK_PLL_F80M,           /*!< UART source clock default choice is PLL_F80M */
} soc_periph_uart_clk_src_legacy_t;

//////////////////////////////////////////////////MCPWM/////////////////////////////////////////////////////////////////



///////////////////////////////////////////////// I2S //////////////////////////////////////////////////////////////



/////////////////////////////////////////////////I2C////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////SPI////////////////////////////////////////////////////////////////////

//TODO: IDF-7502
/**
 * @brief Array initializer for all supported clock sources of SPI
 */
#define SOC_SPI_CLKS {SOC_MOD_CLK_PLL_F80M, SOC_MOD_CLK_XTAL, SOC_MOD_CLK_RC_FAST}

/**
 * @brief Type of SPI clock source.
 */
typedef enum {
    SPI_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F80M,     /*!< Select PLL_80M as SPI source clock */
    SPI_CLK_SRC_PLL_F80M = SOC_MOD_CLK_PLL_F80M,    /*!< Select PLL_80M as SPI source clock */
    SPI_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,            /*!< Select XTAL as SPI source clock */
    SPI_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,      /*!< Select RC_FAST as SPI source clock */
} soc_periph_spi_clk_src_t;

//////////////////////////////////////////////////SDM//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////GPIO Glitch Filter////////////////////////////////////////////////////


//////////////////////////////////////////////////TWAI//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////ADC///////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////MWDT/////////////////////////////////////////////////////////////////

//TODO: IDF-6516
/**
 * @brief Array initializer for all supported clock sources of MWDT
 */
#define SOC_MWDT_CLKS {SOC_MOD_CLK_XTAL, SOC_MOD_CLK_PLL_F80M, SOC_MOD_CLK_RC_FAST}

/**
 * @brief MWDT clock source
 */
typedef enum {
    MWDT_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,           /*!< Select XTAL as the source clock */
    MWDT_CLK_SRC_PLL_F80M = SOC_MOD_CLK_PLL_F80M,   /*!< Select PLL fixed 80 MHz as the source clock */
    MWDT_CLK_SRC_RC_FAST = SOC_MOD_CLK_RC_FAST,     /*!< Select RTC fast as the source clock */
    MWDT_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F80M,    /*!< Select PLL fixed 80 MHz as the default clock choice */
} soc_periph_mwdt_clk_src_t;

//////////////////////////////////////////////////LEDC/////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////PARLIO////////////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif
