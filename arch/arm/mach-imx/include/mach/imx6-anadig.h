/* SPDX-License-Identifier: GPL-2.0-or-later */
/* SPDX-FileCopyrightText: 2008-2011 Freescale Semiconductor, Inc. */

/* Freescale ANADIG Register Definitions */

#ifndef __ARCH_ARM___ANADIG_H
#define __ARCH_ARM___ANADIG_H

#define HW_ANADIG_PLL_SYS	(0x00000000)
#define HW_ANADIG_PLL_SYS_SET	(0x00000004)
#define HW_ANADIG_PLL_SYS_CLR	(0x00000008)
#define HW_ANADIG_PLL_SYS_TOG	(0x0000000c)

#define BM_ANADIG_PLL_SYS_LOCK 0x80000000
#define BM_ANADIG_PLL_SYS_PLL_SEL 0x00080000
#define BM_ANADIG_PLL_SYS_LVDS_24MHZ_SEL 0x00040000
#define BM_ANADIG_PLL_SYS_LVDS_SEL 0x00020000
#define BM_ANADIG_PLL_SYS_BYPASS 0x00010000
#define BP_ANADIG_PLL_SYS_BYPASS_CLK_SRC      14
#define BM_ANADIG_PLL_SYS_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_PLL_SYS_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_PLL_SYS_BYPASS_CLK_SRC)
#define BV_ANADIG_PLL_SYS_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_PLL_SYS_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_PLL_SYS_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_PLL_SYS_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_PLL_SYS_ENABLE 0x00002000
#define BM_ANADIG_PLL_SYS_POWERDOWN 0x00001000
#define BM_ANADIG_PLL_SYS_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_SYS_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_SYS_HALF_CP 0x00000200
#define BM_ANADIG_PLL_SYS_DOUBLE_LF 0x00000100
#define BM_ANADIG_PLL_SYS_HALF_LF 0x00000080
#define BP_ANADIG_PLL_SYS_DIV_SELECT      0
#define BM_ANADIG_PLL_SYS_DIV_SELECT 0x0000007F
#define BF_ANADIG_PLL_SYS_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_PLL_SYS_DIV_SELECT)

#define HW_ANADIG_USB1_PLL_480_CTRL	(0x00000010)
#define HW_ANADIG_USB1_PLL_480_CTRL_SET	(0x00000014)
#define HW_ANADIG_USB1_PLL_480_CTRL_CLR	(0x00000018)
#define HW_ANADIG_USB1_PLL_480_CTRL_TOG	(0x0000001c)

#define BM_ANADIG_USB1_PLL_480_CTRL_LOCK 0x80000000
#define BM_ANADIG_USB1_PLL_480_CTRL_BYPASS 0x00010000
#define BP_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC      14
#define BM_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC)
#define BV_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_USB1_PLL_480_CTRL_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_USB1_PLL_480_CTRL_ENABLE 0x00002000
#define BM_ANADIG_USB1_PLL_480_CTRL_POWER 0x00001000
#define BM_ANADIG_USB1_PLL_480_CTRL_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_USB1_PLL_480_CTRL_DOUBLE_CP 0x00000400
#define BM_ANADIG_USB1_PLL_480_CTRL_HALF_CP 0x00000200
#define BM_ANADIG_USB1_PLL_480_CTRL_DOUBLE_LF 0x00000100
#define BM_ANADIG_USB1_PLL_480_CTRL_HALF_LF 0x00000080
#define BM_ANADIG_USB1_PLL_480_CTRL_EN_USB_CLKS 0x00000040
#define BP_ANADIG_USB1_PLL_480_CTRL_CONTROL0      2
#define BM_ANADIG_USB1_PLL_480_CTRL_CONTROL0 0x0000001C
#define BF_ANADIG_USB1_PLL_480_CTRL_CONTROL0(v)  (((v) << 2) & BM_ANADIG_USB1_PLL_480_CTRL_CONTROL0)
#define BP_ANADIG_USB1_PLL_480_CTRL_DIV_SELECT      0
#define BM_ANADIG_USB1_PLL_480_CTRL_DIV_SELECT 0x00000003
#define BF_ANADIG_USB1_PLL_480_CTRL_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_USB1_PLL_480_CTRL_DIV_SELECT)

#define HW_ANADIG_USB2_PLL_480_CTRL	(0x00000020)
#define HW_ANADIG_USB2_PLL_480_CTRL_SET	(0x00000024)
#define HW_ANADIG_USB2_PLL_480_CTRL_CLR	(0x00000028)
#define HW_ANADIG_USB2_PLL_480_CTRL_TOG	(0x0000002c)

#define BM_ANADIG_USB2_PLL_480_CTRL_LOCK 0x80000000
#define BM_ANADIG_USB2_PLL_480_CTRL_BYPASS 0x00010000
#define BP_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC      14
#define BM_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC)
#define BV_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_USB2_PLL_480_CTRL_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_USB2_PLL_480_CTRL_ENABLE 0x00002000
#define BM_ANADIG_USB2_PLL_480_CTRL_POWER 0x00001000
#define BM_ANADIG_USB2_PLL_480_CTRL_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_USB2_PLL_480_CTRL_DOUBLE_CP 0x00000400
#define BM_ANADIG_USB2_PLL_480_CTRL_HALF_CP 0x00000200
#define BM_ANADIG_USB2_PLL_480_CTRL_DOUBLE_LF 0x00000100
#define BM_ANADIG_USB2_PLL_480_CTRL_HALF_LF 0x00000080
#define BM_ANADIG_USB2_PLL_480_CTRL_EN_USB_CLKS 0x00000040
#define BP_ANADIG_USB2_PLL_480_CTRL_CONTROL0      2
#define BM_ANADIG_USB2_PLL_480_CTRL_CONTROL0 0x0000001C
#define BF_ANADIG_USB2_PLL_480_CTRL_CONTROL0(v)  (((v) << 2) & BM_ANADIG_USB2_PLL_480_CTRL_CONTROL0)
#define BP_ANADIG_USB2_PLL_480_CTRL_DIV_SELECT      0
#define BM_ANADIG_USB2_PLL_480_CTRL_DIV_SELECT 0x00000003
#define BF_ANADIG_USB2_PLL_480_CTRL_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_USB2_PLL_480_CTRL_DIV_SELECT)

#define HW_ANADIG_PLL_528	(0x00000030)
#define HW_ANADIG_PLL_528_SET	(0x00000034)
#define HW_ANADIG_PLL_528_CLR	(0x00000038)
#define HW_ANADIG_PLL_528_TOG	(0x0000003c)

