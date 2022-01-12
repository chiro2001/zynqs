// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XAD_FIFO_ALL_H
#define XAD_FIFO_ALL_H

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
#include "xad_fifo_all_hw.h"

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
} XAd_fifo_all_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAd_fifo_all;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAd_fifo_all_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAd_fifo_all_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAd_fifo_all_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAd_fifo_all_ReadReg(BaseAddress, RegOffset) \
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
int XAd_fifo_all_Initialize(XAd_fifo_all *InstancePtr, u16 DeviceId);
XAd_fifo_all_Config* XAd_fifo_all_LookupConfig(u16 DeviceId);
int XAd_fifo_all_CfgInitialize(XAd_fifo_all *InstancePtr, XAd_fifo_all_Config *ConfigPtr);
#else
int XAd_fifo_all_Initialize(XAd_fifo_all *InstancePtr, const char* InstanceName);
int XAd_fifo_all_Release(XAd_fifo_all *InstancePtr);
#endif

void XAd_fifo_all_Start(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_IsDone(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_IsIdle(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_IsReady(XAd_fifo_all *InstancePtr);
void XAd_fifo_all_EnableAutoRestart(XAd_fifo_all *InstancePtr);
void XAd_fifo_all_DisableAutoRestart(XAd_fifo_all *InstancePtr);

void XAd_fifo_all_Set_div(XAd_fifo_all *InstancePtr, u32 Data);
u32 XAd_fifo_all_Get_div(XAd_fifo_all *InstancePtr);
void XAd_fifo_all_Set_threshold(XAd_fifo_all *InstancePtr, u32 Data);
u32 XAd_fifo_all_Get_threshold(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_Get_count(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_Get_count_vld(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_Get_success(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_Get_success_vld(XAd_fifo_all *InstancePtr);

void XAd_fifo_all_InterruptGlobalEnable(XAd_fifo_all *InstancePtr);
void XAd_fifo_all_InterruptGlobalDisable(XAd_fifo_all *InstancePtr);
void XAd_fifo_all_InterruptEnable(XAd_fifo_all *InstancePtr, u32 Mask);
void XAd_fifo_all_InterruptDisable(XAd_fifo_all *InstancePtr, u32 Mask);
void XAd_fifo_all_InterruptClear(XAd_fifo_all *InstancePtr, u32 Mask);
u32 XAd_fifo_all_InterruptGetEnabled(XAd_fifo_all *InstancePtr);
u32 XAd_fifo_all_InterruptGetStatus(XAd_fifo_all *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
