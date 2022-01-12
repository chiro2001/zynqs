// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xad2bram.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAd2bram_CfgInitialize(XAd2bram *InstancePtr, XAd2bram_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAd2bram_Start(XAd2bram *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAd2bram_IsDone(XAd2bram *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAd2bram_IsIdle(XAd2bram *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAd2bram_IsReady(XAd2bram *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAd2bram_EnableAutoRestart(XAd2bram *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XAd2bram_DisableAutoRestart(XAd2bram *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_AP_CTRL, 0);
}

void XAd2bram_Set_depth(XAd2bram *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_DEPTH_DATA, Data);
}

u32 XAd2bram_Get_depth(XAd2bram *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_DEPTH_DATA);
    return Data;
}

void XAd2bram_InterruptGlobalEnable(XAd2bram *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_GIE, 1);
}

void XAd2bram_InterruptGlobalDisable(XAd2bram *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_GIE, 0);
}

void XAd2bram_InterruptEnable(XAd2bram *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_IER);
    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_IER, Register | Mask);
}

void XAd2bram_InterruptDisable(XAd2bram *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_IER);
    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_IER, Register & (~Mask));
}

void XAd2bram_InterruptClear(XAd2bram *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAd2bram_WriteReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_ISR, Mask);
}

u32 XAd2bram_InterruptGetEnabled(XAd2bram *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_IER);
}

u32 XAd2bram_InterruptGetStatus(XAd2bram *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAd2bram_ReadReg(InstancePtr->Control_BaseAddress, XAD2BRAM_CONTROL_ADDR_ISR);
}

