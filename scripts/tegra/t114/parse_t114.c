// SPDX-License-Identifier: GPL-2.0-only
// SPDX-FileCopyrightText: 2012 NVIDIA CORPORATION

/*
 * parse_t114.h - Definitions for the dev/sdram parameters
 */

#include "../parse.h"
#include "nvboot_bct_t114.h"

enum_item s_devtype_table_t114[] = {
	{ "NvBootDevType_Sdmmc", nvboot_dev_type_sdmmc },
	{ "NvBootDevType_Spi", nvboot_dev_type_spi },
	{ "Sdmmc", nvboot_dev_type_sdmmc },
	{ "Spi", nvboot_dev_type_spi },
	{ NULL, 0 }
};

enum_item s_sdmmc_data_width_table_t114[] = {
	{
	  "NvBootSdmmcDataWidth_4Bit",
	  nvboot_sdmmc_data_width_4bit
	},
	{
	  "NvBootSdmmcDataWidth_8Bit",
	  nvboot_sdmmc_data_width_8bit
	},
	{ "4Bit", nvboot_sdmmc_data_width_4bit },
	{ "8Bit", nvboot_sdmmc_data_width_8bit },
	{ NULL, 0 }
};

enum_item s_spi_clock_source_table_t114[] = {
	{ "NvBootSpiClockSource_PllPOut0", nvboot_spi_clock_source_pllp_out0 },
	{ "NvBootSpiClockSource_ClockM", nvboot_spi_clock_source_clockm },
	{ "ClockSource_PllPOut0", nvboot_spi_clock_source_pllp_out0 },
	{ "ClockSource_ClockM", nvboot_spi_clock_source_clockm },
	{ "PllPOut0", nvboot_spi_clock_source_pllp_out0 },
	{ "ClockM", nvboot_spi_clock_source_clockm },
	{ NULL, 0 }
};

enum_item s_nvboot_memory_type_table_t114[] = {
	{ "NvBootMemoryType_None", nvboot_memory_type_none },
	{ "NvBootMemoryType_Ddr3", nvboot_memory_type_ddr3 },
	{ "NvBootMemoryType_Ddr2", nvboot_memory_type_ddr2 },
	{ "NvBootMemoryType_Ddr", nvboot_memory_type_ddr },
	{ "NvBootMemoryType_LpDdr2", nvboot_memory_type_lpddr2 },
	{ "NvBootMemoryType_LpDdr", nvboot_memory_type_lpddr },

	{ "None", nvboot_memory_type_none },
	{ "Ddr3", nvboot_memory_type_ddr3 },
	{ "Ddr2", nvboot_memory_type_ddr2 },
	{ "Ddr", nvboot_memory_type_ddr },
	{ "LpDdr2", nvboot_memory_type_lpddr2 },
	{ "LpDdr", nvboot_memory_type_lpddr },

	{ NULL, 0 }
};

#define TOKEN(name)						\
	token_##name, field_type_u32, NULL

