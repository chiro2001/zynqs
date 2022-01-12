// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of div
//        bit 31~0 - div[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of threshold
//        bit 31~0 - threshold[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of start_r
//        bit 31~0 - start_r[31:0] (Read)
// 0x24 : Control signal of start_r
//        bit 0  - start_r_ap_vld (Read/COR)
//        others - reserved
// 0x30 : Data signal of end_r
//        bit 31~0 - end_r[31:0] (Read)
// 0x34 : Control signal of end_r
//        bit 0  - end_r_ap_vld (Read/COR)
//        others - reserved
// 0x40 : Data signal of count
//        bit 31~0 - count[31:0] (Read)
// 0x44 : Control signal of count
//        bit 0  - count_ap_vld (Read/COR)
//        others - reserved
// 0x50 : Data signal of success
//        bit 31~0 - success[31:0] (Read)
// 0x54 : Control signal of success
//        bit 0  - success_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL        0x00
#define XAD_FIFO_ALL_CONTROL_ADDR_GIE            0x04
#define XAD_FIFO_ALL_CONTROL_ADDR_IER            0x08
#define XAD_FIFO_ALL_CONTROL_ADDR_ISR            0x0c
#define XAD_FIFO_ALL_CONTROL_ADDR_DIV_DATA       0x10
#define XAD_FIFO_ALL_CONTROL_BITS_DIV_DATA       32
#define XAD_FIFO_ALL_CONTROL_ADDR_THRESHOLD_DATA 0x18
#define XAD_FIFO_ALL_CONTROL_BITS_THRESHOLD_DATA 32
#define XAD_FIFO_ALL_CONTROL_ADDR_START_R_DATA   0x20
#define XAD_FIFO_ALL_CONTROL_BITS_START_R_DATA   32
#define XAD_FIFO_ALL_CONTROL_ADDR_START_R_CTRL   0x24
#define XAD_FIFO_ALL_CONTROL_ADDR_END_R_DATA     0x30
#define XAD_FIFO_ALL_CONTROL_BITS_END_R_DATA     32
#define XAD_FIFO_ALL_CONTROL_ADDR_END_R_CTRL     0x34
#define XAD_FIFO_ALL_CONTROL_ADDR_COUNT_DATA     0x40
#define XAD_FIFO_ALL_CONTROL_BITS_COUNT_DATA     32
#define XAD_FIFO_ALL_CONTROL_ADDR_COUNT_CTRL     0x44
#define XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_DATA   0x50
#define XAD_FIFO_ALL_CONTROL_BITS_SUCCESS_DATA   32
#define XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_CTRL   0x54

