// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xbram2da_start.h"

extern XBram2da_start_Config XBram2da_start_ConfigTable[];

XBram2da_start_Config *XBram2da_start_LookupConfig(u16 DeviceId) {
	XBram2da_start_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XBRAM2DA_START_NUM_INSTANCES; Index++) {
		if (XBram2da_start_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XBram2da_start_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XBram2da_start_Initialize(XBram2da_start *InstancePtr, u16 DeviceId) {
	XBram2da_start_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XBram2da_start_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XBram2da_start_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

