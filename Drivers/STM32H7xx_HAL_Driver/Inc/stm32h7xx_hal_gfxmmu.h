/**
  ******************************************************************************
  * @file    stm32h7xx_hal_gfxmmu.h
  * @author  MCD Application Team
  * @brief   Header file of GFXMMU HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_GFXMMU_H
#define STM32H7xx_HAL_GFXMMU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

#if defined(GFXMMU)

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup GFXMMU
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Types GFXMMU Exported Types
  * @{
  */

/** 
  * @brief  HAL GFXMMU states definition
  */
typedef enum
{
  HAL_GFXMMU_STATE_RESET = 0x00U, /*!< GFXMMU not initialized */
  HAL_GFXMMU_STATE_READY = 0x01U, /*!< GFXMMU initialized and ready for use */
}HAL_GFXMMU_StateTypeDef;

/** 
  * @brief  GFXMMU buffers structure definition
  */
typedef struct
{
  uint32_t Buf0Address; /*!< Physical address of buffer 0. */
  uint32_t Buf1Address; /*!< Physical address of buffer 1. */
  uint32_t Buf2Address; /*!< Physical address of buffer 2. */
  uint32_t Buf3Address; /*!< Physical address of buffer 3. */
}GFXMMU_BuffersTypeDef;

/** 
  * @brief  GFXMMU cache and pre-fetch structure definition
  */
typedef struct
{
  FunctionalState Activation;          /*!< Cache and pre-fetch enable/disable.
                                            @note: All following parameters are useful only if cache and pre-fetch are enabled. */
  uint32_t        CacheLock;           /*!< Locking the cache to a buffer.
                                            This parameter can be a value of @ref GFXMMU_CacheLock. */
  uint32_t        CacheLockBuffer;     /*!< Buffer on which the cache is locked.
                                            This parameter can be a value of @ref GFXMMU_CacheLockBuffer.
                                            @note: Useful only when lock of the cache is enabled. */
  uint32_t        CacheForce;          /*!< Forcing the cache regardless MPU attributes.
                                            This parameter can be a value of @ref GFXMMU_CacheForce.
                                            @note: Useful only when lock of the cache is enabled. */
  uint32_t        OutterBufferability; /*!< Bufferability of an access generated by the GFXMMU cache.
                                            This parameter can be a value of @ref GFXMMU_OutterBufferability. */
  uint32_t        OutterCachability;   /*!< Cachability of an access generated by the GFXMMU cache.
                                            This parameter can be a value of @ref GFXMMU_OutterCachability. */
  uint32_t        Prefetch;            /*!< Pre-fetch enable/disable.
                                            This parameter can be a value of @ref GFXMMU_Prefetch. */
}GFXMMU_CachePrefetchTypeDef;

/** 
  * @brief  GFXMMU interrupts structure definition
  */
typedef struct
{
  FunctionalState Activation;     /*!< Interrupts enable/disable */
  uint32_t        UsedInterrupts; /*!< Interrupts used.
                                       This parameter can be a values combination of @ref GFXMMU_Interrupts.
                                       @note: Useful only when interrupts are enabled. */
}GFXMMU_InterruptsTypeDef;

/** 
  * @brief  GFXMMU init structure definition
  */
typedef struct
{
  uint32_t                    BlocksPerLine; /*!< Number of blocks of 16 bytes per line.
                                                  This parameter can be a value of @ref GFXMMU_BlocksPerLine. */
  uint32_t                    DefaultValue;  /*!< Value returned when virtual memory location not physically mapped. */
  GFXMMU_BuffersTypeDef       Buffers;       /*!< Physical buffers addresses. */
  GFXMMU_CachePrefetchTypeDef CachePrefetch; /*!< Cache and pre-fetch parameters. */
  GFXMMU_InterruptsTypeDef    Interrupts;    /*!< Interrupts parameters. */
}GFXMMU_InitTypeDef;

/** 
  * @brief  GFXMMU handle structure definition
  */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