field_item s_sdram_field_table_t114[] = {
	{ "MemoryType", token_memory_type,
	  field_type_enum, s_nvboot_memory_type_table_t114 },

	{ "PllMInputDivider",           TOKEN(pllm_input_divider) },
	{ "PllMFeedbackDivider",        TOKEN(pllm_feedback_divider) },
	{ "PllMStableTime",             TOKEN(pllm_stable_time) },
	{ "PllMSetupControl",           TOKEN(pllm_setup_control) },
	{ "PllMSelectDiv2",             TOKEN(pllm_select_div2) },
	{ "PllMPDLshiftPh45",           TOKEN(pllm_pdlshift_ph45) },
	{ "PllMPDLshiftPh90",           TOKEN(pllm_pdlshift_ph90) },
	{ "PllMPDLshiftPh135",          TOKEN(pllm_pdlshift_ph135) },
	{ "PllMKCP",                    TOKEN(pllm_kcp) },
	{ "PllMKVCO",                   TOKEN(pllm_kvco) },
	{ "EmcBctSpare0",               TOKEN(emc_bct_spare0) },
	{ "EmcAutoCalInterval",         TOKEN(emc_auto_cal_interval) },
	{ "EmcAutoCalConfig",           TOKEN(emc_auto_cal_config) },
	{ "EmcAutoCalConfig2",          TOKEN(emc_auto_cal_config2) },
	{ "EmcAutoCalConfig3",          TOKEN(emc_auto_cal_config3) },
	{ "EmcAutoCalWait",             TOKEN(emc_auto_cal_wait) },
	{ "EmcPinProgramWait",          TOKEN(emc_pin_program_wait) },
	{ "EmcRc",                      TOKEN(emc_rc) },
	{ "EmcRfc",                     TOKEN(emc_rfc) },
	{ "EmcRfcSlr",                  TOKEN(emc_rfc_slr) },
	{ "EmcRas",                     TOKEN(emc_ras) },
	{ "EmcRp",                      TOKEN(emc_rp) },
	{ "EmcR2r",                     TOKEN(emc_r2r) },
	{ "EmcW2w",                     TOKEN(emc_w2w) },
	{ "EmcR2w",                     TOKEN(emc_r2w) },
	{ "EmcW2r",                     TOKEN(emc_w2r) },
	{ "EmcR2p",                     TOKEN(emc_r2p) },
	{ "EmcW2p",                     TOKEN(emc_w2p) },
	{ "EmcRrd",                     TOKEN(emc_rrd) },
	{ "EmcRdRcd",                   TOKEN(emc_rd_rcd) },
	{ "EmcWrRcd",                   TOKEN(emc_wr_rcd) },
	{ "EmcRext",                    TOKEN(emc_rext) },
	{ "EmcWdv",                     TOKEN(emc_wdv) },
	{ "EmcWdvMask",                 TOKEN(emc_wdv_mask) },
	{ "EmcQUseExtra",               TOKEN(emc_quse_extra) },
	{ "EmcQUse",                    TOKEN(emc_quse) },
	{ "EmcIbdly",                   TOKEN(emc_ibdly) },
	{ "EmcEInput",                  TOKEN(emc_einput) },
	{ "EmcEInputDuration",          TOKEN(emc_einput_duration) },
	{ "EmcPutermExtra",             TOKEN(emc_puterm_extra) },
	{ "EmcCdbCntl1",                TOKEN(emc_cdb_cntl1) },
	{ "EmcCdbCntl2",                TOKEN(emc_cdb_cntl2) },
	{ "EmcQRst",                    TOKEN(emc_qrst) },
	{ "EmcQSafe",                   TOKEN(emc_qsafe) },
	{ "EmcRdv",                     TOKEN(emc_rdv) },
	{ "EmcRdvMask",                 TOKEN(emc_rdv_mask) },
	{ "EmcRefresh",                 TOKEN(emc_refresh) },
	{ "EmcBurstRefreshNum",         TOKEN(emc_burst_refresh_num) },
	{ "EmcPdEx2Wr",                 TOKEN(emc_pdex2wr) },
	{ "EmcPdEx2Rd",                 TOKEN(emc_pdex2rd) },
	{ "EmcPChg2Pden",               TOKEN(emc_pchg2pden) },
	{ "EmcAct2Pden",                TOKEN(emc_act2pden) },
	{ "EmcAr2Pden",                 TOKEN(emc_ar2pden) },
	{ "EmcRw2Pden",                 TOKEN(emc_rw2pden) },
	{ "EmcTxsr",                    TOKEN(emc_txsr) },
	{ "EmcTcke",                    TOKEN(emc_tcke) },
	{ "EmcTckesr",                   TOKEN(emc_tckesr) },
	{ "EmcTpd",                     TOKEN(emc_tpd) },
	{ "EmcTfaw",                    TOKEN(emc_tfaw) },
	{ "EmcTrpab",                   TOKEN(emc_trpab) },
	{ "EmcTClkStable",              TOKEN(emc_tclkstable) },
	{ "EmcTClkStop",                TOKEN(emc_tclkstop) },
	{ "EmcTRefBw",                  TOKEN(emc_trefbw) },
	{ "EmcFbioCfg5",                TOKEN(emc_fbio_cfg5) },
	{ "EmcFbioCfg6",                TOKEN(emc_fbio_cfg6) },
	{ "EmcFbioSpare",               TOKEN(emc_fbio_spare) },
	{ "EmcMrsResetDllWait",         TOKEN(emc_mrs_reset_dll_wait) },
	{ "EmcMrsResetDll",             TOKEN(emc_mrs_reset_dll) },
	{ "EmcMrsDdr2DllReset",         TOKEN(emc_mrs_ddr2_dll_reset) },
	{ "EmcMrs",                     TOKEN(emc_mrs) },
	{ "EmcEmrs2",                   TOKEN(emc_emrs2) },
	{ "EmcEmrs3",                   TOKEN(emc_emrs3) },
	{ "EmcEmrsDdr2DllEnable",       TOKEN(emc_emrs_ddr2_dll_enable) },
	{ "EmcEmrsDdr2OcdCalib",        TOKEN(emc_emrs_ddr2_ocd_calib) },
	{ "EmcEmrs",                    TOKEN(emc_emrs) },
	{ "EmcMrw1",                    TOKEN(emc_mrw1) },
	{ "EmcMrw2",                    TOKEN(emc_mrw2) },
	{ "EmcMrw3",                    TOKEN(emc_mrw3) },
	{ "EmcMrw4",                    TOKEN(emc_mrw4) },
	{ "EmcMrwResetCommand",         TOKEN(emc_mrw_reset_command) },
	{ "EmcMrwResetNInitWait",       TOKEN(emc_mrw_reset_ninit_wait) },
	{ "EmcAdrCfg",                  TOKEN(emc_adr_cfg) },
	{ "McEmemCfg",                  TOKEN(mc_emem_cfg) },
	{ "EmcCfg2",                    TOKEN(emc_cfg2) },
	{ "EmcCfgDigDll",               TOKEN(emc_cfg_dig_dll) },
	{ "EmcCfgDigDllPeriod",         TOKEN(emc_cfg_dig_dll_period) },
	{ "EmcCfg",                     TOKEN(emc_cfg) },
	{ "EmcDbg",                     TOKEN(emc_dbg) },
	{ "WarmBootWait",               TOKEN(warm_boot_wait) },
	{ "EmcCttTermCtrl",             TOKEN(emc_ctt_term_ctrl) },
	{ "EmcOdtWrite",                TOKEN(emc_odt_write) },
	{ "EmcOdtRead",                 TOKEN(emc_odt_read) },
	{ "EmcZcalWaitCnt",             TOKEN(emc_zcal_wait_cnt) },
	{ "EmcZcalMrwCmd",              TOKEN(emc_zcal_mrw_cmd) },
	{ "EmcDdr2Wait",                TOKEN(emc_ddr2_wait) },
	{ "PmcDdrPwr",                  TOKEN(pmc_ddr_pwr) },
	{ "EmcClockSource",             TOKEN(emc_clock_source) },
	{ "EmcPinExtraWait",            TOKEN(emc_pin_extra_wait) },
	{ "EmcTimingControlWait",       TOKEN(emc_timing_control_wait) },
	{ "EmcWext",                    TOKEN(emc_wext) },
	{ "EmcCtt",                     TOKEN(emc_ctt) },
	{ "EmcCttDuration",             TOKEN(emc_ctt_duration) },
	{ "EmcPreRefreshReqCnt",        TOKEN(emc_prerefresh_req_cnt) },
	{ "EmcTxsrDll",                 TOKEN(emc_txsr_dll) },
	{ "EmcCfgRsv",                  TOKEN(emc_cfg_rsv) },
	{ "EmcMrwExtra",                TOKEN(emc_mrw_extra) },
	{ "EmcWarmBootMrwExtra",        TOKEN(emc_warm_boot_mrw_extra) },
	{ "EmcWarmBootExtraModeRegWriteEnable",
			TOKEN(emc_warm_boot_extramode_reg_write_enable) },
	{ "EmcExtraModeRegWriteEnable", TOKEN(emc_extramode_reg_write_enable) },
	{ "EmcMrsWaitCnt",              TOKEN(emc_mrs_wait_cnt) },
	{ "EmcMrsWaitCnt2",             TOKEN(emc_mrs_wait_cnt2) },
	{ "EmcCmdQ",                    TOKEN(emc_cmd_q) },
	{ "EmcMc2EmcQ",                 TOKEN(emc_mc2emc_q) },
	{ "EmcDynSelfRefControl",       TOKEN(emc_dyn_self_ref_control) },
	{ "AhbArbitrationXbarCtrlMemInitDone",
			TOKEN(ahb_arbitration_xbar_ctrl_meminit_done) },
	{ "EmcDevSelect",               TOKEN(emc_dev_select) },
	{ "EmcSelDpdCtrl",              TOKEN(emc_sel_dpd_ctrl) },
	{ "EmcDllXformDqs0",            TOKEN(emc_dll_xform_dqs0) },
	{ "EmcDllXformDqs1",            TOKEN(emc_dll_xform_dqs1) },
	{ "EmcDllXformDqs2",            TOKEN(emc_dll_xform_dqs2) },
	{ "EmcDllXformDqs3",            TOKEN(emc_dll_xform_dqs3) },
	{ "EmcDllXformDqs4",            TOKEN(emc_dll_xform_dqs4) },
	{ "EmcDllXformDqs5",            TOKEN(emc_dll_xform_dqs5) },
	{ "EmcDllXformDqs6",            TOKEN(emc_dll_xform_dqs6) },
	{ "EmcDllXformDqs7",            TOKEN(emc_dll_xform_dqs7) },
	{ "EmcDllXformQUse0",           TOKEN(emc_dll_xform_quse0) },
	{ "EmcDllXformQUse1",           TOKEN(emc_dll_xform_quse1) },
	{ "EmcDllXformQUse2",           TOKEN(emc_dll_xform_quse2) },
	{ "EmcDllXformQUse3",           TOKEN(emc_dll_xform_quse3) },
	{ "EmcDllXformQUse4",           TOKEN(emc_dll_xform_quse4) },
	{ "EmcDllXformQUse5",           TOKEN(emc_dll_xform_quse5) },
	{ "EmcDllXformQUse6",           TOKEN(emc_dll_xform_quse6) },
	{ "EmcDllXformQUse7",           TOKEN(emc_dll_xform_quse7) },
	{ "EmcDllXformAddr0",           TOKEN(emc_dll_xform_addr0) },
	{ "EmcDllXformAddr1",           TOKEN(emc_dll_xform_addr1) },
	{ "EmcDllXformAddr2",           TOKEN(emc_dll_xform_addr2) },
	{ "EmcDliTrimTxDqs0",           TOKEN(emc_dli_trim_tx_dqs0) },
	{ "EmcDliTrimTxDqs1",           TOKEN(emc_dli_trim_tx_dqs1) },
	{ "EmcDliTrimTxDqs2",           TOKEN(emc_dli_trim_tx_dqs2) },
	{ "EmcDliTrimTxDqs3",           TOKEN(emc_dli_trim_tx_dqs3) },
	{ "EmcDliTrimTxDqs4",           TOKEN(emc_dli_trim_tx_dqs4) },
	{ "EmcDliTrimTxDqs5",           TOKEN(emc_dli_trim_tx_dqs5) },
	{ "EmcDliTrimTxDqs6",           TOKEN(emc_dli_trim_tx_dqs6) },
	{ "EmcDliTrimTxDqs7",           TOKEN(emc_dli_trim_tx_dqs7) },
	{ "EmcDllXformDq0",             TOKEN(emc_dll_xform_dq0) },
	{ "EmcDllXformDq1",             TOKEN(emc_dll_xform_dq1) },
	{ "EmcDllXformDq2",             TOKEN(emc_dll_xform_dq2) },
	{ "EmcDllXformDq3",             TOKEN(emc_dll_xform_dq3) },
	{ "EmcZcalInterval",            TOKEN(emc_zcal_interval) },
	{ "EmcZcalInitDev0",            TOKEN(emc_zcal_init_dev0) },
	{ "EmcZcalInitDev1",            TOKEN(emc_zcal_init_dev1) },
	{ "EmcZcalInitWait",            TOKEN(emc_zcal_init_wait) },
	{ "EmcZcalWarmColdBootEnables", TOKEN(emc_zcal_warm_cold_boot_enables) },
	{ "EmcMrwLpddr2ZcalWarmBoot",   TOKEN(emc_mrw_lpddr2zcal_warm_boot) },
	{ "EmcZqCalDdr3WarmBoot",       TOKEN(emc_zqcal_ddr3_warm_boot) },
	{ "EmcZcalWarmBootWait",        TOKEN(emc_zcal_warm_boot_wait) },
	{ "EmcMrsWarmBootEnable",       TOKEN(emc_mrs_warm_boot_enable) },
	{ "EmcMrsExtra",                TOKEN(emc_mrs_extra) },
	{ "EmcWarmBootMrsExtra",        TOKEN(emc_warm_boot_mrs_extra) },
	{ "EmcClkenOverride",           TOKEN(emc_clken_override) },
	{ "EmcExtraRefreshNum",         TOKEN(emc_extra_refresh_num) },
	{ "EmcClkenOverrideAllWarmBoot",
			TOKEN(emc_clken_override_allwarm_boot) },
	{ "McClkenOverrideAllWarmBoot", TOKEN(mc_clken_override_allwarm_boot) },
	{ "EmcCfgDigDllPeriodWarmBoot",
			TOKEN(emc_cfg_dig_dll_period_warm_boot) },
	{ "PmcVddpSel",                 TOKEN(pmc_vddp_sel) },
	{ "PmcDdrCfg",                  TOKEN(pmc_ddr_cfg) },
	{ "PmcIoDpdReq",                TOKEN(pmc_io_dpd_req) },
	{ "PmcIoDpd2Req",               TOKEN(pmc_io_dpd2_req) },
	{ "PmcRegShort",                TOKEN(pmc_reg_short) },
	{ "PmcENoVttGen",               TOKEN(pmc_eno_vtt_gen) },
	{ "PmcNoIoPower",               TOKEN(pmc_no_io_power) },
	{ "EmcXm2CmdPadCtrl",           TOKEN(emc_xm2cmd_pad_ctrl) },
	{ "EmcXm2CmdPadCtrl2",          TOKEN(emc_xm2cmd_pad_ctrl2) },
	{ "EmcXm2CmdPadCtrl3",          TOKEN(emc_xm2cmd_pad_ctrl3) },
	{ "EmcXm2CmdPadCtrl4",          TOKEN(emc_xm2cmd_pad_ctrl4) },
	{ "EmcXm2DqsPadCtrl",           TOKEN(emc_xm2dqs_pad_ctrl) },
	{ "EmcXm2DqsPadCtrl2",          TOKEN(emc_xm2dqs_pad_ctrl2) },
	{ "EmcXm2DqsPadCtrl3",          TOKEN(emc_xm2dqs_pad_ctrl3) },
	{ "EmcXm2DqsPadCtrl4",          TOKEN(emc_xm2dqs_pad_ctrl4) },
	{ "EmcXm2DqPadCtrl",            TOKEN(emc_xm2dq_pad_ctrl) },
	{ "EmcXm2DqPadCtrl2",           TOKEN(emc_xm2dq_pad_ctrl2) },
	{ "EmcXm2ClkPadCtrl",           TOKEN(emc_xm2clk_pad_ctrl) },
	{ "EmcXm2ClkPadCtrl2",          TOKEN(emc_xm2clk_pad_ctrl2) },
	{ "EmcXm2CompPadCtrl",          TOKEN(emc_xm2comp_pad_ctrl) },
	{ "EmcXm2VttGenPadCtrl",        TOKEN(emc_xm2vttgen_pad_ctrl) },
	{ "EmcXm2VttGenPadCtrl2",       TOKEN(emc_xm2vttgen_pad_ctrl2) },
	{ "EmcAcpdControl",             TOKEN(emc_acpd_control) },
	{ "EmcSwizzleRank0ByteCfg",     TOKEN(emc_swizzle_rank0_byte_cfg) },
	{ "EmcSwizzleRank0Byte0",       TOKEN(emc_swizzle_rank0_byte0) },
	{ "EmcSwizzleRank0Byte1",       TOKEN(emc_swizzle_rank0_byte1) },
	{ "EmcSwizzleRank0Byte2",       TOKEN(emc_swizzle_rank0_byte2) },
	{ "EmcSwizzleRank0Byte3",       TOKEN(emc_swizzle_rank0_byte3) },
	{ "EmcSwizzleRank1ByteCfg",     TOKEN(emc_swizzle_rank1_byte_cfg) },
	{ "EmcSwizzleRank1Byte0",       TOKEN(emc_swizzle_rank1_byte0) },
	{ "EmcSwizzleRank1Byte1",       TOKEN(emc_swizzle_rank1_byte1) },
	{ "EmcSwizzleRank1Byte2",       TOKEN(emc_swizzle_rank1_byte2) },
	{ "EmcSwizzleRank1Byte3",       TOKEN(emc_swizzle_rank1_byte3) },
	{ "EmcAddrSwizzleStack1a",      TOKEN(emc_addr_swizzle_stack1a) },
	{ "EmcAddrSwizzleStack1b",      TOKEN(emc_addr_swizzle_stack1b) },
	{ "EmcAddrSwizzleStack2a",      TOKEN(emc_addr_swizzle_stack2a) },
	{ "EmcAddrSwizzleStack2b",      TOKEN(emc_addr_swizzle_stack2b) },
	{ "EmcAddrSwizzleStack3",       TOKEN(emc_addr_swizzle_stack3) },
	{ "EmcDsrVttgenDrv",            TOKEN(emc_dsr_vttgen_drv) },
	{ "EmcTxdsrvttgen",             TOKEN(emc_txdsrvttgen) },
	{ "McEmemAdrCfg",               TOKEN(mc_emem_adr_cfg) },
	{ "McEmemAdrCfgDev0",           TOKEN(mc_emem_adr_cfg_dev0) },
	{ "McEmemAdrCfgDev1",           TOKEN(mc_emem_adr_cfg_dev1) },
	{ "McEmemAdrCfgChannelMask",    TOKEN(mc_emem_adr_cfg_channel_mask) },
	{ "McEmemAdrCfgChannelMaskPropagationCount",
			TOKEN(mc_emem_adr_cfg_channel_mask_propagation_count) },
	{ "McEmemAdrCfgBankMask0",      TOKEN(mc_emem_adr_cfg_bank_mask0) },
	{ "McEmemAdrCfgBankMask1",      TOKEN(mc_emem_adr_cfg_bank_mask1) },
	{ "McEmemAdrCfgBankMask2",      TOKEN(mc_emem_adr_cfg_bank_mask2) },
	{ "McEmemArbCfg",               TOKEN(mc_emem_arb_cfg) },
	{ "McEmemArbOutstandingReq",    TOKEN(mc_emem_arb_outstanding_req) },
	{ "McEmemArbTimingRcd",         TOKEN(mc_emem_arb_timing_rcd) },
	{ "McEmemArbTimingRp",          TOKEN(mc_emem_arb_timing_rp) },
	{ "McEmemArbTimingRc",          TOKEN(mc_emem_arb_timing_rc) },
	{ "McEmemArbTimingRas",         TOKEN(mc_emem_arb_timing_ras) },
	{ "McEmemArbTimingFaw",         TOKEN(mc_emem_arb_timing_faw) },
	{ "McEmemArbTimingRrd",         TOKEN(mc_emem_arb_timing_rrd) },
	{ "McEmemArbTimingRap2Pre",     TOKEN(mc_emem_arb_timing_rap2pre) },
	{ "McEmemArbTimingWap2Pre",     TOKEN(mc_emem_arb_timing_wap2pre) },
	{ "McEmemArbTimingR2R",         TOKEN(mc_emem_arb_timing_r2r) },
	{ "McEmemArbTimingW2W",         TOKEN(mc_emem_arb_timing_w2w) },
	{ "McEmemArbTimingR2W",         TOKEN(mc_emem_arb_timing_r2w) },
	{ "McEmemArbTimingW2R",         TOKEN(mc_emem_arb_timing_w2r) },
	{ "McEmemArbDaTurns",           TOKEN(mc_emem_arb_da_turns) },
	{ "McEmemArbDaCovers",          TOKEN(mc_emem_arb_da_covers) },
	{ "McEmemArbMisc0",             TOKEN(mc_emem_arb_misc0) },
	{ "McEmemArbMisc1",             TOKEN(mc_emem_arb_misc1) },
	{ "McEmemArbRing1Throttle",     TOKEN(mc_emem_arb_ring1_throttle) },
	{ "McEmemArbOverride",          TOKEN(mc_emem_arb_override) },
	{ "McEmemArbRsv",               TOKEN(mc_emem_arb_rsv) },
	{ "McClkenOverride",            TOKEN(mc_clken_override) },
	{ "McEmcRegMode",               TOKEN(mc_emc_reg_mode) },
	{ "McVideoProtectBom",          TOKEN(mc_video_protect_bom) },
	{ "McVideoProtectSizeMb",       TOKEN(mc_video_protect_size_mb) },
	{ "McVideoProtectVprOverride",  TOKEN(mc_video_protect_vpr_override) },
	{ "McSecCarveoutBom",           TOKEN(mc_sec_carveout_bom) },
	{ "McSecCarveoutSizeMb",        TOKEN(mc_sec_carveout_size_mb) },
	{ "McVideoProtectWriteAccess",  TOKEN(mc_video_protect_write_access) },
	{ "McSecCarveoutProtectWriteAccess",
			TOKEN(mc_sec_carveout_protect_write_access) },
	{ "EmcCaTrainingEnable",        TOKEN(emc_ca_training_enable) },
	{ "EmcCaTrainingTimingCntl1",   TOKEN(emc_ca_training_timing_cntl1) },
	{ "EmcCaTrainingTimingCntl2",   TOKEN(emc_ca_training_timing_cntl2) },
	{ "SwizzleRankByteEncode",      TOKEN(swizzle_rank_byte_encode) },
	{ "BootRomPatchControl",        TOKEN(boot_rom_patch_control) },
	{ "BootRomPatchData",           TOKEN(boot_rom_patch_data) },
	{ "Ch1EmcDllXformDqs0",         TOKEN(ch1_emc_dll_xform_dqs0) },
	{ "Ch1EmcDllXformDqs1",         TOKEN(ch1_emc_dll_xform_dqs1) },
	{ "Ch1EmcDllXformDqs2",         TOKEN(ch1_emc_dll_xform_dqs2) },
	{ "Ch1EmcDllXformDqs3",         TOKEN(ch1_emc_dll_xform_dqs3) },
	{ "Ch1EmcDllXformDqs4",         TOKEN(ch1_emc_dll_xform_dqs4) },
	{ "Ch1EmcDllXformDqs5",         TOKEN(ch1_emc_dll_xform_dqs5) },
	{ "Ch1EmcDllXformDqs6",         TOKEN(ch1_emc_dll_xform_dqs6) },
	{ "Ch1EmcDllXformDqs7",         TOKEN(ch1_emc_dll_xform_dqs7) },
	{ "Ch1EmcDllXformQUse0",        TOKEN(ch1_emc_dll_xform_quse0) },
	{ "Ch1EmcDllXformQUse1",        TOKEN(ch1_emc_dll_xform_quse1) },
	{ "Ch1EmcDllXformQUse2",        TOKEN(ch1_emc_dll_xform_quse2) },
	{ "Ch1EmcDllXformQUse3",        TOKEN(ch1_emc_dll_xform_quse3) },
	{ "Ch1EmcDllXformQUse4",        TOKEN(ch1_emc_dll_xform_quse4) },
	{ "Ch1EmcDllXformQUse5",        TOKEN(ch1_emc_dll_xform_quse5) },
	{ "Ch1EmcDllXformQUse6",        TOKEN(ch1_emc_dll_xform_quse6) },
	{ "Ch1EmcDllXformQUse7",        TOKEN(ch1_emc_dll_xform_quse7) },
	{ "Ch1EmcDliTrimTxDqs0",        TOKEN(ch1_emc_dli_trim_tx_dqs0) },
	{ "Ch1EmcDliTrimTxDqs1",        TOKEN(ch1_emc_dli_trim_tx_dqs1) },
	{ "Ch1EmcDliTrimTxDqs2",        TOKEN(ch1_emc_dli_trim_tx_dqs2) },
	{ "Ch1EmcDliTrimTxDqs3",        TOKEN(ch1_emc_dli_trim_tx_dqs3) },
	{ "Ch1EmcDliTrimTxDqs4",        TOKEN(ch1_emc_dli_trim_tx_dqs4) },
	{ "Ch1EmcDliTrimTxDqs5",        TOKEN(ch1_emc_dli_trim_tx_dqs5) },
	{ "Ch1EmcDliTrimTxDqs6",        TOKEN(ch1_emc_dli_trim_tx_dqs6) },
	{ "Ch1EmcDliTrimTxDqs7",        TOKEN(ch1_emc_dli_trim_tx_dqs7) },
	{ "Ch1EmcDllXformDq0",          TOKEN(ch1_emc_dll_xform_dq0) },
	{ "Ch1EmcDllXformDq1",          TOKEN(ch1_emc_dll_xform_dq1) },
	{ "Ch1EmcDllXformDq2",          TOKEN(ch1_emc_dll_xform_dq2) },
	{ "Ch1EmcDllXformDq3",          TOKEN(ch1_emc_dll_xform_dq3) },
	{ "Ch1EmcSwizzleRank0ByteCfg",  TOKEN(ch1_emc_swizzle_rank0_byte_cfg) },
	{ "Ch1EmcSwizzleRank0Byte0",    TOKEN(ch1_emc_swizzle_rank0_byte0) },
	{ "Ch1EmcSwizzleRank0Byte1",    TOKEN(ch1_emc_swizzle_rank0_byte1) },
	{ "Ch1EmcSwizzleRank0Byte2",    TOKEN(ch1_emc_swizzle_rank0_byte2) },
	{ "Ch1EmcSwizzleRank0Byte3",    TOKEN(ch1_emc_swizzle_rank0_byte3) },
	{ "Ch1EmcSwizzleRank1ByteCfg",  TOKEN(ch1_emc_swizzle_rank1_byte_cfg) },
	{ "Ch1EmcSwizzleRank1Byte0",    TOKEN(ch1_emc_swizzle_rank1_byte0) },
	{ "Ch1EmcSwizzleRank1Byte1",    TOKEN(ch1_emc_swizzle_rank1_byte1) },
	{ "Ch1EmcSwizzleRank1Byte2",    TOKEN(ch1_emc_swizzle_rank1_byte2) },
	{ "Ch1EmcSwizzleRank1Byte3",    TOKEN(ch1_emc_swizzle_rank1_byte3) },
	{ "Ch1EmcAddrSwizzleStack1a",   TOKEN(ch1_emc_addr_swizzle_stack1a) },
	{ "Ch1EmcAddrSwizzleStack1b",   TOKEN(ch1_emc_addr_swizzle_stack1b) },
	{ "Ch1EmcAddrSwizzleStack2a",   TOKEN(ch1_emc_addr_swizzle_stack2a) },
	{ "Ch1EmcAddrSwizzleStack2b",   TOKEN(ch1_emc_addr_swizzle_stack2b) },
	{ "Ch1EmcAddrSwizzleStack3",    TOKEN(ch1_emc_addr_swizzle_stack3) },
	{ "Ch1EmcAutoCalConfig",        TOKEN(ch1_emc_auto_cal_config) },
	{ "Ch1EmcAutoCalConfig2",       TOKEN(ch1_emc_auto_cal_config2) },
	{ "Ch1EmcAutoCalConfig3",       TOKEN(ch1_emc_auto_cal_config3) },
	{ "Ch1EmcCdbCntl1",             TOKEN(ch1_emc_cdb_cntl1) },
	{ "Ch1EmcDllXformAddr0",        TOKEN(ch1_emc_dll_xform_addr0) },
	{ "Ch1EmcDllXformAddr1",        TOKEN(ch1_emc_dll_xform_addr1) },
	{ "Ch1EmcDllXformAddr2",        TOKEN(ch1_emc_dll_xform_addr2) },
	{ "Ch1EmcFbioSpare",            TOKEN(ch1_emc_fbio_spare) },
	{ "Ch1EmcXm2ClkPadCtrl",        TOKEN(ch1_emc_xm2_clk_pad_ctrl) },
	{ "Ch1EmcXm2ClkPadCtrl2",       TOKEN(ch1_emc_xm2_clk_pad_ctrl2) },
	{ "Ch1EmcXm2CmdPadCtrl2",       TOKEN(ch1_emc_xm2_cmd_pad_ctrl2) },
	{ "Ch1EmcXm2CmdPadCtrl3",       TOKEN(ch1_emc_xm2_cmd_pad_ctrl3) },
	{ "Ch1EmcXm2CmdPadCtrl4",       TOKEN(ch1_emc_xm2_cmd_pad_ctrl4) },
	{ "Ch1EmcXm2DqPadCtrl",         TOKEN(ch1_emc_xm2_dq_pad_ctrl) },
	{ "Ch1EmcXm2DqPadCtrl2",        TOKEN(ch1_emc_xm2_dq_pad_ctrl2) },
	{ "Ch1EmcXm2DqsPadCtrl",        TOKEN(ch1_emc_xm2_dqs_pad_ctrl) },
	{ "Ch1EmcXm2DqsPadCtrl3",       TOKEN(ch1_emc_xm2_dqs_pad_ctrl3) },
	{ "Ch1EmcXm2DqsPadCtrl4",       TOKEN(ch1_emc_xm2_dqs_pad_ctrl4) },
	{ NULL, 0, 0, NULL }
};

