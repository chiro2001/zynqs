// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xad_fifo_all.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAd_fifo_all_CfgInitialize(XAd_fifo_all *InstancePtr, XAd_fifo_all_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAd_fifo_all_Start(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAd_fifo_all_IsDone(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAd_fifo_all_IsIdle(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAd_fifo_all_IsReady(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAd_fifo_all_EnableAutoRestart(XAd_fifo_all *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XAd_fifo_all_DisableAutoRestart(XAd_fifo_all *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_AP_CTRL, 0);
}

void XAd_fifo_all_Set_div(XAd_fifo_all *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_DIV_DATA, Data);
}

u32 XAd_fifo_all_Get_div(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_DIV_DATA);
    return Data;
}

void XAd_fifo_all_Set_threshold(XAd_fifo_all *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_THRESHOLD_DATA, Data);
}

u32 XAd_fifo_all_Get_threshold(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_THRESHOLD_DATA);
    return Data;
}

u32 XAd_fifo_all_Get_start_r(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_START_R_DATA);
    return Data;
}

u32 XAd_fifo_all_Get_start_r_vld(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_START_R_CTRL);
    return Data & 0x1;
}

u32 XAd_fifo_all_Get_end_r(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_END_R_DATA);
    return Data;
}

u32 XAd_fifo_all_Get_end_r_vld(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_END_R_CTRL);
    return Data & 0x1;
}

u32 XAd_fifo_all_Get_count(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_COUNT_DATA);
    return Data;
}

u32 XAd_fifo_all_Get_count_vld(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_COUNT_CTRL);
    return Data & 0x1;
}

u32 XAd_fifo_all_Get_success(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_DATA);
    return Data;
}

u32 XAd_fifo_all_Get_success_vld(XAd_fifo_all *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_SUCCESS_CTRL);
    return Data & 0x1;
}

void XAd_fifo_all_InterruptGlobalEnable(XAd_fifo_all *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_GIE, 1);
}

void XAd_fifo_all_InterruptGlobalDisable(XAd_fifo_all *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_GIE, 0);
}

void XAd_fifo_all_InterruptEnable(XAd_fifo_all *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_IER);
    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_IER, Register | Mask);
}

void XAd_fifo_all_InterruptDisable(XAd_fifo_all *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_IER);
    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_IER, Register & (~Mask));
}

void XAd_fifo_all_InterruptClear(XAd_fifo_all *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd_fifo_all_WriteReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_ISR, Mask);
}

u32 XAd_fifo_all_InterruptGetEnabled(XAd_fifo_all *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_IER);
}

u32 XAd_fifo_all_InterruptGetStatus(XAd_fifo_all *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAd_fifo_all_ReadReg(InstancePtr->Control_BaseAddress, XAD_FIFO_ALL_CONTROL_ADDR_ISR);
}

