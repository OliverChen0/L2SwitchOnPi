/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * MCF5441X Internal Memory Map
 *
 * Copyright 2010-2012 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
 */

#ifndef __MCF5441X__
#define __MCF5441X__

/* Interrupt Controller (INTC) */
#define INT0_LO_RSVD0			(0)
#define INT0_LO_EPORT1			(1)
#define INT0_LO_EPORT2			(2)
#define INT0_LO_EPORT3			(3)
#define INT0_LO_EPORT4			(4)
#define INT0_LO_EPORT5			(5)
#define INT0_LO_EPORT6			(6)
#define INT0_LO_EPORT7			(7)
#define INT0_LO_EDMA_00		(8)
#define INT0_LO_EDMA_01		(9)
#define INT0_LO_EDMA_02		(10)
#define INT0_LO_EDMA_03		(11)
#define INT0_LO_EDMA_04		(12)
#define INT0_LO_EDMA_05		(13)
#define INT0_LO_EDMA_06		(14)
#define INT0_LO_EDMA_07		(15)
#define INT0_LO_EDMA_08		(16)
#define INT0_LO_EDMA_09		(17)
#define INT0_LO_EDMA_10		(18)
#define INT0_LO_EDMA_11		(19)
#define INT0_LO_EDMA_12		(20)
#define INT0_LO_EDMA_13		(21)
#define INT0_LO_EDMA_14		(22)
#define INT0_LO_EDMA_15		(23)
#define INT0_LO_EDMA_ERR		(24)
#define INT0_LO_SCM			(25)
#define INT0_LO_UART0			(26)
#define INT0_LO_UART1			(27)
#define INT0_LO_UART2			(28)
#define INT0_LO_UART3			(29)
#define INT0_LO_I2C0			(30)
#define INT0_LO_DSPI0			(31)
#define INT0_HI_DTMR0			(32)
#define INT0_HI_DTMR1			(33)
#define INT0_HI_DTMR2			(34)
#define INT0_HI_DTMR3			(35)
#define INT0_HI_MACNET0_TXF		(36)
#define INT0_HI_MACNET0_TXB		(37)
#define INT0_HI_MACNET0_UN		(38)
#define INT0_HI_MACNET0_RL		(39)
#define INT0_HI_MACNET0_RXF		(40)
#define INT0_HI_MACNET0_RXB		(41)
#define INT0_HI_MACNET0_MII		(42)
#define INT0_HI_MACNET0_LC		(43)
/* not used 44 */
#define INT0_HI_MACNET0_GRA		(45)
#define INT0_HI_MACNET0_EBERR		(46)
#define INT0_HI_MACNET0_BABT		(47)
#define INT0_HI_MACNET0_BABR		(48)
#define INT0_HI_MACNET1_TXF		(49)
#define INT0_HI_MACNET1_TXB		(50)
#define INT0_HI_MACNET1_UN		(51)
#define INT0_HI_MACNET1_RL		(52)
#define INT0_HI_MACNET1_RXF		(53)
#define INT0_HI_MACNET1_RXB		(54)
#define INT0_HI_MACNET1_MII		(55)
#define INT0_HI_MACNET1_LC		(56)
/* not used 57 */
#define INT0_HI_MACNET1_GRA		(58)
#define INT0_HI_MACNET1_EBERR		(59)
#define INT0_HI_MACNET1_BABT		(60)
#define INT0_HI_MACNET1_BABR		(61)
#define INT0_HI_SCMIR			(62)
#define INT0_HI_OW			(63)

#define INT1_LO_CAN0_IFG		(0)
#define INT1_LO_CAN0_BOFF		(1)
/* not used 2 */
#define INT1_LO_CAN0_TXRXWRN		(3)
#define INT1_LO_CAN1_IFG		(4)
#define INT1_LO_CAN1_BOFF		(5)
/* not used 6 */
#define INT1_LO_CAN1_TXRXWRN		(7)
#define INT1_LO_EDMA_16		(8)
#define INT1_LO_EDMA_17		(9)
#define INT1_LO_EDMA_18		(10)
#define INT1_LO_EDMA_19		(11)
#define INT1_LO_EDMA_20		(12)
#define INT1_LO_EDMA_21		(13)
#define INT1_LO_EDMA_22		(14)
#define INT1_LO_EDMA_23		(15)
#define INT1_LO_EDMA_24		(16)
#define INT1_LO_EDMA_25		(17)
#define INT1_LO_EDMA_26		(18)
#define INT1_LO_EDMA_27		(19)
#define INT1_LO_EDMA_28		(20)
#define INT1_LO_EDMA_29		(21)
#define INT1_LO_EDMA_30		(22)
#define INT1_LO_EDMA_31		(23)
#define INT1_LO_EDMA_32		(24)
#define INT1_LO_EDMA_33		(25)
#define INT1_LO_EDMA_34		(26)
#define INT1_LO_EDMA_35		(27)
#define INT1_LO_EDMA_36		(28)
#define INT1_LO_EDMA_37		(29)
#define INT1_LO_EDMA_38		(30)
#define INT1_LO_EDMA_39		(31)
#define INT1_LO_EDMA_40		(32)
#define INT1_HI_EDMA_41		(33)
#define INT1_HI_EDMA_42		(34)
#define INT1_HI_EDMA_43		(35)
#define INT1_HI_EDMA_44		(36)
#define INT1_HI_EDMA_45		(37)
#define INT1_HI_EDMA_46		(38)
#define INT1_HI_EDMA_47		(39)
#define INT1_HI_EDMA_48		(40)
#define INT1_HI_EDMA_49		(41)
#define INT1_HI_EDMA_50		(42)
#define INT1_HI_EDMA_51		(43)
#define INT1_HI_EDMA_52		(44)
#define INT1_HI_EDMA_53		(45)
#define INT1_HI_EDMA_54		(46)
#define INT1_HI_EDMA_55		(47)
#define INT1_HI_UART4			(48)
#define INT1_HI_UART5			(49)
#define INT1_HI_UART6			(50)
#define INT1_HI_UART7			(51)
#define INT1_HI_UART8			(52)
#define INT1_HI_UART9			(53)
#define INT1_HI_DSPI1			(54)
#define INT1_HI_DSPI2			(55)
#define INT1_HI_DSPI3			(56)
#define INT1_HI_I2C1			(57)
#define INT1_HI_I2C2			(58)
#define INT1_HI_I2C3			(59)
#define INT1_HI_I2C4			(60)
#define INT1_HI_I2C5			(61)

