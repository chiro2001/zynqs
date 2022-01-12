// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xbram2da_start.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XBram2da_start_CfgInitialize(XBram2da_start *InstancePtr, XBram2da_start_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XBram2da_start_Start(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL) & 0x80;
    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XBram2da_start_IsDone(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XBram2da_start_IsIdle(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XBram2da_start_IsReady(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XBram2da_start_EnableAutoRestart(XBram2da_start *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XBram2da_start_DisableAutoRestart(XBram2da_start *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_AP_CTRL, 0);
}

void XBram2da_start_Set_start_r(XBram2da_start *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_START_R_DATA, Data);
}

u32 XBram2da_start_Get_start_r(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_START_R_DATA);
    return Data;
}

void XBram2da_start_Set_stop(XBram2da_start *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_STOP_DATA, Data);
}

u32 XBram2da_start_Get_stop(XBram2da_start *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_STOP_DATA);
    return Data;
}

void XBram2da_start_InterruptGlobalEnable(XBram2da_start *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_GIE, 1);
}

void XBram2da_start_InterruptGlobalDisable(XBram2da_start *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_GIE, 0);
}

void XBram2da_start_InterruptEnable(XBram2da_start *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_IER);
    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_IER, Register | Mask);
}

void XBram2da_start_InterruptDisable(XBram2da_start *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_IER);
    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_IER, Register & (~Mask));
}

void XBram2da_start_InterruptClear(XBram2da_start *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XBram2da_start_WriteReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_ISR, Mask);
}

u32 XBram2da_start_InterruptGetEnabled(XBram2da_start *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_IER);
}

u32 XBram2da_start_InterruptGetStatus(XBram2da_start *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XBram2da_start_ReadReg(InstancePtr->Control_BaseAddress, XBRAM2DA_START_CONTROL_ADDR_ISR);
}