typedef struct __GFXMMU_HandleTypeDef
#else
typedef struct
#endif
{
  GFXMMU_TypeDef          *Instance; /*!< GFXMMU instance */
  GFXMMU_InitTypeDef      Init;      /*!< GFXMMU init parameters */
  HAL_GFXMMU_StateTypeDef State;     /*!< GFXMMU state */
  __IO uint32_t           ErrorCode; /*!< GFXMMU error code */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
  void (*ErrorCallback)     (struct __GFXMMU_HandleTypeDef *hgfxmmu); /*!< GFXMMU error callback */
  void (*MspInitCallback)   (struct __GFXMMU_HandleTypeDef *hgfxmmu); /*!< GFXMMU MSP init callback */
  void (*MspDeInitCallback) (struct __GFXMMU_HandleTypeDef *hgfxmmu); /*!< GFXMMU MSP de-init callback */
#endif
}GFXMMU_HandleTypeDef;

/** 
  * @brief  GFXMMU LUT line structure definition
  */
typedef struct
{
  uint32_t LineNumber;        /*!< LUT line number.
                                   This parameter must be a number between Min_Data = 0 and Max_Data = 1023. */
  uint32_t LineStatus;        /*!< LUT line enable/disable.
                                   This parameter can be a value of @ref GFXMMU_LutLineStatus. */
  uint32_t FirstVisibleBlock; /*!< First visible block on this line.
                                   This parameter must be a number between Min_Data = 0 and Max_Data = 255. */
  uint32_t LastVisibleBlock;  /*!< Last visible block on this line.
                                   This parameter must be a number between Min_Data = 0 and Max_Data = 255. */
  int32_t  LineOffset;        /*!< Offset of block 0 of the current line in physical buffer.
                                   This parameter must be a number between Min_Data = -4080 and Max_Data = 4190208.
                                   @note: Line offset has to be computed with the following formula:
                                          LineOffset = [(Blocks already used) - (1st visible block)]*BlockSize. */
}GFXMMU_LutLineTypeDef;

#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
/**
  * @brief  GFXMMU callback ID enumeration definition
  */
typedef enum
{
  HAL_GFXMMU_ERROR_CB_ID     = 0x00U, /*!< GFXMMU error callback ID */
  HAL_GFXMMU_MSPINIT_CB_ID   = 0x01U, /*!< GFXMMU MSP init callback ID */
  HAL_GFXMMU_MSPDEINIT_CB_ID = 0x02U  /*!< GFXMMU MSP de-init callback ID */
}HAL_GFXMMU_CallbackIDTypeDef;

/**
  * @brief  GFXMMU callback pointer definition
  */
typedef void (*pGFXMMU_CallbackTypeDef)(GFXMMU_HandleTypeDef *hgfxmmu);
#endif

/**
  * @}
  */ 
/* End of exported types -----------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Constants GFXMMU Exported Constants
  * @{
  */

/** @defgroup GFXMMU_BlocksPerLine GFXMMU blocks per line
  * @{
  */
#define GFXMMU_256BLOCKS 0x00000000U     /*!< 256 blocks of 16 bytes per line */
#define GFXMMU_192BLOCKS GFXMMU_CR_192BM /*!< 192 blocks of 16 bytes per line */
/**
  * @}
  */

/** @defgroup GFXMMU_CacheLock GFXMMU cache lock
  * @{
  */
#define GFXMMU_CACHE_LOCK_DISABLE 0x00000000U  /*!< Cache not locked to a buffer */
#define GFXMMU_CACHE_LOCK_ENABLE  GFXMMU_CR_CL /*!< Cache locked to a buffer */
/**
  * @}
  */

/** @defgroup GFXMMU_CacheLockBuffer GFXMMU cache lock buffer
  * @{
  */
#define GFXMMU_CACHE_LOCK_BUFFER0 0x00000000U     /*!< Cache locked to buffer 0 */
#define GFXMMU_CACHE_LOCK_BUFFER1 GFXMMU_CR_CLB_0 /*!< Cache locked to buffer 1 */
#define GFXMMU_CACHE_LOCK_BUFFER2 GFXMMU_CR_CLB_1 /*!< Cache locked to buffer 2 */
#define GFXMMU_CACHE_LOCK_BUFFER3 GFXMMU_CR_CLB   /*!< Cache locked to buffer 3 */
/**
  * @}
  */