#define BM_ANADIG_PLL_528_LOCK 0x80000000
#define BM_ANADIG_PLL_528_PFD_OFFSET_EN 0x00040000
#define BM_ANADIG_PLL_528_DITHER_ENABLE 0x00020000
#define BM_ANADIG_PLL_528_BYPASS 0x00010000
#define BP_ANADIG_PLL_528_BYPASS_CLK_SRC      14
#define BM_ANADIG_PLL_528_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_PLL_528_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_PLL_528_BYPASS_CLK_SRC)
#define BV_ANADIG_PLL_528_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_PLL_528_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_PLL_528_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_PLL_528_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_PLL_528_ENABLE 0x00002000
#define BM_ANADIG_PLL_528_POWERDOWN 0x00001000
#define BM_ANADIG_PLL_528_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_528_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_528_HALF_CP 0x00000200
#define BM_ANADIG_PLL_528_DOUBLE_LF 0x00000100
#define BM_ANADIG_PLL_528_HALF_LF 0x00000080
#define BM_ANADIG_PLL_528_DIV_SELECT 0x00000001

#define HW_ANADIG_PLL_528_SS	(0x00000040)

#define BP_ANADIG_PLL_528_SS_STOP      16
#define BM_ANADIG_PLL_528_SS_STOP 0xFFFF0000
#define BF_ANADIG_PLL_528_SS_STOP(v) (((v) << 16) & BM_ANADIG_PLL_528_SS_STOP)
#define BM_ANADIG_PLL_528_SS_ENABLE 0x00008000
#define BP_ANADIG_PLL_528_SS_STEP      0
#define BM_ANADIG_PLL_528_SS_STEP 0x00007FFF
#define BF_ANADIG_PLL_528_SS_STEP(v)  (((v) << 0) & BM_ANADIG_PLL_528_SS_STEP)

#define HW_ANADIG_PLL_528_NUM	(0x00000050)

#define BP_ANADIG_PLL_528_NUM_A      0
#define BM_ANADIG_PLL_528_NUM_A 0x3FFFFFFF
#define BF_ANADIG_PLL_528_NUM_A(v)  (((v) << 0) & BM_ANADIG_PLL_528_NUM_A)

#define HW_ANADIG_PLL_528_DENOM	(0x00000060)

#define BP_ANADIG_PLL_528_DENOM_B      0
#define BM_ANADIG_PLL_528_DENOM_B 0x3FFFFFFF
#define BF_ANADIG_PLL_528_DENOM_B(v)  (((v) << 0) & BM_ANADIG_PLL_528_DENOM_B)

#define HW_ANADIG_PLL_AUDIO	(0x00000070)
#define HW_ANADIG_PLL_AUDIO_SET	(0x00000074)
#define HW_ANADIG_PLL_AUDIO_CLR	(0x00000078)
#define HW_ANADIG_PLL_AUDIO_TOG	(0x0000007c)

#define BM_ANADIG_PLL_AUDIO_LOCK 0x80000000
#define BM_ANADIG_PLL_AUDIO_SSC_EN 0x00200000
#define BP_ANADIG_PLL_AUDIO_TEST_DIV_SELECT      19
#define BM_ANADIG_PLL_AUDIO_TEST_DIV_SELECT 0x00180000
#define BF_ANADIG_PLL_AUDIO_TEST_DIV_SELECT(v)  (((v) << 19) & BM_ANADIG_PLL_AUDIO_TEST_DIV_SELECT)
#define BM_ANADIG_PLL_AUDIO_PFD_OFFSET_EN 0x00040000
#define BM_ANADIG_PLL_AUDIO_DITHER_ENABLE 0x00020000
#define BM_ANADIG_PLL_AUDIO_BYPASS 0x00010000
#define BP_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC      14
#define BM_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC)
#define BV_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_PLL_AUDIO_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_PLL_AUDIO_ENABLE 0x00002000
#define BM_ANADIG_PLL_AUDIO_POWERDOWN 0x00001000
#define BM_ANADIG_PLL_AUDIO_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_AUDIO_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_AUDIO_HALF_CP 0x00000200
#define BM_ANADIG_PLL_AUDIO_DOUBLE_LF 0x00000100
#define BM_ANADIG_PLL_AUDIO_HALF_LF 0x00000080
#define BP_ANADIG_PLL_AUDIO_DIV_SELECT      0
#define BM_ANADIG_PLL_AUDIO_DIV_SELECT 0x0000007F
#define BF_ANADIG_PLL_AUDIO_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_PLL_AUDIO_DIV_SELECT)

#define HW_ANADIG_PLL_AUDIO_NUM	(0x00000080)

#define BP_ANADIG_PLL_AUDIO_NUM_A      0
#define BM_ANADIG_PLL_AUDIO_NUM_A 0x3FFFFFFF
#define BF_ANADIG_PLL_AUDIO_NUM_A(v)  (((v) << 0) & BM_ANADIG_PLL_AUDIO_NUM_A)

#define HW_ANADIG_PLL_AUDIO_DENOM	(0x00000090)

#define BP_ANADIG_PLL_AUDIO_DENOM_B      0
#define BM_ANADIG_PLL_AUDIO_DENOM_B 0x3FFFFFFF
#define BF_ANADIG_PLL_AUDIO_DENOM_B(v)  (((v) << 0) & BM_ANADIG_PLL_AUDIO_DENOM_B)

#define HW_ANADIG_PLL_VIDEO	(0x000000a0)
#define HW_ANADIG_PLL_VIDEO_SET	(0x000000a4)
#define HW_ANADIG_PLL_VIDEO_CLR	(0x000000a8)
#define HW_ANADIG_PLL_VIDEO_TOG	(0x000000ac)

#define BM_ANADIG_PLL_VIDEO_LOCK 0x80000000
#define BM_ANADIG_PLL_VIDEO_SSC_EN 0x00200000
#define BP_ANADIG_PLL_VIDEO_TEST_DIV_SELECT      19
#define BM_ANADIG_PLL_VIDEO_TEST_DIV_SELECT 0x00180000
#define BF_ANADIG_PLL_VIDEO_TEST_DIV_SELECT(v)  (((v) << 19) & BM_ANADIG_PLL_VIDEO_TEST_DIV_SELECT)
#define BM_ANADIG_PLL_VIDEO_PFD_OFFSET_EN 0x00040000
#define BM_ANADIG_PLL_VIDEO_DITHER_ENABLE 0x00020000
#define BM_ANADIG_PLL_VIDEO_BYPASS 0x00010000
#define BP_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC      14
#define BM_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC)
#define BV_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_PLL_VIDEO_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_PLL_VIDEO_ENABLE 0x00002000
#define BM_ANADIG_PLL_VIDEO_POWERDOWN 0x00001000
#define BM_ANADIG_PLL_VIDEO_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_VIDEO_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_VIDEO_HALF_CP 0x00000200
#define BM_ANADIG_PLL_VIDEO_DOUBLE_LF 0x00000100
#define BM_ANADIG_PLL_VIDEO_HALF_LF 0x00000080
#define BP_ANADIG_PLL_VIDEO_DIV_SELECT      0
#define BM_ANADIG_PLL_VIDEO_DIV_SELECT 0x0000007F
#define BF_ANADIG_PLL_VIDEO_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_PLL_VIDEO_DIV_SELECT)

#define HW_ANADIG_PLL_VIDEO_NUM	(0x000000b0)

