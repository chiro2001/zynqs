// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xd2dma.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XD2dma_CfgInitialize(XD2dma *InstancePtr, XD2dma_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XD2dma_Start(XD2dma *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL) & 0x80;
    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XD2dma_IsDone(XD2dma *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XD2dma_IsIdle(XD2dma *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XD2dma_IsReady(XD2dma *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XD2dma_EnableAutoRestart(XD2dma *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XD2dma_DisableAutoRestart(XD2dma *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_AP_CTRL, 0);
}

void XD2dma_Set_depth(XD2dma *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_DEPTH_DATA, Data);
}

u32 XD2dma_Get_depth(XD2dma *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_DEPTH_DATA);
    return Data;
}

void XD2dma_InterruptGlobalEnable(XD2dma *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_GIE, 1);
}

void XD2dma_InterruptGlobalDisable(XD2dma *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_GIE, 0);
}

void XD2dma_InterruptEnable(XD2dma *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_IER);
    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_IER, Register | Mask);
}

void XD2dma_InterruptDisable(XD2dma *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_IER);
    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_IER, Register & (~Mask));
}

void XD2dma_InterruptClear(XD2dma *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XD2dma_WriteReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_ISR, Mask);
}

u32 XD2dma_InterruptGetEnabled(XD2dma *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_IER);
}

u32 XD2dma_InterruptGetStatus(XD2dma *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XD2dma_ReadReg(InstancePtr->Control_BaseAddress, XD2DMA_CONTROL_ADDR_ISR);
}