/** @defgroup GFXMMU_CacheForce GFXMMU cache force
  * @{
  */
#define GFXMMU_CACHE_FORCE_DISABLE 0x00000000U  /*!< Caching not forced */
#define GFXMMU_CACHE_FORCE_ENABLE  GFXMMU_CR_FC /*!< Caching forced */
/**
  * @}
  */

/** @defgroup GFXMMU_OutterBufferability GFXMMU outer bufferability
  * @{
  */
#define GFXMMU_OUTTER_BUFFERABILITY_DISABLE 0x00000000U  /*!< No bufferable */
#define GFXMMU_OUTTER_BUFFERABILITY_ENABLE  GFXMMU_CR_OB /*!< Bufferable */
/**
  * @}
  */

/** @defgroup GFXMMU_OutterCachability GFXMMU outer cachability
  * @{
  */
#define GFXMMU_OUTTER_CACHABILITY_DISABLE 0x00000000U  /*!< No cacheable */
#define GFXMMU_OUTTER_CACHABILITY_ENABLE  GFXMMU_CR_OC /*!< Cacheable */
/**
  * @}
  */

/** @defgroup GFXMMU_Prefetch GFXMMU pre-fetch
  * @{
  */
#define GFXMMU_PREFETCH_DISABLE GFXMMU_CR_PD /*!< Pre-fetch disable */
#define GFXMMU_PREFETCH_ENABLE  0x00000000U  /*!< Pre-fetch enable */
/**
  * @}
  */

/** @defgroup GFXMMU_Interrupts GFXMMU interrupts
  * @{
  */
#define GFXMMU_AHB_MASTER_ERROR_IT GFXMMU_CR_AMEIE /*!< AHB master error interrupt */
#define GFXMMU_BUFFER0_OVERFLOW_IT GFXMMU_CR_B0OIE /*!< Buffer 0 overflow interrupt */
#define GFXMMU_BUFFER1_OVERFLOW_IT GFXMMU_CR_B1OIE /*!< Buffer 1 overflow interrupt */
#define GFXMMU_BUFFER2_OVERFLOW_IT GFXMMU_CR_B2OIE /*!< Buffer 2 overflow interrupt */
#define GFXMMU_BUFFER3_OVERFLOW_IT GFXMMU_CR_B3OIE /*!< Buffer 3 overflow interrupt */
/**
  * @}
  */

/** @defgroup GFXMMU_Error_Code GFXMMU Error Code
  * @{
  */
#define GFXMMU_ERROR_NONE             0x00000000U    /*!< No error */
#define GFXMMU_ERROR_BUFFER0_OVERFLOW GFXMMU_SR_B0OF /*!< Buffer 0 overflow */
#define GFXMMU_ERROR_BUFFER1_OVERFLOW GFXMMU_SR_B1OF /*!< Buffer 1 overflow */
#define GFXMMU_ERROR_BUFFER2_OVERFLOW GFXMMU_SR_B2OF /*!< Buffer 2 overflow */
#define GFXMMU_ERROR_BUFFER3_OVERFLOW GFXMMU_SR_B3OF /*!< Buffer 3 overflow */
#define GFXMMU_ERROR_AHB_MASTER       GFXMMU_SR_AMEF /*!< AHB master error */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
#define GFXMMU_ERROR_INVALID_CALLBACK 0x00000100U    /*!< Invalid callback error */
#endif
/**
  * @}
  */

/** @defgroup GFXMMU_LutLineStatus GFXMMU LUT line status
  * @{
  */
#define GFXMMU_LUT_LINE_DISABLE 0x00000000U     /*!< LUT line disabled */
#define GFXMMU_LUT_LINE_ENABLE  GFXMMU_LUTxL_EN /*!< LUT line enabled */
/**
  * @}
  */

/** @defgroup GFXMMU_CacheForceParam GFXMMU cache force parameter
  * @{
  */