#define INT2_LO_EDMA56_63		(0)
#define INT2_LO_PWM_SM0SR_CF		(1)
#define INT2_LO_PWM_SM1SR_CF		(2)
#define INT2_LO_PWM_SM2SR_CF		(3)
#define INT2_LO_PWM_SM3SR_CF		(4)
#define INT2_LO_PWM_SM0SR_RF		(5)
#define INT2_LO_PWM_SM1SR_RF		(6)
#define INT2_LO_PWM_SM2SR_RF		(7)
#define INT2_LO_PWM_SM3SR_RF		(8)
#define INT2_LO_PWM_FSR		(9)
#define INT2_LO_PWM_SMSR_REF		(10)
#define INT2_LO_PLL_SR_LOCF		(11)
#define INT2_LO_PLL_SR_LOLF		(12)
#define INT2_LO_PIT0_PIF		(13)
#define INT2_LO_PIT1_PIF		(14)
#define INT2_LO_PIT2_PIF		(15)
#define INT2_LO_PIT3_PIF		(16)
#define INT2_LO_USBOTG_USBSTS		(17)
#define INT2_LO_USBH_USBSTS		(18)
/* not used 19-20 */
#define INT2_LO_SSI0			(21)
#define INT2_LO_SSI1			(22)
#define INT2_LO_NFC			(23)
/* not used 24-25 */
#define INT2_LO_RTC			(26)
#define INT2_LO_CCM_UOCSR		(27)
#define INT2_LO_RNG_EI			(28)
#define INT2_LO_SIM1_DATA		(29)
#define INT2_LO_SIM1			(30)
#define INT2_LO_SDHC			(31)
/* not used 32-37 */
#define INT2_HI_L2SW_BERR		(38)
#define INT2_HI_L2SW_RXB		(39)
#define INT2_HI_L2SW_RXF		(40)
#define INT2_HI_L2SW_TXB		(41)
#define INT2_HI_L2SW_TXF		(42)
#define INT2_HI_L2SW_QM		(43)
#define INT2_HI_L2SW_OD0		(44)
#define INT2_HI_L2SW_OD1		(45)
#define INT2_HI_L2SW_OD2		(46)
#define INT2_HI_L2SW_LRN		(47)
#define INT2_HI_MACNET0_TS		(48)
#define INT2_HI_MACNET0_WAKE		(49)
#define INT2_HI_MACNET0_PLR		(50)
/* not used 51-54 */
#define INT2_HI_MACNET1_TS		(51)
#define INT2_HI_MACNET1_WAKE		(52)
#define INT2_HI_MACNET1_PLR		(53)

/* Serial Boot Facility (SBF) */
#define SBF_SBFCR_BLDIV(x)		(((x)&0x000F))
#define SBF_SBFCR_FR			(0x0010)

/* Reset Controller Module (RCM) */
#define RCM_RCR_SOFTRST		(0x80)
#define RCM_RCR_FRCRSTOUT		(0x40)

#define RCM_RSR_SOFT			(0x20)
#define RCM_RSR_LOC			(0x10)
#define RCM_RSR_POR			(0x08)
#define RCM_RSR_EXT			(0x04)
#define RCM_RSR_WDR_CORE		(0x02)
#define RCM_RSR_LOL			(0x01)

/* Chip Configuration Module (CCM) */
#define CCM_CCR_BOOTMOD		(0xC000)
#define CCM_CCR_PLLMULT		(0x0FC0)
#define CCM_CCR_BOOTPS			(0x0030)
#define CCM_CCR_BOOTPS_32		(0x0000)
#define CCM_CCR_BOOTPS_16		(0x0020)
#define CCM_CCR_BOOTPS_8		(0x0010)
#define CCM_CCR_BOOTPS_		(0x0000)
#define CCM_CCR_ALESEL			(0x0008)
#define CCM_CCR_OSCMOD			(0x0004)
#define CCM_CCR_PLLMOD			(0x0002)
#define CCM_CCR_BOOTMEM		(0x0001)

#define CCM_CIR_PIN_MASK		(0xFFC0)
#define CCM_CIR_PRN_MASK		(0x003F)
#define CCM_CIR_PIN_MCF54410		(0x9F<<6)
#define CCM_CIR_PIN_MCF54415		(0xA0<<6)
#define CCM_CIR_PIN_MCF54416		(0xA1<<6)
#define CCM_CIR_PIN_MCF54417		(0xA2<<6)
#define CCM_CIR_PIN_MCF54418		(0xA3<<6)

#define CCM_MISCCR_PWM_EXTCLK(x)	(((x)&(0x0003)<<14)
#define CCM_MISCCR_PWM_EXTCLK_MASK	(0x3FFF)
#define CCM_MISCCR_PWM_EXTCLK_TMR0	(0x0000)
#define CCM_MISCCR_PWM_EXTCLK_TMR1	(0x4000)
#define CCM_MISCCR_PWM_EXTCLK_TMR2	(0x8000)
#define CCM_MISCCR_PWM_EXTCLK_TMR3	(0xC000)
#define CCM_MISCCR_LIMP		(0x1000)
#define CCM_MISCCR_BME			(0x0800)
#define CCM_MISCCR_BMT(x)		(((x)&0x0007)<<8)
#define CCM_MISCCR_BMT_65536		(0)
#define CCM_MISCCR_BMT_32768		(1)
#define CCM_MISCCR_BMT_16384		(2)
#define CCM_MISCCR_BMT_8192		(3)
#define CCM_MISCCR_BMT_4096		(4)
#define CCM_MISCCR_BMT_2048		(5)
#define CCM_MISCCR_BMT_1024		(6)
#define CCM_MISCCR_BMT_512		(7)
#define CCM_MISCCR_SDHCSRC		(0x0040)
#define CCM_MISCCR_SSI1SRC		(0x0020)
#define CCM_MISCCR_SSI0SRC		(0x0010)
#define CCM_MISCCR_USBHOC		(0x0008)
#define CCM_MISCCR_USBOOC		(0x0004)
#define CCM_MISCCR_USBPUE		(0x0002)
#define CCM_MISCCR_USBSRC		(0x0001)

#define CCM_CDRH_SSI0DIV(x)		(((x)&0x00FF)<<8)
#define CCM_CDRH_SSI0DIV_MASK		(0x00FF)
#define CCM_CDRH_SSI1DIV(x)		(((x)&0x00FF))
#define CCM_CDRH_SSI1DIV_MASK		(0xFF00)
#define CCM_CDRL_LPDIV(x)		(((x)&0x000F)<<8)
#define CCM_CDRL_LPDIV_MASK		(0xFF0F)
#define CCM_CDR_LPDIV(x)		CCM_CDRL_LPDIV(x)

#define CCM_UOCSR_DPPD			(0x2000)
#define CCM_UOCSR_DMPD			(0x1000)
#define CCM_UOCSR_DRV_VBUS		(0x0800)
#define CCM_UOCSR_CRG_VBUS		(0x0400)
#define CCM_UOCSR_DCR_VBUS		(0x0200)
#define CCM_UOCSR_DPPU			(0x0100)
#define CCM_UOCSR_AVLD			(0x0080)
#define CCM_UOCSR_BVLD			(0x0040)
#define CCM_UOCSR_VVLD			(0x0020)
#define CCM_UOCSR_SEND			(0x0010)
#define CCM_UOCSR_PWRFLT		(0x0008)
#define CCM_UOCSR_WKUP			(0x0004)
#define CCM_UOCSR_UOMIE		(0x0002)
#define CCM_UOCSR_XPDE			(0x0001)

#define CCM_UHCSR_DRV_VBUS		(0x0010)
#define CCM_UHCSR_PWRFLT		(0x0008)
#define CCM_UHCSR_WKUP			(0x0004)
#define CCM_UHCSR_UOMIE		(0x0002)
#define CCM_UHCSR_XPDE			(0x0001)

