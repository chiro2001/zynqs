// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XD2DMA_H
#define XD2DMA_H

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
#include "xd2dma_hw.h"

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
} XD2dma_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XD2dma;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XD2dma_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XD2dma_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XD2dma_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XD2dma_ReadReg(BaseAddress, RegOffset) \
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
int XD2dma_Initialize(XD2dma *InstancePtr, u16 DeviceId);
XD2dma_Config* XD2dma_LookupConfig(u16 DeviceId);
int XD2dma_CfgInitialize(XD2dma *InstancePtr, XD2dma_Config *ConfigPtr);
#else
int XD2dma_Initialize(XD2dma *InstancePtr, const char* InstanceName);
int XD2dma_Release(XD2dma *InstancePtr);
#endif

void XD2dma_Start(XD2dma *InstancePtr);
u32 XD2dma_IsDone(XD2dma *InstancePtr);
u32 XD2dma_IsIdle(XD2dma *InstancePtr);
u32 XD2dma_IsReady(XD2dma *InstancePtr);
void XD2dma_EnableAutoRestart(XD2dma *InstancePtr);
void XD2dma_DisableAutoRestart(XD2dma *InstancePtr);

void XD2dma_Set_depth(XD2dma *InstancePtr, u32 Data);
u32 XD2dma_Get_depth(XD2dma *InstancePtr);

void XD2dma_InterruptGlobalEnable(XD2dma *InstancePtr);
void XD2dma_InterruptGlobalDisable(XD2dma *InstancePtr);
void XD2dma_InterruptEnable(XD2dma *InstancePtr, u32 Mask);
void XD2dma_InterruptDisable(XD2dma *InstancePtr, u32 Mask);
void XD2dma_InterruptClear(XD2dma *InstancePtr, u32 Mask);
u32 XD2dma_InterruptGetEnabled(XD2dma *InstancePtr);
u32 XD2dma_InterruptGetStatus(XD2dma *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