field_item s_sdmmc_table_t114[] = {
	{ "ClockDivider",               TOKEN(sdmmc_clock_divider) },
	{ "DataWidth",
	  token_sdmmc_data_width,
	  field_type_enum,
	  s_sdmmc_data_width_table_t114 },
	{ "MaxPowerClassSupported",     TOKEN(sdmmc_max_power_class_supported) },
	{ "MultiPageSupport",           TOKEN(sdmmc_multi_page_support) },
	{ NULL, 0, 0, NULL }
};

field_item s_spiflash_table_t114[] = {
	{ "ReadCommandTypeFast",        TOKEN(spiflash_read_command_type_fast) },
	{ "PageSize2kor16k",            TOKEN(spiflash_page_size_2k_or_16k) },
	{ "ClockDivider",               TOKEN(spiflash_clock_divider) },
	{ "ClockSource",
	  token_spiflash_clock_source,
	  field_type_enum,
	  s_spi_clock_source_table_t114 },
	{ NULL, 0, 0, NULL }
};

parse_subfield_item s_device_type_table_t114[] = {
	{ "SdmmcParams.", token_sdmmc_params,
		s_sdmmc_table_t114, t114_set_dev_param },
	{ "SpiFlashParams.", token_spiflash_params,
		s_spiflash_table_t114, t114_set_dev_param },
	{ NULL, 0, NULL }
};