#define CCM_MISCCR3_TMR_ENET		(0x1000)
#define CCM_MISCCR3_ENETCLK(x)		(((x)&7)<<8)
#define CCM_MISCCR3_ENETCLK_MASK	(0xF8FF)
#define CCM_MISCCR3_ENETCLK_MII	(0x0700)
#define CCM_MISCCR3_ENETCLK_OSC	(0x0600)
#define CCM_MISCCR3_ENETCLK_USB	(0x0500)
#define CCM_MISCCR3_ENETCLK_TMR3	(0x0400)
#define CCM_MISCCR3_ENETCLK_TMR2	(0x0300)
#define CCM_MISCCR3_ENETCLK_TMR1	(0x0200)
#define CCM_MISCCR3_ENETCLK_TMR0	(0x0100)
#define CCM_MISCCR3_ENETCLK_INTBUS	(0x0000)

#define CCM_MISCCR2_EXTCLKBYP		(0x8000)
#define CCM_MISCCR2_DDR2CLK		(0x4000)
#define CCM_MISCCR2_RGPIO_HALF		(0x2000)
#define CCM_MISCCR2_SWTSCR		(0x1000)
#define CCM_MISCCR2_PLLMODE(x)		(((x)&7)<<8)
#define CCM_MISCCR2_PLLMODE_MASK	(0xF8FF)
#define CCM_MISCCR2_DCCBYP		(0x0080)
#define CCM_MISCCR2_DAC1SEL		(0x0040)
#define CCM_MISCCR2_DAC0SEL		(0x0020)
#define CCM_MISCCR2_ADCEN		(0x0010)
#define CCM_MISCCR2_ADC7SEL		(0x0008)
#define CCM_MISCCR2_ADC3SEL		(0x0004)
#define CCM_MISCCR2_FBHALF		(0x0002)
#define CCM_MISCCR2_ULPI		(0x0001)

#define CCM_FNACR_PCR(x)		(((x)&0x0F)<<24)
#define CCM_FNACR_PCR_MASK		(0xF0FFFFFF)
#define CCM_FNACR_MCC(x)		((x)&0xFFFF)
#define CCM_FNACR_MCC_MASK		(0xFFFF0000)

/* General Purpose I/O Module (GPIO) */
#define GPIO_PAR_FBCTL_ALE(x)		(((x)&3)<<6)
#define GPIO_PAR_FBCTL_ALE_MASK	(0x3F)
#define GPIO_PAR_FBCTL_ALE_FB_ALE	(0xC0)
#define GPIO_PAR_FBCTL_ALE_FB_TS	(0x80)
#define GPIO_PAR_FBCTL_ALE_GPIO	(0x00)
#define GPIO_PAR_FBCTL_OE(x)		(((x)&3)<<4)
#define GPIO_PAR_FBCTL_OE_MASK		(0xCF)
#define GPIO_PAR_FBCTL_OE_FB_OE	(0x30)
#define GPIO_PAR_FBCTL_OE_FB_TBST	(0x20)
#define GPIO_PAR_FBCTL_OE_NFC_RE	(0x20)
#define GPIO_PAR_FBCTL_OE_GPIO		(0x00)
#define GPIO_PAR_FBCTL_FBCLK		(0x08)
#define GPIO_PAR_FBCTL_RW		(0x04)
#define GPIO_PAR_FBCTL_TA(x)		((x)&3)
#define GPIO_PAR_FBCTL_TA_MASK		(0xFC)
#define GPIO_PAR_FBCTL_TA_TA		(0x03)
#define GPIO_PAR_FBCTL_TA_NFC_RB	(0x01)
#define GPIO_PAR_FBCTL_TA_GPIO		(0x00)

#define GPIO_PAR_BE_BS3(x)		(((x)&0x03)<<6)
#define GPIO_PAR_BE_BE3_MASK		(0x3F)
#define GPIO_PAR_BE_BE3_BE3		(0xC0)
#define GPIO_PAR_BE_BE3_CS3		(0x80)
#define GPIO_PAR_BE_BE3_FB_A1		(0x40)
#define GPIO_PAR_BE_BE3_NFC_ALE	(0x40)
#define GPIO_PAR_BE_BE3_GPIO		(0x00)
#define GPIO_PAR_BE_BS2(x)		(((x)&0x03)<<4)
#define GPIO_PAR_BE_BE2_MASK		(0xCF)
#define GPIO_PAR_BE_BE2_BE2		(0x30)
#define GPIO_PAR_BE_BE2_CS2		(0x20)
#define GPIO_PAR_BE_BE2_FB_A0		(0x10)
#define GPIO_PAR_BE_BE2_NFC_CLE	(0x10)
#define GPIO_PAR_BE_BE2_GPIO		(0x00)
#define GPIO_PAR_BE_BS1(x)		(((x)&0x03)<<2)
#define GPIO_PAR_BE_BE1_MASK		(0xF3)
#define GPIO_PAR_BE_BE1_BE1		(0x0C)
#define GPIO_PAR_BE_BE1_FB_TSZ1	(0x08)
#define GPIO_PAR_BE_BE1_GPIO		(0x00)
#define GPIO_PAR_BE_BS0(x)		((x)&0x03)
#define GPIO_PAR_BE_BE0_MASK		(0xFC)
#define GPIO_PAR_BE_BE0_BE0		(0x03)
#define GPIO_PAR_BE_BE0_FB_TSZ0	(0x02)
#define GPIO_PAR_BE_BE0_GPIO		(0x00)

#define GPIO_PAR_CS_CS5(x)		(((x)&0x03)<<6)
#define GPIO_PAR_CS_CS5_MASK		(0x3F)
#define GPIO_PAR_CS_CS5_CS5		(0xC0)
#define GPIO_PAR_CS_CS5_DACK1		(0x80)
#define GPIO_PAR_CS_CS5_GPIO		(0x00)
#define GPIO_PAR_CS_CS4(x)		(((x)&0x03)<<4)
#define GPIO_PAR_CS_CS4_MASK		(0xCF)
#define GPIO_PAR_CS_CS4_CS4		(0x30)
#define GPIO_PAR_CS_CS4_DREQ1		(0x20)
#define GPIO_PAR_CS_CS4_GPIO		(0x00)
#define GPIO_PAR_CS_CS1(x)		(((x)&0x03)<<2)
#define GPIO_PAR_CS_CS1_MASK		(0xF3)
#define GPIO_PAR_CS_CS1_CS1		(0x0C)
#define GPIO_PAR_CS_CS1_NFC_CE		(0x04)
#define GPIO_PAR_CS_CS1_GPIO		(0x00)
#define GPIO_PAR_CS_CS0_CS0		(0x01)

