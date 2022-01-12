// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XAD2BRAM_H
#define XAD2BRAM_H

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
#include "xad2bram_hw.h"

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
} XAd2bram_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAd2bram;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAd2bram_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAd2bram_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAd2bram_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAd2bram_ReadReg(BaseAddress, RegOffset) \
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
int XAd2bram_Initialize(XAd2bram *InstancePtr, u16 DeviceId);
XAd2bram_Config* XAd2bram_LookupConfig(u16 DeviceId);
int XAd2bram_CfgInitialize(XAd2bram *InstancePtr, XAd2bram_Config *ConfigPtr);
#else
int XAd2bram_Initialize(XAd2bram *InstancePtr, const char* InstanceName);
int XAd2bram_Release(XAd2bram *InstancePtr);
#endif

void XAd2bram_Start(XAd2bram *InstancePtr);
u32 XAd2bram_IsDone(XAd2bram *InstancePtr);
u32 XAd2bram_IsIdle(XAd2bram *InstancePtr);
u32 XAd2bram_IsReady(XAd2bram *InstancePtr);
void XAd2bram_EnableAutoRestart(XAd2bram *InstancePtr);
void XAd2bram_DisableAutoRestart(XAd2bram *InstancePtr);

void XAd2bram_Set_depth(XAd2bram *InstancePtr, u32 Data);
u32 XAd2bram_Get_depth(XAd2bram *InstancePtr);

void XAd2bram_InterruptGlobalEnable(XAd2bram *InstancePtr);
void XAd2bram_InterruptGlobalDisable(XAd2bram *InstancePtr);
void XAd2bram_InterruptEnable(XAd2bram *InstancePtr, u32 Mask);
void XAd2bram_InterruptDisable(XAd2bram *InstancePtr, u32 Mask);
void XAd2bram_InterruptClear(XAd2bram *InstancePtr, u32 Mask);
u32 XAd2bram_InterruptGetEnabled(XAd2bram *InstancePtr);
u32 XAd2bram_InterruptGetStatus(XAd2bram *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
