// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XBRAM2DA_START_H
#define XBRAM2DA_START_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xbram2da_start_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XBram2da_start_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XBram2da_start;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XBram2da_start_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XBram2da_start_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XBram2da_start_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XBram2da_start_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XBram2da_start_Initialize(XBram2da_start *InstancePtr, u16 DeviceId);
XBram2da_start_Config* XBram2da_start_LookupConfig(u16 DeviceId);
int XBram2da_start_CfgInitialize(XBram2da_start *InstancePtr, XBram2da_start_Config *ConfigPtr);
#else
int XBram2da_start_Initialize(XBram2da_start *InstancePtr, const char* InstanceName);
int XBram2da_start_Release(XBram2da_start *InstancePtr);
#endif

void XBram2da_start_Start(XBram2da_start *InstancePtr);
u32 XBram2da_start_IsDone(XBram2da_start *InstancePtr);
u32 XBram2da_start_IsIdle(XBram2da_start *InstancePtr);
u32 XBram2da_start_IsReady(XBram2da_start *InstancePtr);
void XBram2da_start_EnableAutoRestart(XBram2da_start *InstancePtr);
void XBram2da_start_DisableAutoRestart(XBram2da_start *InstancePtr);

void XBram2da_start_Set_start_r(XBram2da_start *InstancePtr, u32 Data);
u32 XBram2da_start_Get_start_r(XBram2da_start *InstancePtr);
void XBram2da_start_Set_stop(XBram2da_start *InstancePtr, u32 Data);
u32 XBram2da_start_Get_stop(XBram2da_start *InstancePtr);

void XBram2da_start_InterruptGlobalEnable(XBram2da_start *InstancePtr);
void XBram2da_start_InterruptGlobalDisable(XBram2da_start *InstancePtr);
void XBram2da_start_InterruptEnable(XBram2da_start *InstancePtr, u32 Mask);
void XBram2da_start_InterruptDisable(XBram2da_start *InstancePtr, u32 Mask);
void XBram2da_start_InterruptClear(XBram2da_start *InstancePtr, u32 Mask);
u32 XBram2da_start_InterruptGetEnabled(XBram2da_start *InstancePtr);
u32 XBram2da_start_InterruptGetStatus(XBram2da_start *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