#define GPIO_PAR_CANI2C_I2C0SCL(x)	(((x)&0x03)<<6)
#define GPIO_PAR_CANI2C_I2C0SCL_MASK	(0x3F)
#define GPIO_PAR_CANI2C_I2C0SCL_I2C0SCL	(0xC0)
#define GPIO_PAR_CANI2C_I2C0SCL_U8TXD	(0x80)
#define GPIO_PAR_CANI2C_I2C0SCL_CAN0TX	(0x40)
#define GPIO_PAR_CANI2C_I2C0SCL_GPIO	(0x00)
#define GPIO_PAR_CANI2C_I2C0SDA(x)	(((x)&0x03)<<4)
#define GPIO_PAR_CANI2C_I2C0SDA_MASK	(0xCF)
#define GPIO_PAR_CANI2C_I2C0SDA_I2C0SDA	(0x30)
#define GPIO_PAR_CANI2C_I2C0SDA_U8RXD	(0x20)
#define GPIO_PAR_CANI2C_I2C0SDA_CAN0RX	(0x10)
#define GPIO_PAR_CANI2C_I2C0SDA_GPIO	(0x00)
#define GPIO_PAR_CANI2C_CAN1TX(x)	(((x)&0x03)<<2)
#define GPIO_PAR_CANI2C_CAN1TX_MASK	(0xF3)
#define GPIO_PAR_CANI2C_CAN1TX_CAN1TX	(0x0C)
#define GPIO_PAR_CANI2C_CAN1TX_U9TXD	(0x08)
#define GPIO_PAR_CANI2C_CAN1TX_I2C1SCL	(0x04)
#define GPIO_PAR_CANI2C_CAN1TX_GPIO	(0x00)
#define GPIO_PAR_CANI2C_CAN1RX(x)	((x)&0x03)
#define GPIO_PAR_CANI2C_CAN1RX_MASK	(0xFC)
#define GPIO_PAR_CANI2C_CAN1RX_CAN1RX	(0x03)
#define GPIO_PAR_CANI2C_CAN1RX_U9RXD	(0x02)
#define GPIO_PAR_CANI2C_CAN1RX_I2C1SDA	(0x01)
#define GPIO_PAR_CANI2C_CAN1RX_GPIO	(0x00)

#define GPIO_PAR_IRQH_IRQ7		(0x10)
#define GPIO_PAR_IRQH_IRQ4(x)		(((x)&0x03)<<2)
#define GPIO_PAR_IRQH_IRQ4_MASK	(0xF3)
#define GPIO_PAR_IRQH_IRQ4_IRQ4	(0x0C)
#define GPIO_PAR_IRQH_IRQ4_DREQ0	(0x08)
#define GPIO_PAR_IRQH_IRQ4_GPIO	(0x00)
#define GPIO_PAR_IRQH_IRQ1		(0x03)

#define GPIO_PAR_IRQL_IRQ6(x)		(((x)&0x03)<<6)
#define GPIO_PAR_IRQL_IRQ6_MASK	(0x3F)
#define GPIO_PAR_IRQL_IRQ6_IRQ6	(0xC0)
#define GPIO_PAR_IRQL_IRQ6_USBCLKIN	(0x40)
#define GPIO_PAR_IRQL_IRQ6_GPIO	(0x00)
#define GPIO_PAR_IRQL_IRQ3(x)		(((x)&0x03)<<4)
#define GPIO_PAR_IRQL_IRQ3_MASK	(0xCF)
#define GPIO_PAR_IRQL_IRQ3_IRQ3	(0x30)
#define GPIO_PAR_IRQL_IRQ3_DSPI0_PCS3	(0x20)
#define GPIO_PAR_IRQL_IRQ3_USB1_VBUS_EN	(0x10)
#define GPIO_PAR_IRQL_IRQ3_GPIO	(0x00)
#define GPIO_PAR_IRQL_IRQ2(x)		(((x)&0x03)<<2)
#define GPIO_PAR_IRQL_IRQ2_MASK	(0xF3)
#define GPIO_PAR_IRQL_IRQ2_IRQ2	(0x0C)
#define GPIO_PAR_IRQL_IRQ2_DSPI0_PCS2	(0x08)
#define GPIO_PAR_IRQL_IRQ2_USB1_VBUS_OC	(0x04)
#define GPIO_PAR_IRQL_IRQ2_GPIO	(0x00)

#define GPIO_PAR_DSPI0_SIN(x)		(((x)&0x03)<<6)
#define GPIO_PAR_DSPI0_SIN_MASK	(0x3F)
#define GPIO_PAR_DSPI0_SIN_DSPI0SIN	(0xC0)
#define GPIO_PAR_DSPI0_SIN_SBF_DI	(0xC0)
#define GPIO_PAR_DSPI0_SIN_U3RXD	(0x80)
#define GPIO_PAR_DSPI0_SIN_SDHC_CMD	(0x40)
#define GPIO_PAR_DSPI0_SIN_GPIO	(0x00)
#define GPIO_PAR_DSPI0_SOUT(x)		(((x)&0x03)<<4)
#define GPIO_PAR_DSPI0_SOUT_MASK	(0xCF)
#define GPIO_PAR_DSPI0_SOUT_DSPI0SOUT	(0x30)
#define GPIO_PAR_DSPI0_SOUT_SBF_DO	(0x30)
#define GPIO_PAR_DSPI0_SOUT_U3TXD	(0x20)
#define GPIO_PAR_DSPI0_SOUT_SDHC_DAT0	(0x10)
#define GPIO_PAR_DSPI0_SOUT_GPIO	(0x00)
#define GPIO_PAR_DSPI0_SCK(x)		(((x)&0x03)<<2)
#define GPIO_PAR_DSPI0_SCK_MASK	(0xF3)
#define GPIO_PAR_DSPI0_SCK_DSPI0SCK	(0x0C)
#define GPIO_PAR_DSPI0_SCK_SBF_CK	(0x0C)
#define GPIO_PAR_DSPI0_SCK_I2C3SCL	(0x08)
#define GPIO_PAR_DSPI0_SCK_SDHC_CLK	(0x04)
#define GPIO_PAR_DSPI0_SCK_GPIO	(0x00)
#define GPIO_PAR_DSPI0_PCS0(x)		((x)&0x03)
#define GPIO_PAR_DSPI0_PCS0_MASK	(0xFC)
#define GPIO_PAR_DSPI0_PCS0_DSPI0PCS0	(0x03)
#define GPIO_PAR_DSPI0_PCS0_SS		(0x03)
#define GPIO_PAR_DSPI0_PCS0_I2C3SDA	(0x02)
#define GPIO_PAR_DSPI0_PCS0_SDHC_DAT3	(0x01)
#define GPIO_PAR_DSPI0_PCS0_GPIO	(0x00)

#define GPIO_PAR_DSPIOW_DSPI0PSC1	(0x80)
#define GPIO_PAR_DSPIOW_SBF_CS		(0x80)
#define GPIO_PAR_DSPIOW_OWDAT		(((x)&0x03)<<4)
#define GPIO_PAR_DSPIOW_OWDAT_MASK	(0xCF)
#define GPIO_PAR_DSPIOW_OWDAT_OWDAT	(0x30)
#define GPIO_PAR_DSPIOW_OWDAT_DACK0	(0x20)
#define GPIO_PAR_DSPIOW_OWDAT_GPIO	(0x00)