#define BP_ANADIG_PLL_VIDEO_NUM_A      0
#define BM_ANADIG_PLL_VIDEO_NUM_A 0x3FFFFFFF
#define BF_ANADIG_PLL_VIDEO_NUM_A(v)  (((v) << 0) & BM_ANADIG_PLL_VIDEO_NUM_A)

#define HW_ANADIG_PLL_VIDEO_DENOM	(0x000000c0)

#define BP_ANADIG_PLL_VIDEO_DENOM_B      0
#define BM_ANADIG_PLL_VIDEO_DENOM_B 0x3FFFFFFF
#define BF_ANADIG_PLL_VIDEO_DENOM_B(v)  (((v) << 0) & BM_ANADIG_PLL_VIDEO_DENOM_B)

#define HW_ANADIG_PLL_MLB	(0x000000d0)
#define HW_ANADIG_PLL_MLB_SET	(0x000000d4)
#define HW_ANADIG_PLL_MLB_CLR	(0x000000d8)
#define HW_ANADIG_PLL_MLB_TOG	(0x000000dc)

#define BM_ANADIG_PLL_MLB_LOCK 0x80000000
#define BP_ANADIG_PLL_MLB_MLB_FLT_RES_SEL      26
#define BM_ANADIG_PLL_MLB_MLB_FLT_RES_SEL 0x1C000000
#define BF_ANADIG_PLL_MLB_MLB_FLT_RES_SEL(v)  (((v) << 26) & BM_ANADIG_PLL_MLB_MLB_FLT_RES_SEL)
#define BP_ANADIG_PLL_MLB_RX_CLK_DELAY_CFG      23
#define BM_ANADIG_PLL_MLB_RX_CLK_DELAY_CFG 0x03800000
#define BF_ANADIG_PLL_MLB_RX_CLK_DELAY_CFG(v)  (((v) << 23) & BM_ANADIG_PLL_MLB_RX_CLK_DELAY_CFG)
#define BP_ANADIG_PLL_MLB_VDDD_DELAY_CFG      20
#define BM_ANADIG_PLL_MLB_VDDD_DELAY_CFG 0x00700000
#define BF_ANADIG_PLL_MLB_VDDD_DELAY_CFG(v)  (((v) << 20) & BM_ANADIG_PLL_MLB_VDDD_DELAY_CFG)
#define BP_ANADIG_PLL_MLB_VDDA_DELAY_CFG      17
#define BM_ANADIG_PLL_MLB_VDDA_DELAY_CFG 0x000E0000
#define BF_ANADIG_PLL_MLB_VDDA_DELAY_CFG(v)  (((v) << 17) & BM_ANADIG_PLL_MLB_VDDA_DELAY_CFG)
#define BM_ANADIG_PLL_MLB_BYPASS 0x00010000
#define BP_ANADIG_PLL_MLB_PHASE_SEL      12
#define BM_ANADIG_PLL_MLB_PHASE_SEL 0x00003000
#define BF_ANADIG_PLL_MLB_PHASE_SEL(v)  (((v) << 12) & BM_ANADIG_PLL_MLB_PHASE_SEL)
#define BM_ANADIG_PLL_MLB_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_MLB_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_MLB_HALF_CP 0x00000200

#define HW_ANADIG_PLL_ENET	(0x000000e0)
#define HW_ANADIG_PLL_ENET_SET	(0x000000e4)
#define HW_ANADIG_PLL_ENET_CLR	(0x000000e8)
#define HW_ANADIG_PLL_ENET_TOG	(0x000000ec)

#define BM_ANADIG_PLL_ENET_LOCK 0x80000000
#define BM_ANADIG_PLL_ENET_ENABLE_SATA 0x00100000
#define BM_ANADIG_PLL_ENET_ENABLE_PCIE 0x00080000
#define BM_ANADIG_PLL_ENET_PFD_OFFSET_EN 0x00040000
#define BM_ANADIG_PLL_ENET_DITHER_ENABLE 0x00020000
#define BM_ANADIG_PLL_ENET_BYPASS 0x00010000
#define BP_ANADIG_PLL_ENET_BYPASS_CLK_SRC      14
#define BM_ANADIG_PLL_ENET_BYPASS_CLK_SRC 0x0000C000
#define BF_ANADIG_PLL_ENET_BYPASS_CLK_SRC(v)  (((v) << 14) & BM_ANADIG_PLL_ENET_BYPASS_CLK_SRC)
#define BV_ANADIG_PLL_ENET_BYPASS_CLK_SRC__OSC_24M  0x0
#define BV_ANADIG_PLL_ENET_BYPASS_CLK_SRC__ANACLK_1 0x1
#define BV_ANADIG_PLL_ENET_BYPASS_CLK_SRC__ANACLK_2 0x2
#define BV_ANADIG_PLL_ENET_BYPASS_CLK_SRC__XOR      0x3
#define BM_ANADIG_PLL_ENET_ENABLE 0x00002000
#define BM_ANADIG_PLL_ENET_POWERDOWN 0x00001000
#define BM_ANADIG_PLL_ENET_HOLD_RING_OFF 0x00000800
#define BM_ANADIG_PLL_ENET_DOUBLE_CP 0x00000400
#define BM_ANADIG_PLL_ENET_HALF_CP 0x00000200
#define BM_ANADIG_PLL_ENET_DOUBLE_LF 0x00000100
#define BM_ANADIG_PLL_ENET_HALF_LF 0x00000080
#define BP_ANADIG_PLL_ENET_DIV_SELECT      0
#define BM_ANADIG_PLL_ENET_DIV_SELECT 0x00000003
#define BF_ANADIG_PLL_ENET_DIV_SELECT(v)  (((v) << 0) & BM_ANADIG_PLL_ENET_DIV_SELECT)

#define HW_ANADIG_PFD_480	(0x000000f0)
#define HW_ANADIG_PFD_480_SET	(0x000000f4)
#define HW_ANADIG_PFD_480_CLR	(0x000000f8)
#define HW_ANADIG_PFD_480_TOG	(0x000000fc)

#define BM_ANADIG_PFD_480_PFD3_CLKGATE 0x80000000
#define BM_ANADIG_PFD_480_PFD3_STABLE 0x40000000
#define BP_ANADIG_PFD_480_PFD3_FRAC      24
#define BM_ANADIG_PFD_480_PFD3_FRAC 0x3F000000
#define BF_ANADIG_PFD_480_PFD3_FRAC(v)  (((v) << 24) & BM_ANADIG_PFD_480_PFD3_FRAC)
#define BM_ANADIG_PFD_480_PFD2_CLKGATE 0x00800000
#define BM_ANADIG_PFD_480_PFD2_STABLE 0x00400000
#define BP_ANADIG_PFD_480_PFD2_FRAC      16
#define BM_ANADIG_PFD_480_PFD2_FRAC 0x003F0000
#define BF_ANADIG_PFD_480_PFD2_FRAC(v)  (((v) << 16) & BM_ANADIG_PFD_480_PFD2_FRAC)
#define BM_ANADIG_PFD_480_PFD1_CLKGATE 0x00008000
#define BM_ANADIG_PFD_480_PFD1_STABLE 0x00004000
#define BP_ANADIG_PFD_480_PFD1_FRAC      8
#define BM_ANADIG_PFD_480_PFD1_FRAC 0x00003F00
#define BF_ANADIG_PFD_480_PFD1_FRAC(v)  (((v) << 8) & BM_ANADIG_PFD_480_PFD1_FRAC)
#define BM_ANADIG_PFD_480_PFD0_CLKGATE 0x00000080
#define BM_ANADIG_PFD_480_PFD0_STABLE 0x00000040
#define BP_ANADIG_PFD_480_PFD0_FRAC      0
#define BM_ANADIG_PFD_480_PFD0_FRAC 0x0000003F
#define BF_ANADIG_PFD_480_PFD0_FRAC(v)  (((v) << 0) & BM_ANADIG_PFD_480_PFD0_FRAC)

