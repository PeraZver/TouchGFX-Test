/**
  ******************************************************************************
  * File Name          : OSWrappers.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include <stm32f4xx_hal.h>
#include <TouchGFXHAL.hpp>
#include <touchgfx/hal/OSWrappers.hpp>

static volatile uint32_t fb_sem;
static volatile uint32_t vsync_sem;

using namespace touchgfx;

/*
 * Initialize frame buffer semaphore and queue/mutex for VSYNC signal.
 */
void OSWrappers::initialize()
{
  fb_sem = 0;
  vsync_sem = 0;
}

/*
 * Take the frame buffer semaphore. Blocks until semaphore is available.
 */
void OSWrappers::takeFrameBufferSemaphore()
{
  while(fb_sem);
  fb_sem = 1;
}

/*
 * Release the frame buffer semaphore.
 */
void OSWrappers::giveFrameBufferSemaphore()
{
  fb_sem = 0;
}

/*
 * Attempt to obtain the frame buffer semaphore. If semaphore is not available, do
 * nothing.
 *
 * Note must return immediately! This function does not care who has the taken the semaphore,
 * it only serves to make sure that the semaphore is taken by someone.
 */
void OSWrappers::tryTakeFrameBufferSemaphore()
{
  fb_sem = 1;
}

/*
 * Release the frame buffer semaphore in a way that is safe in interrupt context. Called
 * from ISR.
 *
 * Release the frame buffer semaphore in a way that is safe in interrupt context.
 * Called from ISR.
 */
void OSWrappers::giveFrameBufferSemaphoreFromISR()
{
  fb_sem = 0;
}

/*
 * Signal that a VSYNC has occurred. Should make the vsync queue/mutex available.
 *
 * Note This function is called from an ISR, and should (depending on OS) trigger a
 * scheduling.
 */
void OSWrappers::signalVSync()
{
  vsync_sem = 1;
}

/*
  * Signal that the rendering of the frame has completed. Used by
  * some systems to avoid using any previous vsync.
  */
void OSWrappers::signalRenderingDone()
{
    vsync_sem = 0;
}

/*
 * This function checks if a VSync occurred after last rendering.
 * The function is used in systems that cannot wait in  waitForVSync
 * (because they are also checking other event sources.
 *
 * @note signalRenderingDone is typically used together with this function.
 *
 * @return True if VSync occurred.
 */
bool OSWrappers::isVSyncAvailable()
{
  return vsync_sem;
}

/*
 * This function check if a VSYNC has occured.
 * If VSYNC has occured, signal TouchGFX to start a rendering
 */
void OSWrappers::waitForVSync()
{
  if(vsync_sem)
  {
    vsync_sem = 0;
    HAL::getInstance()->backPorchExited();
  }
}

/*
 * A function that causes executing task to sleep for a number of milliseconds.
 *
 * A function that causes executing task to sleep for a number of milliseconds.
 * This function is OPTIONAL. It is only used by the TouchGFX in the case of
 * a specific frame refresh strategy (REFRESH_STRATEGY_OPTIM_SINGLE_BUFFER_TFT_CTRL).
 * Due to backwards compatibility, in order for this function to be useable by the HAL
 * the function must be explicitly registered:
 * hal.registerTaskDelayFunction(&OSWrappers::taskDelay)
 *
 * see HAL::setFrameRefreshStrategy(FrameRefreshStrategy s)
 * see HAL::registerTaskDelayFunction(void (*delayF)(uint16_t))
 */
void OSWrappers::taskDelay(uint16_t ms)
{
    HAL_Delay(ms);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