#define GPIO_PAR_TIMER_T3IN(x)		(((x)&0x03)<<6)
#define GPIO_PAR_TIMER_T3IN_MASK	(0x3F)
#define GPIO_PAR_TIMER_T3IN_T3IN	(0xC0)
#define GPIO_PAR_TIMER_T3IN_EXTA3	(0xC0)
#define GPIO_PAR_TIMER_T3IN_T3OUT	(0x80)
#define GPIO_PAR_TIMER_T3IN_USB0_VBUSEN	(0x40)
#define GPIO_PAR_TIMER_T3IN_ULIPI_DIR	(0x40)
#define GPIO_PAR_TIMER_T3IN_GPIO	(0x00)
#define GPIO_PAR_TIMER_T2IN(x)		(((x)&0x03)<<4)
#define GPIO_PAR_TIMER_T2IN_MASK	(0xCF)
#define GPIO_PAR_TIMER_T2IN_T2IN	(0x30)
#define GPIO_PAR_TIMER_T2IN_EXTA2	(0x30)
#define GPIO_PAR_TIMER_T2IN_T2OUT	(0x20)
#define GPIO_PAR_TIMER_T2IN_SDHC_DAT2	(0x10)
#define GPIO_PAR_TIMER_T2IN_GPIO	(0x00)
#define GPIO_PAR_TIMER_T1IN(x)		(((x)&0x03)<<2)
#define GPIO_PAR_TIMER_T1IN_MASK	(0xF3)
#define GPIO_PAR_TIMER_T1IN_T1IN	(0x0C)
#define GPIO_PAR_TIMER_T1IN_EXTA1	(0x0C)
#define GPIO_PAR_TIMER_T1IN_T1OUT	(0x08)
#define GPIO_PAR_TIMER_T1IN_SDHC_DAT1	(0x04)
#define GPIO_PAR_TIMER_T1IN_GPIO	(0x00)
#define GPIO_PAR_TIMER_T0IN(x)		((x)&0x03)
#define GPIO_PAR_TIMER_T0IN_MASK	(0xFC)
#define GPIO_PAR_TIMER_T0IN_T0IN	(0x03)
#define GPIO_PAR_TIMER_T0IN_EXTA0	(0x03)
#define GPIO_PAR_TIMER_T0IN_T0OUT	(0x02)
#define GPIO_PAR_TIMER_T0IN_USBO_VBUSOC	(0x01)
#define GPIO_PAR_TIMER_T0IN_ULPI_NXT	(0x01)
#define GPIO_PAR_TIMER_T0IN_GPIO	(0x00)

#define GPIO_PAR_UART2_U2CTS(x)	(((x)&0x03)<<6)
#define GPIO_PAR_UART2_U2CTS_MASK	(0x3F)
#define GPIO_PAR_UART2_U2CTS_U2CTS	(0xC0)
#define GPIO_PAR_UART2_U2CTS_U6TXD	(0x80)
#define GPIO_PAR_UART2_U2CTS_SSI1_BCLK	(0x40)
#define GPIO_PAR_UART2_U2CTS_GPIO	(0x00)
#define GPIO_PAR_UART2_U2RTS(x)	(((x)&0x03)<<4)
#define GPIO_PAR_UART2_U2RTS_MASK	(0xCF)
#define GPIO_PAR_UART2_U2RTS_U2RTS	(0x30)
#define GPIO_PAR_UART2_U2RTS_U6RXD	(0x20)
#define GPIO_PAR_UART2_U2RTS_SSI1_FS	(0x10)
#define GPIO_PAR_UART2_U2RTS_GPIO	(0x00)
#define GPIO_PAR_UART2_U2RXD(x)	(((x)&0x03)<<2)
#define GPIO_PAR_UART2_U2RXD_MASK	(0xF3)
#define GPIO_PAR_UART2_U2RXD_U2RXD	(0x0C)
#define GPIO_PAR_UART2_U2RXD_PWM_A3	(0x08)
#define GPIO_PAR_UART2_U2RXD_SSI1_RXD	(0x04)
#define GPIO_PAR_UART2_U2RXD_GPIO	(0x00)
#define GPIO_PAR_UART2_U2TXD(x)	((x)&0x03)
#define GPIO_PAR_UART2_U2TXD_MASK	(0xFC)
#define GPIO_PAR_UART2_U2TXD_U2TXD	(0x03)
#define GPIO_PAR_UART2_U2TXD_PWM_B3	(0x02)
#define GPIO_PAR_UART2_U2TXD_SSI1_TXD	(0x01)
#define GPIO_PAR_UART2_U2TXD_GPIO	(0x00)

#define GPIO_PAR_UART1_U1CTS(x)	(((x)&0x03)<<6)
#define GPIO_PAR_UART1_U1CTS_MASK	(0x3F)
#define GPIO_PAR_UART1_U1CTS_U1CTS	(0xC0)
#define GPIO_PAR_UART1_U1CTS_U5TXD	(0x80)
#define GPIO_PAR_UART1_U1CTS_DSPI3_SCK	(0x40)
#define GPIO_PAR_UART1_U1CTS_GPIO	(0x00)
#define GPIO_PAR_UART1_U1RTS(x)	(((x)&0x03)<<4)
#define GPIO_PAR_UART1_U1RTS_MASK	(0xCF)
#define GPIO_PAR_UART1_U1RTS_U1RTS	(0x30)
#define GPIO_PAR_UART1_U1RTS_U5RXD	(0x20)
#define GPIO_PAR_UART1_U1RTS_DSPI3_PCS0	(0x10)
#define GPIO_PAR_UART1_U1RTS_GPIO	(0x00)
#define GPIO_PAR_UART1_U1RXD(x)	(((x)&0x03)<<2)
#define GPIO_PAR_UART1_U1RXD_MASK	(0xF3)
#define GPIO_PAR_UART1_U1RXD_U1RXD	(0x0C)
#define GPIO_PAR_UART1_U1RXD_I2C5SDA	(0x08)
#define GPIO_PAR_UART1_U1RXD_DSPI3_SIN	(0x04)
#define GPIO_PAR_UART1_U1RXD_GPIO	(0x00)
#define GPIO_PAR_UART1_U1TXD(x)	((x)&0x03)
#define GPIO_PAR_UART1_U1TXD_MASK	(0xFC)
#define GPIO_PAR_UART1_U1TXD_U1TXD	(0x03)
#define GPIO_PAR_UART1_U1TXD_I2C5SCL	(0x02)
#define GPIO_PAR_UART1_U1TXD_DSPI3_SOUT	(0x01)
#define GPIO_PAR_UART1_U1TXD_GPIO	(0x00)

#define GPIO_PAR_UART0_U0CTS(x)	(((x)&0x03)<<6)
#define GPIO_PAR_UART0_U0CTS_MASK	(0x3F)
#define GPIO_PAR_UART0_U0CTS_U0CTS	(0xC0)
#define GPIO_PAR_UART0_U0CTS_U4TXD	(0x80)
#define GPIO_PAR_UART0_U0CTS_DSPI2_SCK	(0x40)
#define GPIO_PAR_UART0_U0CTS_GPIO	(0x00)
#define GPIO_PAR_UART0_U0RTS(x)	(((x)&0x03)<<4)
#define GPIO_PAR_UART0_U0RTS_MASK	(0xCF)
#define GPIO_PAR_UART0_U0RTS_U0RTS	(0x30)
#define GPIO_PAR_UART0_U0RTS_U4RXD	(0x20)
#define GPIO_PAR_UART0_U0RTS_DSPI2_PCS0	(0x10)
#define GPIO_PAR_UART0_U0RTS_GPIO	(0x00)
#define GPIO_PAR_UART0_U0RXD(x)	(((x)&0x03)<<2)
#define GPIO_PAR_UART0_U0RXD_MASK	(0xF3)
#define GPIO_PAR_UART0_U0RXD_U0RXD	(0x0C)
#define GPIO_PAR_UART0_U0RXD_I2C4SDA	(0x08)
#define GPIO_PAR_UART0_U0RXD_DSPI2_SIN	(0x04)
#define GPIO_PAR_UART0_U0RXD_GPIO	(0x00)
#define GPIO_PAR_UART0_U0TXD(x)	((x)&0x03)
#define GPIO_PAR_UART0_U0TXD_MASK	(0xFC)
#define GPIO_PAR_UART0_U0TXD_U0TXD	(0x03)
#define GPIO_PAR_UART0_U0TXD_I2C4SCL	(0x02)
#define GPIO_PAR_UART0_U0TXD_DSPI2_SOUT	(0x01)
#define GPIO_PAR_UART0_U0TXD_GPIO	(0x00)