#define GFXMMU_CACHE_FORCE_FLUSH      GFXMMU_CCR_FF /*!< Force cache flush */
#define GFXMMU_CACHE_FORCE_INVALIDATE GFXMMU_CCR_FI /*!< Force cache invalidate */
/**
  * @}
  */

/**
  * @}
  */ 
/* End of exported constants -------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/** @defgroup GFXMMU_Exported_Macros GFXMMU Exported Macros
 * @{
 */

/** @brief  Reset GFXMMU handle state.
  * @param  __HANDLE__ GFXMMU handle.
  * @retval None
  */
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
#define __HAL_GFXMMU_RESET_HANDLE_STATE(__HANDLE__) do{                                               \
                                                        (__HANDLE__)->State = HAL_GFXMMU_STATE_RESET; \
                                                        (__HANDLE__)->MspInitCallback = NULL;         \
                                                        (__HANDLE__)->MspDeInitCallback = NULL;       \
                                                      } while(0)
#else
#define __HAL_GFXMMU_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_GFXMMU_STATE_RESET)
#endif

/**
  * @}
  */
/* End of exported macros ----------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GFXMMU_Exported_Functions GFXMMU Exported Functions
  * @{
  */

/** @addtogroup GFXMMU_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_GFXMMU_Init(GFXMMU_HandleTypeDef *hgfxmmu);
HAL_StatusTypeDef HAL_GFXMMU_DeInit(GFXMMU_HandleTypeDef *hgfxmmu);
void HAL_GFXMMU_MspInit(GFXMMU_HandleTypeDef *hgfxmmu);
void HAL_GFXMMU_MspDeInit(GFXMMU_HandleTypeDef *hgfxmmu);
#if (USE_HAL_GFXMMU_REGISTER_CALLBACKS == 1)
/* GFXMMU callbacks register/unregister functions *****************************/
HAL_StatusTypeDef HAL_GFXMMU_RegisterCallback(GFXMMU_HandleTypeDef        *hgfxmmu,
                                              HAL_GFXMMU_CallbackIDTypeDef CallbackID,
                                              pGFXMMU_CallbackTypeDef      pCallback);
HAL_StatusTypeDef HAL_GFXMMU_UnRegisterCallback(GFXMMU_HandleTypeDef        *hgfxmmu,
                                                HAL_GFXMMU_CallbackIDTypeDef CallbackID);
#endif
/**
  * @}
  */

/** @addtogroup GFXMMU_Exported_Functions_Group2 Operations functions
  * @{
  */
/* Operation functions ********************************************************/
HAL_StatusTypeDef HAL_GFXMMU_ConfigLut(GFXMMU_HandleTypeDef *hgfxmmu,
                                       uint32_t FirstLine,
                                       uint32_t LinesNumber,
                                       uint32_t Address);

HAL_StatusTypeDef HAL_GFXMMU_DisableLutLines(GFXMMU_HandleTypeDef *hgfxmmu,
                                             uint32_t FirstLine,
                                             uint32_t LinesNumber);

HAL_StatusTypeDef HAL_GFXMMU_ConfigLutLine(GFXMMU_HandleTypeDef *hgfxmmu, GFXMMU_LutLineTypeDef *lutLine);

HAL_StatusTypeDef HAL_GFXMMU_ConfigForceCache(GFXMMU_HandleTypeDef *hgfxmmu, uint32_t ForceParam);

HAL_StatusTypeDef HAL_GFXMMU_ModifyBuffers(GFXMMU_HandleTypeDef *hgfxmmu, GFXMMU_BuffersTypeDef *Buffers);

HAL_StatusTypeDef HAL_GFXMMU_ModifyCachePrefetch(GFXMMU_HandleTypeDef *hgfxmmu,
                                                 GFXMMU_CachePrefetchTypeDef *CachePrefetch);

void HAL_GFXMMU_IRQHandler(GFXMMU_HandleTypeDef *hgfxmmu);

void HAL_GFXMMU_ErrorCallback(GFXMMU_HandleTypeDef *hgfxmmu);
/**
  * @}
  */

