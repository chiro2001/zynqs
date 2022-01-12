// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xad_fifo_all.h"

extern XAd_fifo_all_Config XAd_fifo_all_ConfigTable[];

XAd_fifo_all_Config *XAd_fifo_all_LookupConfig(u16 DeviceId) {
	XAd_fifo_all_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XAD_FIFO_ALL_NUM_INSTANCES; Index++) {
		if (XAd_fifo_all_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAd_fifo_all_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAd_fifo_all_Initialize(XAd_fifo_all *InstancePtr, u16 DeviceId) {
	XAd_fifo_all_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAd_fifo_all_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAd_fifo_all_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