#define GPIO_PAR_SDHCH_DAT3(x)		(((x)&0x03)<<6)
#define GPIO_PAR_SDHCH_DAT3_MASK	(0x3F)
#define GPIO_PAR_SDHCH_DAT3_DAT3	(0xC0)
#define GPIO_PAR_SDHCH_DAT3_PWM_A1	(0x80)
#define GPIO_PAR_SDHCH_DAT3_DSPI1_PCS0	(0x40)
#define GPIO_PAR_SDHCH_DAT3_GPIO	(0x00)
#define GPIO_PAR_SDHCH_DAT2(x)		(((x)&0x03)<<4)
#define GPIO_PAR_SDHCH_DAT2_MASK	(0xCF)
#define GPIO_PAR_SDHCH_DAT2_DAT2	(0x30)
#define GPIO_PAR_SDHCH_DAT2_PWM_B1	(0x20)
#define GPIO_PAR_SDHCH_DAT2_DSPI1_PCS2	(0x10)
#define GPIO_PAR_SDHCH_DAT2_GPIO	(0x00)
#define GPIO_PAR_SDHCH_DAT1(x)		(((x)&0x03)<<2)
#define GPIO_PAR_SDHCH_DAT1_MASK	(0xF3)
#define GPIO_PAR_SDHCH_DAT1_DAT1	(0x0C)
#define GPIO_PAR_SDHCH_DAT1_PWM_A2	(0x08)
#define GPIO_PAR_SDHCH_DAT1_DSPI1_PCS1	(0x04)
#define GPIO_PAR_SDHCH_DAT1_GPIO	(0x00)
#define GPIO_PAR_SDHCH_DAT0(x)		((x)&0x03)
#define GPIO_PAR_SDHCH_DAT0_MASK	(0xFC)
#define GPIO_PAR_SDHCH_DAT0_DAT0	(0x03)
#define GPIO_PAR_SDHCH_DAT0_PWM_B2	(0x02)
#define GPIO_PAR_SDHCH_DAT0_DSPI1_SOUT	(0x01)
#define GPIO_PAR_SDHCH_DAT0_GPIO	(0x00)

#define GPIO_PAR_SDHCL_CMD(x)		(((x)&0x03)<<2)
#define GPIO_PAR_SDHCL_CMD_MASK	(0xF3)
#define GPIO_PAR_SDHCL_CMD_CMD		(0x0C)
#define GPIO_PAR_SDHCL_CMD_PWM_A0	(0x08)
#define GPIO_PAR_SDHCL_CMD_DSPI1_SIN	(0x04)
#define GPIO_PAR_SDHCL_CMD_GPIO	(0x00)
#define GPIO_PAR_SDHCL_CLK(x)		((x)&0x03)
#define GPIO_PAR_SDHCL_CLK_MASK	(0xFC)
#define GPIO_PAR_SDHCL_CLK_CLK		(0x03)
#define GPIO_PAR_SDHCL_CLK_PWM_B0	(0x02)
#define GPIO_PAR_SDHCL_CLK_DSPI1_SCK	(0x01)
#define GPIO_PAR_SDHCL_CLK_GPIO	(0x00)

#define GPIO_PAR_SIMP0H_DAT(x)		(((x)&0x03)<<6)
#define GPIO_PAR_SIMP0H_DAT_MASK	(0x3F)
#define GPIO_PAR_SIMP0H_DAT_DAT	(0xC0)
#define GPIO_PAR_SIMP0H_DAT_PWM_FAULT2	(0x80)
#define GPIO_PAR_SIMP0H_DAT_SDHC_DAT7	(0x40)
#define GPIO_PAR_SIMP0H_DAT_GPIO	(0x00)
#define GPIO_PAR_SIMP0H_VEN(x)		(((x)&0x03)<<4)
#define GPIO_PAR_SIMP0H_VEN_MASK	(0xCF)
#define GPIO_PAR_SIMP0H_VEN_VEN	(0x30)
#define GPIO_PAR_SIMP0H_VEN_PWM_FAULT0	(0x20)
#define GPIO_PAR_SIMP0H_VEN_GPIO	(0x00)
#define GPIO_PAR_SIMP0H_RST(x)		(((x)&0x03)<<2)
#define GPIO_PAR_SIMP0H_RST_MASK	(0xF3)
#define GPIO_PAR_SIMP0H_RST_RST	(0x0C)
#define GPIO_PAR_SIMP0H_RST_PWM_FORCE	(0x08)
#define GPIO_PAR_SIMP0H_RST_SDHC_DAT6	(0x04)
#define GPIO_PAR_SIMP0H_RST_GPIO	(0x00)
#define GPIO_PAR_SIMP0H_PD(x)		((x)&0x03)
#define GPIO_PAR_SIMP0H_PD_MASK	(0xFC)
#define GPIO_PAR_SIMP0H_PD_PD		(0x03)
#define GPIO_PAR_SIMP0H_PD_PWM_SYNC	(0x02)
#define GPIO_PAR_SIMP0H_PD_SDHC_DAT5	(0x01)
#define GPIO_PAR_SIMP0H_PD_GPIO	(0x00)

#define GPIO_PAR_SIMP0L_CLK(x)		((x)&0x03)
#define GPIO_PAR_SIMP0L_CLK_MASK	(0xFC)
#define GPIO_PAR_SIMP0L_CLK_CLK	(0x03)
#define GPIO_PAR_SIMP0L_CLK_PWM_FAULT1	(0x02)
#define GPIO_PAR_SIMP0L_CLK_SDHC_DAT4	(0x01)
#define GPIO_PAR_SIMP0L_CLK_GPIO	(0x00)

#define GPIO_PAR_SSI0H_RXD(x)		(((x)&0x03)<<6)
#define GPIO_PAR_SSI0H_RXD_MASK	(0x3F)
#define GPIO_PAR_SSI0H_RXD_RXD		(0xC0)
#define GPIO_PAR_SSI0H_RXD_I2C2SDA	(0x80)
#define GPIO_PAR_SSI0H_RXD_SIM1_VEN	(0x40)
#define GPIO_PAR_SSI0H_RXD_GPIO	(0x00)
#define GPIO_PAR_SSI0H_TXD(x)		(((x)&0x03)<<4)
#define GPIO_PAR_SSI0H_TXD_MASK	(0xCF)
#define GPIO_PAR_SSI0H_TXD_TXD		(0x30)
#define GPIO_PAR_SSI0H_TXD_I2C2SCL	(0x20)
#define GPIO_PAR_SSI0H_TXD_SIM1_DAT	(0x10)
#define GPIO_PAR_SSI0H_TXD_GPIO	(0x00)
#define GPIO_PAR_SSI0H_FS(x)		(((x)&0x03)<<2)
#define GPIO_PAR_SSI0H_FS_MASK		(0xF3)
#define GPIO_PAR_SSI0H_FS_FS		(0x0C)
#define GPIO_PAR_SSI0H_FS_U7TXD	(0x08)
#define GPIO_PAR_SSI0H_FS_SIM1_RST	(0x04)
#define GPIO_PAR_SSI0H_FS_GPIO		(0x00)
#define GPIO_PAR_SSI0H_MCLK(x)		((x)&0x03)
#define GPIO_PAR_SSI0H_MCLK_MASK	(0xFC)
#define GPIO_PAR_SSI0H_MCLK_MCLK	(0x03)
#define GPIO_PAR_SSI0H_MCLK_SSI_CLKIN	(0x02)
#define GPIO_PAR_SSI0H_MCLK_SIM1_CLK	(0x01)
#define GPIO_PAR_SSI0H_MCLK_GPIO	(0x00)