/** @defgroup GFXMMU_Exported_Functions_Group3 State functions
  * @{
  */
/* State function *************************************************************/
HAL_GFXMMU_StateTypeDef HAL_GFXMMU_GetState(GFXMMU_HandleTypeDef *hgfxmmu);

uint32_t HAL_GFXMMU_GetError(GFXMMU_HandleTypeDef *hgfxmmu);
/**
  * @}
  */

/**
  * @}
  */
/* End of exported functions -------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
/** @defgroup GFXMMU_Private_Macros GFXMMU Private Macros
* @{
*/
#define IS_GFXMMU_BLOCKS_PER_LINE(VALUE) (((VALUE) == GFXMMU_256BLOCKS) || \
                                          ((VALUE) == GFXMMU_192BLOCKS))

#define IS_GFXMMU_BUFFER_ADDRESS(VALUE) (((VALUE) & 0xFU) == 0U)

#define IS_GFXMMU_CACHE_LOCK(VALUE) (((VALUE) == GFXMMU_CACHE_LOCK_DISABLE) || \
                                     ((VALUE) == GFXMMU_CACHE_LOCK_ENABLE))

#define IS_GFXMMU_CACHE_LOCK_BUFFER(VALUE) (((VALUE) == GFXMMU_CACHE_LOCK_BUFFER0) || \
                                            ((VALUE) == GFXMMU_CACHE_LOCK_BUFFER1) || \
                                            ((VALUE) == GFXMMU_CACHE_LOCK_BUFFER2) || \
                                            ((VALUE) == GFXMMU_CACHE_LOCK_BUFFER3))

#define IS_GFXMMU_CACHE_FORCE(VALUE) (((VALUE) == GFXMMU_CACHE_FORCE_DISABLE) || \
                                      ((VALUE) == GFXMMU_CACHE_FORCE_ENABLE))

#define IS_GFXMMU_OUTTER_BUFFERABILITY(VALUE) (((VALUE) == GFXMMU_OUTTER_BUFFERABILITY_DISABLE) || \
                                               ((VALUE) == GFXMMU_OUTTER_BUFFERABILITY_ENABLE))

#define IS_GFXMMU_OUTTER_CACHABILITY(VALUE) (((VALUE) == GFXMMU_OUTTER_CACHABILITY_DISABLE) || \
                                             ((VALUE) == GFXMMU_OUTTER_CACHABILITY_ENABLE))

#define IS_GFXMMU_PREFETCH(VALUE) (((VALUE) == GFXMMU_PREFETCH_DISABLE) || \
                                   ((VALUE) == GFXMMU_PREFETCH_ENABLE))

#define IS_GFXMMU_INTERRUPTS(VALUE) (((VALUE) & 0x1FU) != 0U)

#define IS_GFXMMU_LUT_LINE(VALUE) ((VALUE) < 1024U)

#define IS_GFXMMU_LUT_LINES_NUMBER(VALUE) (((VALUE) > 0U) && ((VALUE) <= 1024U))

#define IS_GFXMMU_LUT_LINE_STATUS(VALUE) (((VALUE) == GFXMMU_LUT_LINE_DISABLE) || \
                                          ((VALUE) == GFXMMU_LUT_LINE_ENABLE))

#define IS_GFXMMU_LUT_BLOCK(VALUE) ((VALUE) < 256U)

#define IS_GFXMMU_LUT_LINE_OFFSET(VALUE) (((VALUE) >= -4080) && ((VALUE) <= 4190208))

#define IS_GFXMMU_CACHE_FORCE_ACTION(VALUE) (((VALUE) == GFXMMU_CACHE_FORCE_FLUSH) || \
                                             ((VALUE) == GFXMMU_CACHE_FORCE_INVALIDATE) || \
                                             ((VALUE) == (GFXMMU_CACHE_FORCE_FLUSH | GFXMMU_CACHE_FORCE_INVALIDATE)))
/**
  * @}
  */ 
/* End of private macros -----------------------------------------------------*/

/**
  * @}
  */ 

/**
  * @}
  */
#endif /* GFXMMU */
#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_GFXMMU_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
