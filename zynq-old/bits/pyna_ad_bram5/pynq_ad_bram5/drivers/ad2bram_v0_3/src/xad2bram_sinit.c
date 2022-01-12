// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xad2bram.h"

extern XAd2bram_Config XAd2bram_ConfigTable[];

XAd2bram_Config *XAd2bram_LookupConfig(u16 DeviceId) {
	XAd2bram_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XAD2BRAM_NUM_INSTANCES; Index++) {
		if (XAd2bram_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAd2bram_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAd2bram_Initialize(XAd2bram *InstancePtr, u16 DeviceId) {
	XAd2bram_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAd2bram_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAd2bram_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