#define HW_ANADIG_PFD_528	(0x00000100)
#define HW_ANADIG_PFD_528_SET	(0x00000104)
#define HW_ANADIG_PFD_528_CLR	(0x00000108)
#define HW_ANADIG_PFD_528_TOG	(0x0000010c)

#define BM_ANADIG_PFD_528_PFD3_CLKGATE 0x80000000
#define BM_ANADIG_PFD_528_PFD3_STABLE 0x40000000
#define BP_ANADIG_PFD_528_PFD3_FRAC      24
#define BM_ANADIG_PFD_528_PFD3_FRAC 0x3F000000
#define BF_ANADIG_PFD_528_PFD3_FRAC(v)  (((v) << 24) & BM_ANADIG_PFD_528_PFD3_FRAC)
#define BM_ANADIG_PFD_528_PFD2_CLKGATE 0x00800000
#define BM_ANADIG_PFD_528_PFD2_STABLE 0x00400000
#define BP_ANADIG_PFD_528_PFD2_FRAC      16
#define BM_ANADIG_PFD_528_PFD2_FRAC 0x003F0000
#define BF_ANADIG_PFD_528_PFD2_FRAC(v)  (((v) << 16) & BM_ANADIG_PFD_528_PFD2_FRAC)
#define BM_ANADIG_PFD_528_PFD1_CLKGATE 0x00008000
#define BM_ANADIG_PFD_528_PFD1_STABLE 0x00004000
#define BP_ANADIG_PFD_528_PFD1_FRAC      8
#define BM_ANADIG_PFD_528_PFD1_FRAC 0x00003F00
#define BF_ANADIG_PFD_528_PFD1_FRAC(v)  (((v) << 8) & BM_ANADIG_PFD_528_PFD1_FRAC)
#define BM_ANADIG_PFD_528_PFD0_CLKGATE 0x00000080
#define BM_ANADIG_PFD_528_PFD0_STABLE 0x00000040
#define BP_ANADIG_PFD_528_PFD0_FRAC      0
#define BM_ANADIG_PFD_528_PFD0_FRAC 0x0000003F
#define BF_ANADIG_PFD_528_PFD0_FRAC(v)  (((v) << 0) & BM_ANADIG_PFD_528_PFD0_FRAC)

#define HW_ANADIG_REG_1P1	(0x00000110)
#define HW_ANADIG_REG_1P1_SET	(0x00000114)
#define HW_ANADIG_REG_1P1_CLR	(0x00000118)
#define HW_ANADIG_REG_1P1_TOG	(0x0000011c)

#define BM_ANADIG_REG_1P1_OK_VDD1P1 0x00020000
#define BM_ANADIG_REG_1P1_BO_VDD1P1 0x00010000
#define BP_ANADIG_REG_1P1_OUTPUT_TRG      8
#define BM_ANADIG_REG_1P1_OUTPUT_TRG 0x00001F00
#define BF_ANADIG_REG_1P1_OUTPUT_TRG(v)  (((v) << 8) & BM_ANADIG_REG_1P1_OUTPUT_TRG)
#define BP_ANADIG_REG_1P1_BO_OFFSET      4
#define BM_ANADIG_REG_1P1_BO_OFFSET 0x00000070
#define BF_ANADIG_REG_1P1_BO_OFFSET(v)  (((v) << 4) & BM_ANADIG_REG_1P1_BO_OFFSET)
#define BM_ANADIG_REG_1P1_ENABLE_PULLDOWN 0x00000008
#define BM_ANADIG_REG_1P1_ENABLE_ILIMIT 0x00000004
#define BM_ANADIG_REG_1P1_ENABLE_BO 0x00000002
#define BM_ANADIG_REG_1P1_ENABLE_LINREG 0x00000001

#define HW_ANADIG_REG_3P0	(0x00000120)
#define HW_ANADIG_REG_3P0_SET	(0x00000124)
#define HW_ANADIG_REG_3P0_CLR	(0x00000128)
#define HW_ANADIG_REG_3P0_TOG	(0x0000012c)

#define BM_ANADIG_REG_3P0_OK_VDD3P0 0x00020000
#define BM_ANADIG_REG_3P0_BO_VDD3P0 0x00010000
#define BP_ANADIG_REG_3P0_OUTPUT_TRG      8
#define BM_ANADIG_REG_3P0_OUTPUT_TRG 0x00001F00
#define BF_ANADIG_REG_3P0_OUTPUT_TRG(v)  (((v) << 8) & BM_ANADIG_REG_3P0_OUTPUT_TRG)
#define BM_ANADIG_REG_3P0_VBUS_SEL 0x00000080
#define BP_ANADIG_REG_3P0_BO_OFFSET      4
#define BM_ANADIG_REG_3P0_BO_OFFSET 0x00000070
#define BF_ANADIG_REG_3P0_BO_OFFSET(v)  (((v) << 4) & BM_ANADIG_REG_3P0_BO_OFFSET)
#define BM_ANADIG_REG_3P0_ENABLE_ILIMIT 0x00000004
#define BM_ANADIG_REG_3P0_ENABLE_BO 0x00000002
#define BM_ANADIG_REG_3P0_ENABLE_LINREG 0x00000001

#define HW_ANADIG_REG_2P5	(0x00000130)
#define HW_ANADIG_REG_2P5_SET	(0x00000134)
#define HW_ANADIG_REG_2P5_CLR	(0x00000138)
#define HW_ANADIG_REG_2P5_TOG	(0x0000013c)

#define BM_ANADIG_REG_2P5_ENABLE_WEAK_LINREG 0x00040000
#define BM_ANADIG_REG_2P5_OK_VDD2P5 0x00020000
#define BM_ANADIG_REG_2P5_BO_VDD2P5 0x00010000
#define BP_ANADIG_REG_2P5_OUTPUT_TRG      8
#define BM_ANADIG_REG_2P5_OUTPUT_TRG 0x00001F00
#define BF_ANADIG_REG_2P5_OUTPUT_TRG(v)  (((v) << 8) & BM_ANADIG_REG_2P5_OUTPUT_TRG)
#define BP_ANADIG_REG_2P5_BO_OFFSET      4
#define BM_ANADIG_REG_2P5_BO_OFFSET 0x00000070
#define BF_ANADIG_REG_2P5_BO_OFFSET(v)  (((v) << 4) & BM_ANADIG_REG_2P5_BO_OFFSET)
#define BM_ANADIG_REG_2P5_ENABLE_PULLDOWN 0x00000008
#define BM_ANADIG_REG_2P5_ENABLE_ILIMIT 0x00000004
#define BM_ANADIG_REG_2P5_ENABLE_BO 0x00000002
#define BM_ANADIG_REG_2P5_ENABLE_LINREG 0x00000001