#define GPIO_PAR_SSI0L_BCLK(x)		((x)&0x03)
#define GPIO_PAR_SSI0L_BCLK_MASK	(0xFC)
#define GPIO_PAR_SSI0L_BCLK_BCLK	(0x03)
#define GPIO_PAR_SSI0L_BCLK_U7RXD	(0x02)
#define GPIO_PAR_SSI0L_BCLK_SIM1_PD	(0x01)
#define GPIO_PAR_SSI0L_BCLK_GPIO	(0x00)

#define GPIO_PAR_DEBUGH1_DAT3		(0x40)
#define GPIO_PAR_DEBUGH1_DAT2		(0x10)
#define GPIO_PAR_DEBUGH1_DAT1		(0x04)
#define GPIO_PAR_DEBUGH1_DAT0		(0x01)

#define GPIO_PAR_DEBUGH0_PST3		(0x40)
#define GPIO_PAR_DEBUGH0_PST2		(0x10)
#define GPIO_PAR_DEBUGH0_PST1		(0x04)
#define GPIO_PAR_DEBUGH0_PST0		(0x01)

#define GPIO_PODR_G4_VAL		(0x01 << 4)
#define GPIO_PODR_G4_MASK		(0xff & ~GPIO_PODR_G4_VAL)
#define GPIO_PDDR_G4_OUTPUT		(0x01 << 4)
#define GPIO_PDDR_G4_MASK		(0xff & ~GPIO_PDDR_G4_OUTPUT)

#define GPIO_PAR_DEBUGL_ALLPST		(0x01)

#define GPIO_PAR_FEC_FEC(x)		((x)&0x0F)
#define GPIO_PAR_FEC_FEC_MASK		(0xF0)
#define GPIO_PAR_FEC_FEC_GPIO		(0x0D)
#define GPIO_PAR_FEC_FEC_RMII1		(0x0C)
#define GPIO_PAR_FEC_FEC_RMII1FUL	(0x0B)
#define GPIO_PAR_FEC_FEC_RMII_ULPI	(0x0A)
#define GPIO_PAR_FEC_FEC_RMII0		(0x09)
#define GPIO_PAR_FEC_FEC_RMII0FUL_ULPI	(0x08)
#define GPIO_PAR_FEC_FEC_RMII0FUL	(0x07)
#define GPIO_PAR_FEC_FEC_RMII0_1FUL	(0x06)
#define GPIO_PAR_FEC_FEC_RMII0FUL_1	(0x05)	/* 0:Full 1: */
/* Both 0&1: MDC, MDIO, COL & TXER - GPIO */
#define GPIO_PAR_FEC_FEC_RMII0_1	(0x04)
#define GPIO_PAR_FEC_FEC_RMII0FUL_1FUL	(0x03)
#define GPIO_PAR_FEC_FEC_MII		(0x01)	/* MDC & MDIO - GPIO */
#define GPIO_PAR_FEC_FEC_MIIFUL	(0x00)

/* TC: Need to edit here.... */

/* Mode Select Control */
#define GPIO_MSCR_SDRAM_MSC(x)		((x)&0x03)
#define GPIO_MSCR_SDRAM_MSC_MASK	(0xFC)

/* Slew Rate Control */

#define GPIO_SRCR_FB3_FB3(x)		((x)&0x03)
#define GPIO_SRCR_FB3_FB3_MASK		(0xFC)

#define GPIO_SRCR_FB2_FB2(x)		((x)&0x03)
#define GPIO_SRCR_FB2_FB2_MASK		(0xFC)

#define GPIO_SRCR_FB1_FB1(x)		((x)&0x03)
#define GPIO_SRCR_FB1_FB1_MASK		(0xFC)

#define GPIO_SRCR_FB4_FB5(x)		(((x)&0x03)<<2)
#define GPIO_SRCR_FB4_FB5_MASK		(0xF3)
#define GPIO_SRCR_FB4_FB4(x)		((x)&0x03)
#define GPIO_SRCR_FB4_FB4_MASK		(0xFC)

#define GPIO_SRCR_DSPIOW_OWDAT(x)	(((x)&0x03)<<4)
#define GPIO_SRCR_DSPIOW_OWDAT_MASK	(0xCF)
#define GPIO_SRCR_DSPIOW_DSPI0(x)	((x)&0x03)
#define GPIO_SRCR_DSPIOW_DSPI0_MASK	(0xFC)

#define GPIO_SRCR_CANI2C_CAN1(x)	(((x)&0x03)<<2)
#define GPIO_SRCR_CANI2C_CAN1_MASK	(0xF3)
#define GPIO_SRCR_CANI2C_I2C0(x)	((x)&0x03)
#define GPIO_SRCR_CANI2C_I2C0_MASK	(0xFC)

#define GPIO_SRCR_IRQ0_IRQ0(x)		((x)&0x03)
#define GPIO_SRCR_IRQ0_IRQ0_MASK	(0xFC)

#define GPIO_SRCR_TIMER_TMR3(x)	(((x)&0x03)<<6)
#define GPIO_SRCR_TIMER_TMR3_MASK	(0x3F)
#define GPIO_SRCR_TIMER_TMR2(x)	(((x)&0x03)<<4)
#define GPIO_SRCR_TIMER_TMR2_MASK	(0xCF)
#define GPIO_SRCR_TIMER_TMR1(x)	(((x)&0x03)<<2)
#define GPIO_SRCR_TIMER_TMR1_MASK	(0xF3)
#define GPIO_SRCR_TIMER_TMR0(x)	((x)&0x03)
#define GPIO_SRCR_TIMER_TMR0_MASK	(0xFC)

#define GPIO_SRCR_UART_U2(x)		(((x)&0x03)<<4)
#define GPIO_SRCR_UART_U2_MASK		(0xCF)
#define GPIO_SRCR_UART_U1(x)		(((x)&0x03)<<2)
#define GPIO_SRCR_UART_U1_MASK		(0xF3)
#define GPIO_SRCR_UART_U0(x)		((x)&0x03)
#define GPIO_SRCR_UART_U0_MASK		(0xFC)

#define GPIO_SRCR_FEC_RMII0(x)		(((x)&0x03)<<2)
#define GPIO_SRCR_FEC_RMII0_MASK	(0xF3)
#define GPIO_SRCR_FEC_RMII1(x)		((x)&0x03)
#define GPIO_SRCR_FEC_RMII1_MASK	(0xFC)

