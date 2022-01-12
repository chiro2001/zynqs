// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xd2dma.h"

extern XD2dma_Config XD2dma_ConfigTable[];

XD2dma_Config *XD2dma_LookupConfig(u16 DeviceId) {
	XD2dma_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XD2DMA_NUM_INSTANCES; Index++) {
		if (XD2dma_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XD2dma_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XD2dma_Initialize(XD2dma *InstancePtr, u16 DeviceId) {
	XD2dma_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XD2dma_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XD2dma_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