#define HW_ANADIG_REG_CORE	(0x00000140)
#define HW_ANADIG_REG_CORE_SET	(0x00000144)
#define HW_ANADIG_REG_CORE_CLR	(0x00000148)
#define HW_ANADIG_REG_CORE_TOG	(0x0000014c)

#define BM_ANADIG_REG_CORE_REF_SHIFT 0x80000000
#define BM_ANADIG_REG_CORE_FET_ODRIVE 0x20000000
#define BP_ANADIG_REG_CORE_RAMP_RATE      27
#define BM_ANADIG_REG_CORE_RAMP_RATE 0x18000000
#define BF_ANADIG_REG_CORE_RAMP_RATE(v)  (((v) << 27) & BM_ANADIG_REG_CORE_RAMP_RATE)
#define BP_ANADIG_REG_CORE_REG2_ADJ      23
#define BM_ANADIG_REG_CORE_REG2_ADJ 0x07800000
#define BF_ANADIG_REG_CORE_REG2_ADJ(v)  (((v) << 23) & BM_ANADIG_REG_CORE_REG2_ADJ)
#define BP_ANADIG_REG_CORE_REG2_TRG      18
#define BM_ANADIG_REG_CORE_REG2_TRG 0x007C0000
#define BF_ANADIG_REG_CORE_REG2_TRG(v)  (((v) << 18) & BM_ANADIG_REG_CORE_REG2_TRG)
#define BP_ANADIG_REG_CORE_REG1_ADJ      14
#define BM_ANADIG_REG_CORE_REG1_ADJ 0x0003C000
#define BF_ANADIG_REG_CORE_REG1_ADJ(v)  (((v) << 14) & BM_ANADIG_REG_CORE_REG1_ADJ)
#define BP_ANADIG_REG_CORE_REG1_TRG      9
#define BM_ANADIG_REG_CORE_REG1_TRG 0x00003E00
#define BF_ANADIG_REG_CORE_REG1_TRG(v)  (((v) << 9) & BM_ANADIG_REG_CORE_REG1_TRG)
#define BP_ANADIG_REG_CORE_REG0_ADJ      5
#define BM_ANADIG_REG_CORE_REG0_ADJ 0x000001E0
#define BF_ANADIG_REG_CORE_REG0_ADJ(v)  (((v) << 5) & BM_ANADIG_REG_CORE_REG0_ADJ)
#define BP_ANADIG_REG_CORE_REG0_TRG      0
#define BM_ANADIG_REG_CORE_REG0_TRG 0x0000001F
#define BF_ANADIG_REG_CORE_REG0_TRG(v)  (((v) << 0) & BM_ANADIG_REG_CORE_REG0_TRG)

#define HW_ANADIG_ANA_MISC0	(0x00000150)
#define HW_ANADIG_ANA_MISC0_SET	(0x00000154)
#define HW_ANADIG_ANA_MISC0_CLR	(0x00000158)
#define HW_ANADIG_ANA_MISC0_TOG	(0x0000015c)

#define BP_ANADIG_ANA_MISC0_CLKGATE_DELAY      26
#define BM_ANADIG_ANA_MISC0_CLKGATE_DELAY 0x1C000000
#define BF_ANADIG_ANA_MISC0_CLKGATE_DELAY(v)  (((v) << 26) & BM_ANADIG_ANA_MISC0_CLKGATE_DELAY)
#define BM_ANADIG_ANA_MISC0_CLKGATE_CTRL 0x02000000
#define BP_ANADIG_ANA_MISC0_ANAMUX      21
#define BM_ANADIG_ANA_MISC0_ANAMUX 0x01E00000
#define BF_ANADIG_ANA_MISC0_ANAMUX(v)  (((v) << 21) & BM_ANADIG_ANA_MISC0_ANAMUX)
#define BM_ANADIG_ANA_MISC0_ANAMUX_EN 0x00100000
#define BP_ANADIG_ANA_MISC0_WBCP_VPW_THRESH      18
#define BM_ANADIG_ANA_MISC0_WBCP_VPW_THRESH 0x000C0000
#define BF_ANADIG_ANA_MISC0_WBCP_VPW_THRESH(v)  (((v) << 18) & BM_ANADIG_ANA_MISC0_WBCP_VPW_THRESH)
#define BM_ANADIG_ANA_MISC0_OSC_XTALOK_EN 0x00020000
#define BM_ANADIG_ANA_MISC0_OSC_XTALOK 0x00010000
#define BP_ANADIG_ANA_MISC0_OSC_I      14
#define BM_ANADIG_ANA_MISC0_OSC_I 0x0000C000
#define BF_ANADIG_ANA_MISC0_OSC_I(v)  (((v) << 14) & BM_ANADIG_ANA_MISC0_OSC_I)
#define BM_ANADIG_ANA_MISC0_RTC_RINGOSC_EN 0x00002000
#define BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG 0x00001000
#define BP_ANADIG_ANA_MISC0_REFTOP_BIAS_TST      8
#define BM_ANADIG_ANA_MISC0_REFTOP_BIAS_TST 0x00000300
#define BF_ANADIG_ANA_MISC0_REFTOP_BIAS_TST(v)  (((v) << 8) & BM_ANADIG_ANA_MISC0_REFTOP_BIAS_TST)
#define BM_ANADIG_ANA_MISC0_REFTOP_VBGUP 0x00000080
#define BP_ANADIG_ANA_MISC0_REFTOP_VBGADJ      4
#define BM_ANADIG_ANA_MISC0_REFTOP_VBGADJ 0x00000070
#define BF_ANADIG_ANA_MISC0_REFTOP_VBGADJ(v)  (((v) << 4) & BM_ANADIG_ANA_MISC0_REFTOP_VBGADJ)
#define BM_ANADIG_ANA_MISC0_REFTOP_SELBIASOFF 0x00000008
#define BM_ANADIG_ANA_MISC0_REFTOP_LOWPOWER 0x00000004
#define BM_ANADIG_ANA_MISC0_REFTOP_PWDVBGUP 0x00000002
#define BM_ANADIG_ANA_MISC0_REFTOP_PWD 0x00000001

#define HW_ANADIG_ANA_MISC1	(0x00000160)
#define HW_ANADIG_ANA_MISC1_SET	(0x00000164)
#define HW_ANADIG_ANA_MISC1_CLR	(0x00000168)
#define HW_ANADIG_ANA_MISC1_TOG	(0x0000016c)

