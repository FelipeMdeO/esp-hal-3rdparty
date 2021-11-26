/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _SOC_GPIO_SIG_MAP_H_
#define _SOC_GPIO_SIG_MAP_H_

#define SPICLK_OUT_MUX_IDX      SPICLK_OUT_IDX
#define SPIQ_IN_IDX                                       0
#define SPIQ_OUT_IDX                                      0
#define SPID_IN_IDX                                       1
#define SPID_OUT_IDX                                      1
#define SPIHD_IN_IDX                                      2
#define SPIHD_OUT_IDX                                     2
#define SPIWP_IN_IDX                                      3
#define SPIWP_OUT_IDX                                     3
#define SPICLK_OUT_IDX                                    4
#define SPICS0_OUT_IDX                                    5
#define U0RXD_IN_IDX                                      6
#define U0TXD_OUT_IDX                                     6
#define U0CTS_IN_IDX                                      7
#define U0RTS_OUT_IDX                                     7
#define U0DSR_IN_IDX                                      8
#define U0DTR_OUT_IDX                                     8
#define U1RXD_IN_IDX                                      9
#define U1TXD_OUT_IDX                                     9
#define U1CTS_IN_IDX                                      10
#define U1RTS_OUT_IDX                                     10
#define U1DSR_IN_IDX                                      11
#define U1DTR_OUT_IDX                                     11
#define I2S_MCLK_IN_IDX                                   12
#define I2S_MCLK_OUT_IDX                                  12
#define I2SO_BCK_IN_IDX                                   13
#define I2SO_BCK_OUT_IDX                                  13
#define I2SO_WS_IN_IDX                                    14
#define I2SO_WS_OUT_IDX                                   14
#define I2SI_SD_IN_IDX                                    15
#define I2SO_SD_OUT_IDX                                   15
#define I2SI_BCK_IN_IDX                                   16
#define I2SI_BCK_OUT_IDX                                  16
#define I2SI_WS_IN_IDX                                    17
#define I2SI_WS_OUT_IDX                                   17
#define I2SO_SD1_OUT_IDX                                  18
#define CPU_TESTBUS0_IDX                                  20
#define CPU_TESTBUS1_IDX                                  21
#define CPU_TESTBUS2_IDX                                  22
#define CPU_TESTBUS3_IDX                                  23
#define CPU_TESTBUS4_IDX                                  24
#define CPU_TESTBUS5_IDX                                  25
#define CPU_TESTBUS6_IDX                                  26
#define CPU_TESTBUS7_IDX                                  27
#define CPU_GPIO_IN0_IDX                                  28
#define CPU_GPIO_OUT0_IDX                                 28
#define CPU_GPIO_IN1_IDX                                  29
#define CPU_GPIO_OUT1_IDX                                 29
#define CPU_GPIO_IN2_IDX                                  30
#define CPU_GPIO_OUT2_IDX                                 30
#define CPU_GPIO_IN3_IDX                                  31
#define CPU_GPIO_OUT3_IDX                                 31
#define CPU_GPIO_IN4_IDX                                  32
#define CPU_GPIO_OUT4_IDX                                 32
#define CPU_GPIO_IN5_IDX                                  33
#define CPU_GPIO_OUT5_IDX                                 33
#define CPU_GPIO_IN6_IDX                                  34
#define CPU_GPIO_OUT6_IDX                                 34
#define CPU_GPIO_IN7_IDX                                  35
#define CPU_GPIO_OUT7_IDX                                 35
#define USB_JTAG_TCK_IDX                                  36
#define USB_JTAG_TMS_IDX                                  37
#define USB_JTAG_TDI_IDX                                  38
#define USB_JTAG_TDO_IDX                                  39
#define USB_EXTPHY_VP_IDX                                 40
#define USB_EXTPHY_OEN_IDX                                40
#define USB_EXTPHY_VM_IDX                                 41
#define USB_EXTPHY_SPEED_IDX                              41
#define USB_EXTPHY_RCV_IDX                                42
#define USB_EXTPHY_VPO_IDX                                42
#define USB_EXTPHY_VMO_IDX                                43
#define USB_EXTPHY_SUSPND_IDX                             44
#define EXT_ADC_START_IDX                                 45
#define LEDC_LS_SIG_OUT0_IDX                              45
#define LEDC_LS_SIG_OUT1_IDX                              46
#define LEDC_LS_SIG_OUT2_IDX                              47
#define LEDC_LS_SIG_OUT3_IDX                              48
#define LEDC_LS_SIG_OUT4_IDX                              49
#define LEDC_LS_SIG_OUT5_IDX                              50
#define RMT_SIG_IN0_IDX                                   51
#define RMT_SIG_OUT0_IDX                                  51
#define RMT_SIG_IN1_IDX                                   52
#define RMT_SIG_OUT1_IDX                                  52
#define I2CEXT0_SCL_IN_IDX                                53
#define I2CEXT0_SCL_OUT_IDX                               53
#define I2CEXT0_SDA_IN_IDX                                54
#define I2CEXT0_SDA_OUT_IDX                               54
#define GPIO_SD0_OUT_IDX                                  55
#define GPIO_SD1_OUT_IDX                                  56
#define GPIO_SD2_OUT_IDX                                  57
#define GPIO_SD3_OUT_IDX                                  58
#define EVENT_MATRIX_IN0_IDX                              59
#define TASK_MATRIX_OUT0_IDX                              59
#define EVENT_MATRIX_IN1_IDX                              60
#define TASK_MATRIX_OUT1_IDX                              60
#define EVENT_MATRIX_IN2_IDX                              61
#define TASK_MATRIX_OUT2_IDX                              61
#define EVENT_MATRIX_IN3_IDX                              62
#define TASK_MATRIX_OUT3_IDX                              62
#define FSPICLK_IN_IDX                                    63
#define FSPICLK_OUT_IDX                                   63
#define FSPIQ_IN_IDX                                      64
#define FSPIQ_OUT_IDX                                     64
#define FSPID_IN_IDX                                      65
#define FSPID_OUT_IDX                                     65
#define FSPIHD_IN_IDX                                     66
#define FSPIHD_OUT_IDX                                    66
#define FSPIWP_IN_IDX                                     67
#define FSPIWP_OUT_IDX                                    67
#define FSPICS0_IN_IDX                                    68
#define FSPICS0_OUT_IDX                                   68
#define FSPICS1_OUT_IDX                                   69
#define FSPICS2_OUT_IDX                                   70
#define FSPICS3_OUT_IDX                                   71
#define FSPICS4_OUT_IDX                                   72
#define FSPICS5_OUT_IDX                                   73
#define TWAI_RX_IDX                                       74
#define TWAI_TX_IDX                                       74
#define TWAI_BUS_OFF_ON_IDX                               75
#define TWAI_CLKOUT_IDX                                   76
#define PCMFSYNC_IN_IDX                                   77
#define PCMFSYNC_OUT_IDX                                  77
#define PCMCLK_IN_IDX                                     78
#define PCMCLK_OUT_IDX                                    78
#define PCMDIN_IDX                                        79
#define PCMDOUT_IDX                                       79
#define CO_EXT_PRIORITY_IN_IDX                            80
#define CO_EXT_PRIORITY_OUT_IDX                           80
#define CO_EXT_ACTIVE_IN_IDX                              81
#define CO_EXT_ACTIVE_OUT_IDX                             81
#define MODEM_COEX_GRANT1_IDX                             87
#define MODEM_COEX_GRANT2_IDX                             88
#define ANT_SEL0_IDX                                      89
#define ANT_SEL1_IDX                                      90
#define ANT_SEL2_IDX                                      91
#define ANT_SEL3_IDX                                      92
#define ANT_SEL4_IDX                                      93
#define ANT_SEL5_IDX                                      94
#define ANT_SEL6_IDX                                      95
#define ANT_SEL7_IDX                                      96
#define SIG_IN_FUNC_97_IDX                                97
#define SIG_IN_FUNC97_IDX                                 97
#define SIG_IN_FUNC_98_IDX                                98
#define SIG_IN_FUNC98_IDX                                 98
#define SIG_IN_FUNC_99_IDX                                99
#define SIG_IN_FUNC99_IDX                                 99
#define SIG_IN_FUNC_100_IDX                               100
#define SIG_IN_FUNC100_IDX                                100
#define SYNCERR_IDX                                       101
#define SYNC_FOUND_IDX                                    102
#define CH_IDX_IDX                                        103
#define SYNC_WINDOW_IDX                                   104
#define DATA_EN_IDX                                       105
#define DATA_IDX                                          106
#define PKT_TX_ON_IDX                                     107
#define PKT_RX_ON_IDX                                     108
#define TXRU_ON_IDX                                       109
#define RXRU_ON_IDX                                       110
#define LELC_ST3_IDX                                      111
#define LELC_ST2_IDX                                      112
#define LELC_ST1_IDX                                      113
#define LELC_ST0_IDX                                      114
#define CRCOK_IDX                                         115
#define CLK_GPIO_IDX                                      116
#define RADIO_START_IDX                                   117
#define SEQUENCE_ON_IDX                                   118
#define PUMP_CLK_IDX                                      119
#define PUMP_XPD_IDX                                      120
#define PUMP_DRV1_IDX                                     121
#define PUMP_DRV0_IDX                                     122
#define CLK_OUT_OUT1_IDX                                  123
#define CLK_OUT_OUT2_IDX                                  124
#define CLK_OUT_OUT3_IDX                                  125
#define SPICS1_OUT_IDX                                    126
#define USB_JTAG_TRST_IDX                                 127
#define SIG_GPIO_OUT_IDX                                  128
#define GPIO_MAP_DATE_IDX                                 0x2109090
#endif  /* _SOC_GPIO_SIG_MAP_H_ */