#define GPIO_SRCR_SDHC_SDHC(x)		((x)&0x03)
#define GPIO_SRCR_SDHC_SDHC_MASK	(0xFC)

#define GPIO_SRCR_SIM0_SIMP0(x)	((x)&0x03)
#define GPIO_SRCR_SIM0_SIMP0_MASK	(0xFC)

#define GPIO_SRCR_SSI0_SSI0(x)		((x)&0x03)
#define GPIO_SRCR_SSI0_SSI0_MASK	(0xFC)

#define GPIO_PCR_URTS_U2		(0x0004)
#define GPIO_PCR_URTS_U1		(0x0002)
#define GPIO_PCR_URTS_U0		(0x0001)

#define GPIO_PCR_UCTS_U2		(0x0004)
#define GPIO_PCR_UCTS_U1		(0x0002)
#define GPIO_PCR_UCTS_U0		(0x0001)

#define GPIO_UTXD_WOM_U9		(0x0200)
#define GPIO_UTXD_WOM_U8		(0x0100)
#define GPIO_UTXD_WOM_U7		(0x0080)
#define GPIO_UTXD_WOM_U6		(0x0040)
#define GPIO_UTXD_WOM_U5		(0x0020)
#define GPIO_UTXD_WOM_U4		(0x0010)
#define GPIO_UTXD_WOM_U3		(0x0008)
#define GPIO_UTXD_WOM_U2		(0x0004)
#define GPIO_UTXD_WOM_U1		(0x0002)
#define GPIO_UTXD_WOM_U0		(0x0001)

#define GPIO_URXD_WOM_U9(x)		(((x)&3)<<18)
#define GPIO_URXD_WOM_U9_MASK		(0xFFF3FFFF)
#define GPIO_URXD_WOM_U8(x)		(((x)&3)<<16)
#define GPIO_URXD_WOM_U8_MASK		(0xFFFCFFFF)
#define GPIO_URXD_WOM_U7(x)		(((x)&3)<<14)
#define GPIO_URXD_WOM_U7_MASK		(0xFFFF3FFF)
#define GPIO_URXD_WOM_U6(x)		(((x)&3)<<12)
#define GPIO_URXD_WOM_U6_MASK		(0xFFFFCFFF)
#define GPIO_URXD_WOM_U5(x)		(((x)&3)<<10)
#define GPIO_URXD_WOM_U5_MASK		(0xFFFFF3FF)
#define GPIO_URXD_WOM_U4(x)		(((x)&3)<<8)
#define GPIO_URXD_WOM_U4_MASK		(0xFFFFFCFF)
#define GPIO_URXD_WOM_U3(x)		(((x)&3)<<6)
#define GPIO_URXD_WOM_U3_MASK		(0xFFFFFF3F)
#define GPIO_URXD_WOM_U2(x)		(((x)&3)<<4)
#define GPIO_URXD_WOM_U2_MASK		(0xFFFFFFCF)
#define GPIO_URXD_WOM_U1(x)		(((x)&3)<<2)
#define GPIO_URXD_WOM_U1_MASK		(0xFFFFFFF3)
#define GPIO_URXD_WOM_U0(x)		((x)&3)
#define GPIO_URXD_WOM_U0_MASK		(0xFFFFFFFC)

#define GPIO_HCR1_PG4_0(x)		(((x)&0x1F)<<27)
#define GPIO_HCR1_PG4_0_MASK		(0x07FFFFFF)
#define GPIO_HCR1_PF7_3(x)		(((x)&0x1F)<<22)
#define GPIO_HCR1_PF7_3_MASK		(0xF83FFFFF)
#define GPIO_HCR1_PE6_0(x)		(((x)&0x7F)<<15)
#define GPIO_HCR1_PE6_0_MASK		(0xFFC07FFF)
#define GPIO_HCR1_PD7_3(x)		(((x)&0x1F)<<10)
#define GPIO_HCR1_PD7_3_MASK		(0xFFFF83FF)
#define GPIO_HCR1_PC7_1(x)		(((x)&0x7F)<<3)
#define GPIO_HCR1_PC7_1_MASK		(0xFFFFFC07)
#define GPIO_HCR1_PB2_0(x)		((x)&7)
#define GPIO_HCR1_PB2_0_MASK		(0xFFFFFFF8)

#define GPIO_HCR0_PK3			(0x00000400)
#define GPIO_HCR0_PK0			(0x00000200)
#define GPIO_HCR0_PD2_0(x)		(((x)&7)<<6)
#define GPIO_HCR0_PD2_0_MASK		(0xFFFFFE3F)
#define GPIO_HCR0_PE7			(0x00000020)
#define GPIO_HCR0_PH7_3(x)		((x)&0x1F)
#define GPIO_HCR0_PH7_3_MASK(x)	(0xFFFFFFE0)

/* SDRAM Controller (SDRAMC) */

/* Phase Locked Loop (PLL) */
#define PLL_CR_LOCIRQ			(0x00040000)
#define PLL_CR_LOCRE			(0x00020000)
#define PLL_CR_LOCEN			(0x00010000)
#define PLL_CR_LOLIRQ			(0x00004000)
#define PLL_CR_LOLRE			(0x00002000)
#define PLL_CR_LOLEN			(0x00001000)
#define PLL_CR_REFDIV(x)		(((x)&7)<<8)
#define PLL_CR_REFDIV_MASK		(0xFFFFF8FF)
#define PLL_CR_FBKDIV(x)		((x)&0x3F)
#define PLL_CR_FBKDIV_MASK		(0xFFFFFFC0)
#define PLL_CR_FBKDIV_BITS		(0x3F)

#define PLL_DR_OUTDIV5(x)		(((x)&0x1F)<<21)
#define PLL_DR_OUTDIV5_MASK		(0xFC1FFFFF)
#define PLL_DR_OUTDIV5_BITS		(0x03E00000)
#define PLL_DR_OUTDIV4(x)		(((x)&0x1F)<<16)
#define PLL_DR_OUTDIV4_MASK		(0xFFE0FFFF)
#define PLL_DR_OUTDIV4_BITS		(0x001F0000)
#define PLL_DR_OUTDIV3(x)		(((x)&0x1F)<<10)
#define PLL_DR_OUTDIV3_MASK		(0xFFFF83FF)
#define PLL_DR_OUTDIV3_BITS		(0x00007C00)
#define PLL_DR_OUTDIV2(x)		(((x)&0x1F)<<5)
#define PLL_DR_OUTDIV2_MASK		(0xFFFFFC1F)
#define PLL_DR_OUTDIV2_BITS		(0x000003E0)
#define PLL_DR_OUTDIV1(x)		((x)&0x1F)
#define PLL_DR_OUTDIV1_MASK		(0xFFFFFFE0)
#define PLL_DR_OUTDIV1_BITS		(0x0000001F)

#define PLL_SR_LOCF			(0x00000200)
#define PLL_SR_LOC			(0x00000100)
#define PLL_SR_LOLF			(0x00000040)
#define PLL_SR_LOCKS			(0x00000020)
#define PLL_SR_LOCK			(0x00000010)
#define PLL_PSR_LOCK			PLL_SR_LOCK	/* compatible with 5x */
#define PLL_SR_MODE(x)			((x)&7)
#define PLL_SR_MODE_MASK		(0xFFFFFFF8)

#endif				/* __MCF5441X__ */