#define BM_ANADIG_ANA_MISC1_IRQ_DIG_BO 0x80000000
#define BM_ANADIG_ANA_MISC1_IRQ_ANA_BO 0x40000000
#define BM_ANADIG_ANA_MISC1_IRQ_TEMPSENSE_BO 0x20000000
#define BM_ANADIG_ANA_MISC1_LVDSCLK2_IBEN 0x00002000
#define BM_ANADIG_ANA_MISC1_LVDSCLK1_IBEN 0x00001000
#define BM_ANADIG_ANA_MISC1_LVDSCLK2_OBEN 0x00000800
#define BM_ANADIG_ANA_MISC1_LVDSCLK1_OBEN 0x00000400
#define BP_ANADIG_ANA_MISC1_LVDS2_CLK_SEL      5
#define BM_ANADIG_ANA_MISC1_LVDS2_CLK_SEL 0x000003E0
#define BF_ANADIG_ANA_MISC1_LVDS2_CLK_SEL(v)  (((v) << 5) & BM_ANADIG_ANA_MISC1_LVDS2_CLK_SEL)
#define BP_ANADIG_ANA_MISC1_LVDS1_CLK_SEL      0
#define BM_ANADIG_ANA_MISC1_LVDS1_CLK_SEL 0x0000001F
#define BF_ANADIG_ANA_MISC1_LVDS1_CLK_SEL(v)  (((v) << 0) & BM_ANADIG_ANA_MISC1_LVDS1_CLK_SEL)

#define HW_ANADIG_ANA_MISC2	(0x00000170)
#define HW_ANADIG_ANA_MISC2_SET	(0x00000174)
#define HW_ANADIG_ANA_MISC2_CLR	(0x00000178)
#define HW_ANADIG_ANA_MISC2_TOG	(0x0000017c)

#define BP_ANADIG_ANA_MISC2_CONTROL3      30
#define BM_ANADIG_ANA_MISC2_CONTROL3 0xC0000000
#define BF_ANADIG_ANA_MISC2_CONTROL3(v) (((v) << 30) & BM_ANADIG_ANA_MISC2_CONTROL3)
#define BP_ANADIG_ANA_MISC2_REG2_STEP_TIME      28
#define BM_ANADIG_ANA_MISC2_REG2_STEP_TIME 0x30000000
#define BF_ANADIG_ANA_MISC2_REG2_STEP_TIME(v)  (((v) << 28) & BM_ANADIG_ANA_MISC2_REG2_STEP_TIME)
#define BP_ANADIG_ANA_MISC2_REG1_STEP_TIME      26
#define BM_ANADIG_ANA_MISC2_REG1_STEP_TIME 0x0C000000
#define BF_ANADIG_ANA_MISC2_REG1_STEP_TIME(v)  (((v) << 26) & BM_ANADIG_ANA_MISC2_REG1_STEP_TIME)
#define BP_ANADIG_ANA_MISC2_REG0_STEP_TIME      24
#define BM_ANADIG_ANA_MISC2_REG0_STEP_TIME 0x03000000
#define BF_ANADIG_ANA_MISC2_REG0_STEP_TIME(v)  (((v) << 24) & BM_ANADIG_ANA_MISC2_REG0_STEP_TIME)
#define BM_ANADIG_ANA_MISC2_CONTROL2 0x00800000
#define BM_ANADIG_ANA_MISC2_REG2_OK 0x00400000
#define BM_ANADIG_ANA_MISC2_REG2_ENABLE_BO 0x00200000
#define BM_ANADIG_ANA_MISC2_REG2_BO_STATUS 0x00080000
#define BP_ANADIG_ANA_MISC2_REG2_BO_OFFSET      16
#define BM_ANADIG_ANA_MISC2_REG2_BO_OFFSET 0x00070000
#define BF_ANADIG_ANA_MISC2_REG2_BO_OFFSET(v)  (((v) << 16) & BM_ANADIG_ANA_MISC2_REG2_BO_OFFSET)
#define BM_ANADIG_ANA_MISC2_CONTROL1 0x00008000
#define BM_ANADIG_ANA_MISC2_REG1_OK 0x00004000
#define BM_ANADIG_ANA_MISC2_REG1_ENABLE_BO 0x00002000
#define BM_ANADIG_ANA_MISC2_REG1_BO_STATUS 0x00000800
#define BP_ANADIG_ANA_MISC2_REG1_BO_OFFSET      8
#define BM_ANADIG_ANA_MISC2_REG1_BO_OFFSET 0x00000700
#define BF_ANADIG_ANA_MISC2_REG1_BO_OFFSET(v)  (((v) << 8) & BM_ANADIG_ANA_MISC2_REG1_BO_OFFSET)
#define BM_ANADIG_ANA_MISC2_CONTROL0 0x00000080
#define BM_ANADIG_ANA_MISC2_REG0_OK 0x00000040
#define BM_ANADIG_ANA_MISC2_REG0_ENABLE_BO 0x00000020
#define BM_ANADIG_ANA_MISC2_REG0_BO_STATUS 0x00000008
#define BP_ANADIG_ANA_MISC2_REG0_BO_OFFSET      0
#define BM_ANADIG_ANA_MISC2_REG0_BO_OFFSET 0x00000007
#define BF_ANADIG_ANA_MISC2_REG0_BO_OFFSET(v)  (((v) << 0) & BM_ANADIG_ANA_MISC2_REG0_BO_OFFSET)

#define HW_ANADIG_TEMPSENSE0	(0x00000180)
#define HW_ANADIG_TEMPSENSE0_SET	(0x00000184)
#define HW_ANADIG_TEMPSENSE0_CLR	(0x00000188)
#define HW_ANADIG_TEMPSENSE0_TOG	(0x0000018c)

#define BP_ANADIG_TEMPSENSE0_ALARM_VALUE      20
#define BM_ANADIG_TEMPSENSE0_ALARM_VALUE 0xFFF00000
#define BF_ANADIG_TEMPSENSE0_ALARM_VALUE(v) (((v) << 20) & BM_ANADIG_TEMPSENSE0_ALARM_VALUE)
#define BP_ANADIG_TEMPSENSE0_TEMP_VALUE      8
#define BM_ANADIG_TEMPSENSE0_TEMP_VALUE 0x000FFF00
#define BF_ANADIG_TEMPSENSE0_TEMP_VALUE(v)  (((v) << 8) & BM_ANADIG_TEMPSENSE0_TEMP_VALUE)
#define BM_ANADIG_TEMPSENSE0_TEST 0x00000040
#define BP_ANADIG_TEMPSENSE0_VBGADJ      3
#define BM_ANADIG_TEMPSENSE0_VBGADJ 0x00000038
#define BF_ANADIG_TEMPSENSE0_VBGADJ(v)  (((v) << 3) & BM_ANADIG_TEMPSENSE0_VBGADJ)
#define BM_ANADIG_TEMPSENSE0_FINISHED 0x00000004
#define BM_ANADIG_TEMPSENSE0_MEASURE_TEMP 0x00000002
#define BM_ANADIG_TEMPSENSE0_POWER_DOWN 0x00000001

#define HW_ANADIG_TEMPSENSE1	(0x00000190)
#define HW_ANADIG_TEMPSENSE1_SET	(0x00000194)
#define HW_ANADIG_TEMPSENSE1_CLR	(0x00000198)
#define HW_ANADIG_TEMPSENSE1_TOG	(0x0000019c)

#define BP_ANADIG_TEMPSENSE1_MEASURE_FREQ      0
#define BM_ANADIG_TEMPSENSE1_MEASURE_FREQ 0x0000FFFF
#define BF_ANADIG_TEMPSENSE1_MEASURE_FREQ(v)  (((v) << 0) & BM_ANADIG_TEMPSENSE1_MEASURE_FREQ)

#define HW_ANADIG_USB1_VBUS_DETECT	(0x000001a0)
#define HW_ANADIG_USB1_VBUS_DETECT_SET	(0x000001a4)
#define HW_ANADIG_USB1_VBUS_DETECT_CLR	(0x000001a8)
#define HW_ANADIG_USB1_VBUS_DETECT_TOG	(0x000001ac)

#define BM_ANADIG_USB1_VBUS_DETECT_EN_CHARGER_RESISTOR 0x80000000
#define BM_ANADIG_USB1_VBUS_DETECT_CHARGE_VBUS 0x08000000
#define BM_ANADIG_USB1_VBUS_DETECT_DISCHARGE_VBUS 0x04000000
#define BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_PWRUP_CMPS 0x00100000
#define BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_5VDETECT 0x00080000
#define BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_TO_B 0x00040000
#define BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_OVERRIDE 0x00000080
#define BM_ANADIG_USB1_VBUS_DETECT_AVALID_OVERRIDE 0x00000040
#define BM_ANADIG_USB1_VBUS_DETECT_BVALID_OVERRIDE 0x00000020
#define BM_ANADIG_USB1_VBUS_DETECT_SESSEND_OVERRIDE 0x00000010
#define BM_ANADIG_USB1_VBUS_DETECT_VBUS_OVERRIDE_EN 0x00000008
#define BP_ANADIG_USB1_VBUS_DETECT_VBUSVALID_THRESH      0
#define BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_THRESH 0x00000007
#define BF_ANADIG_USB1_VBUS_DETECT_VBUSVALID_THRESH(v)  (((v) << 0) & BM_ANADIG_USB1_VBUS_DETECT_VBUSVALID_THRESH)

#define HW_ANADIG_USB1_CHRG_DETECT	(0x000001b0)
#define HW_ANADIG_USB1_CHRG_DETECT_SET	(0x000001b4)
#define HW_ANADIG_USB1_CHRG_DETECT_CLR	(0x000001b8)
#define HW_ANADIG_USB1_CHRG_DETECT_TOG	(0x000001bc)

#define BM_ANADIG_USB1_CHRG_DETECT_BGR_BIAS 0x00800000
#define BM_ANADIG_USB1_CHRG_DETECT_EN_B 0x00100000
#define BM_ANADIG_USB1_CHRG_DETECT_CHK_CHRG_B 0x00080000
#define BM_ANADIG_USB1_CHRG_DETECT_CHK_CONTACT 0x00040000
#define BM_ANADIG_USB1_CHRG_DETECT_FORCE_DETECT 0x00000001

#define HW_ANADIG_USB1_VBUS_DET_STAT	(0x000001c0)
#define HW_ANADIG_USB1_VBUS_DET_STAT_SET	(0x000001c4)
#define HW_ANADIG_USB1_VBUS_DET_STAT_CLR	(0x000001c8)
#define HW_ANADIG_USB1_VBUS_DET_STAT_TOG	(0x000001cc)

#define BM_ANADIG_USB1_VBUS_DET_STAT_VBUS_VALID 0x00000008
#define BM_ANADIG_USB1_VBUS_DET_STAT_AVALID 0x00000004
#define BM_ANADIG_USB1_VBUS_DET_STAT_BVALID 0x00000002
#define BM_ANADIG_USB1_VBUS_DET_STAT_SESSEND 0x00000001

#define HW_ANADIG_USB1_CHRG_DET_STAT	(0x000001d0)
#define HW_ANADIG_USB1_CHRG_DET_STAT_SET	(0x000001d4)
#define HW_ANADIG_USB1_CHRG_DET_STAT_CLR	(0x000001d8)
#define HW_ANADIG_USB1_CHRG_DET_STAT_TOG	(0x000001dc)

#define BM_ANADIG_USB1_CHRG_DET_STAT_DP_STATE 0x00000008
#define BM_ANADIG_USB1_CHRG_DET_STAT_DM_STATE 0x00000004
#define BM_ANADIG_USB1_CHRG_DET_STAT_CHRG_DETECTED 0x00000002
#define BM_ANADIG_USB1_CHRG_DET_STAT_PLUG_CONTACT 0x00000001

#define HW_ANADIG_USB1_LOOPBACK	(0x000001e0)
#define HW_ANADIG_USB1_LOOPBACK_SET	(0x000001e4)
#define HW_ANADIG_USB1_LOOPBACK_CLR	(0x000001e8)
#define HW_ANADIG_USB1_LOOPBACK_TOG	(0x000001ec)

#define BM_ANADIG_USB1_LOOPBACK_UTMO_DIG_TST1 0x00000100
#define BM_ANADIG_USB1_LOOPBACK_UTMO_DIG_TST0 0x00000080
#define BM_ANADIG_USB1_LOOPBACK_TSTI_TX_HIZ 0x00000040
#define BM_ANADIG_USB1_LOOPBACK_TSTI_TX_EN 0x00000020
#define BM_ANADIG_USB1_LOOPBACK_TSTI_TX_LS_MODE 0x00000010
#define BM_ANADIG_USB1_LOOPBACK_TSTI_TX_HS_MODE 0x00000008
#define BM_ANADIG_USB1_LOOPBACK_UTMI_DIG_TST1 0x00000004
#define BM_ANADIG_USB1_LOOPBACK_UTMI_DIG_TST0 0x00000002
#define BM_ANADIG_USB1_LOOPBACK_UTMI_TESTSTART 0x00000001

#define HW_ANADIG_USB1_MISC	(0x000001f0)
#define HW_ANADIG_USB1_MISC_SET	(0x000001f4)
#define HW_ANADIG_USB1_MISC_CLR	(0x000001f8)
#define HW_ANADIG_USB1_MISC_TOG	(0x000001fc)

#define BM_ANADIG_USB1_MISC_EN_CLK_UTMI 0x40000000
#define BM_ANADIG_USB1_MISC_RX_VPIN_FS 0x20000000
#define BM_ANADIG_USB1_MISC_RX_VMIN_FS 0x10000000
#define BM_ANADIG_USB1_MISC_RX_RXD_FS 0x08000000
#define BM_ANADIG_USB1_MISC_RX_SQUELCH 0x04000000
#define BM_ANADIG_USB1_MISC_RX_DISCON_DET 0x02000000
#define BM_ANADIG_USB1_MISC_RX_HS_DATA 0x01000000
#define BM_ANADIG_USB1_MISC_EN_DEGLITCH 0x00000002
#define BM_ANADIG_USB1_MISC_HS_USE_EXTERNAL_R 0x00000001

#define HW_ANADIG_USB2_VBUS_DETECT	(0x00000200)
#define HW_ANADIG_USB2_VBUS_DETECT_SET	(0x00000204)
#define HW_ANADIG_USB2_VBUS_DETECT_CLR	(0x00000208)
#define HW_ANADIG_USB2_VBUS_DETECT_TOG	(0x0000020c)

#define BM_ANADIG_USB2_VBUS_DETECT_EN_CHARGER_RESISTOR 0x80000000
#define BM_ANADIG_USB2_VBUS_DETECT_CHARGE_VBUS 0x08000000
#define BM_ANADIG_USB2_VBUS_DETECT_DISCHARGE_VBUS 0x04000000
#define BM_ANADIG_USB2_VBUS_DETECT_VBUSVALID_PWRUP_CMPS 0x00100000
#define BM_ANADIG_USB2_VBUS_DETECT_VBUSVALID_5VDETECT 0x00080000
#define BM_ANADIG_USB2_VBUS_DETECT_VBUSVALID_TO_B 0x00040000
#define BP_ANADIG_USB2_VBUS_DETECT_VBUSVALID_THRESH      0
#define BM_ANADIG_USB2_VBUS_DETECT_VBUSVALID_THRESH 0x00000007
#define BF_ANADIG_USB2_VBUS_DETECT_VBUSVALID_THRESH(v)  (((v) << 0) & BM_ANADIG_USB2_VBUS_DETECT_VBUSVALID_THRESH)

#define HW_ANADIG_USB2_CHRG_DETECT	(0x00000210)
#define HW_ANADIG_USB2_CHRG_DETECT_SET	(0x00000214)
#define HW_ANADIG_USB2_CHRG_DETECT_CLR	(0x00000218)
#define HW_ANADIG_USB2_CHRG_DETECT_TOG	(0x0000021c)

#define BM_ANADIG_USB2_CHRG_DETECT_BGR_BIAS 0x00800000
#define BM_ANADIG_USB2_CHRG_DETECT_EN_B 0x00100000
#define BM_ANADIG_USB2_CHRG_DETECT_CHK_CHRG_B 0x00080000
#define BM_ANADIG_USB2_CHRG_DETECT_CHK_CONTACT 0x00040000
#define BM_ANADIG_USB2_CHRG_DETECT_FORCE_DETECT 0x00000001

#define HW_ANADIG_USB2_VBUS_DET_STAT	(0x00000220)
#define HW_ANADIG_USB2_VBUS_DET_STAT_SET	(0x00000224)
#define HW_ANADIG_USB2_VBUS_DET_STAT_CLR	(0x00000228)
#define HW_ANADIG_USB2_VBUS_DET_STAT_TOG	(0x0000022c)

#define BM_ANADIG_USB2_VBUS_DET_STAT_VBUS_VALID 0x00000008
#define BM_ANADIG_USB2_VBUS_DET_STAT_AVALID 0x00000004
#define BM_ANADIG_USB2_VBUS_DET_STAT_BVALID 0x00000002
#define BM_ANADIG_USB2_VBUS_DET_STAT_SESSEND 0x00000001

#define HW_ANADIG_USB2_CHRG_DET_STAT	(0x00000230)
#define HW_ANADIG_USB2_CHRG_DET_STAT_SET	(0x00000234)
#define HW_ANADIG_USB2_CHRG_DET_STAT_CLR	(0x00000238)
#define HW_ANADIG_USB2_CHRG_DET_STAT_TOG	(0x0000023c)

#define BM_ANADIG_USB2_CHRG_DET_STAT_DP_STATE 0x00000008
#define BM_ANADIG_USB2_CHRG_DET_STAT_DM_STATE 0x00000004
#define BM_ANADIG_USB2_CHRG_DET_STAT_CHRG_DETECTED 0x00000002
#define BM_ANADIG_USB2_CHRG_DET_STAT_PLUG_CONTACT 0x00000001

#define HW_ANADIG_USB2_LOOPBACK	(0x00000240)
#define HW_ANADIG_USB2_LOOPBACK_SET	(0x00000244)
#define HW_ANADIG_USB2_LOOPBACK_CLR	(0x00000248)
#define HW_ANADIG_USB2_LOOPBACK_TOG	(0x0000024c)

#define BM_ANADIG_USB2_LOOPBACK_UTMO_DIG_TST1 0x00000100
#define BM_ANADIG_USB2_LOOPBACK_UTMO_DIG_TST0 0x00000080
#define BM_ANADIG_USB2_LOOPBACK_TSTI_TX_HIZ 0x00000040
#define BM_ANADIG_USB2_LOOPBACK_TSTI_TX_EN 0x00000020
#define BM_ANADIG_USB2_LOOPBACK_TSTI_TX_LS_MODE 0x00000010
#define BM_ANADIG_USB2_LOOPBACK_TSTI_TX_HS_MODE 0x00000008
#define BM_ANADIG_USB2_LOOPBACK_UTMI_DIG_TST1 0x00000004
#define BM_ANADIG_USB2_LOOPBACK_UTMI_DIG_TST0 0x00000002
#define BM_ANADIG_USB2_LOOPBACK_UTMI_TESTSTART 0x00000001

#define HW_ANADIG_USB2_MISC	(0x00000250)
#define HW_ANADIG_USB2_MISC_SET	(0x00000254)
#define HW_ANADIG_USB2_MISC_CLR	(0x00000258)
#define HW_ANADIG_USB2_MISC_TOG	(0x0000025c)

#define BM_ANADIG_USB2_MISC_EN_CLK_UTMI 0x40000000
#define BM_ANADIG_USB2_MISC_RX_VPIN_FS 0x20000000
#define BM_ANADIG_USB2_MISC_RX_VMIN_FS 0x10000000
#define BM_ANADIG_USB2_MISC_RX_RXD_FS 0x08000000
#define BM_ANADIG_USB2_MISC_RX_SQUELCH 0x04000000
#define BM_ANADIG_USB2_MISC_RX_DISCON_DET 0x02000000
#define BM_ANADIG_USB2_MISC_RX_HS_DATA 0x01000000
#define BM_ANADIG_USB2_MISC_EN_DEGLITCH 0x00000002
#define BM_ANADIG_USB2_MISC_HS_USE_EXTERNAL_R 0x00000001

#define HW_ANADIG_DIGPROG	(0x00000260)

#define BP_ANADIG_DIGPROG_MAJOR      8
#define BM_ANADIG_DIGPROG_MAJOR 0x00FFFF00
#define BF_ANADIG_DIGPROG_MAJOR(v)  (((v) << 8) & BM_ANADIG_DIGPROG_MAJOR)
#define BP_ANADIG_DIGPROG_MINOR      0
#define BM_ANADIG_DIGPROG_MINOR 0x000000FF
#define BF_ANADIG_DIGPROG_MINOR(v)  (((v) << 0) & BM_ANADIG_DIGPROG_MINOR)
#endif /* __ARCH_ARM___ANADIG_H */
