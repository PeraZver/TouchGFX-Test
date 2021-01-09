/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "ili9341.h"
#include "xpt2046.h"

extern "C" {
static void ConvXPTtoILI(uint16_t *x, uint16_t *y)
{
	int16_t tx,ty;
	tx = (int16_t)(((int32_t)*x - XPT_XMIN) * GUI_WIDTH / XPT_WIDTH);
	tx = (tx < 0) ? 0 : tx;
	tx = (tx >= GUI_WIDTH) ? GUI_WIDTH-1 : tx;
	ty = (int16_t)(((int32_t)*y - XPT_YMIN) * GUI_HEIGHT / XPT_HEIGHT);
	ty = (ty < 0) ? 0 : ty;
	ty = (ty >= GUI_HEIGHT) ? GUI_HEIGHT-1 : ty;
	*x = tx;
	*y = ty;
}
}

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */

}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
	static uint16_t prevx = GUI_WIDTH;
	static uint16_t prevy = GUI_HEIGHT;
	uint16_t intx, inty;
	XPT2046_Update(&intx, &inty);
	if (XPT2046_IsReasonable(intx, inty)) {
		ConvXPTtoILI(&intx, &inty);
		if (intx != prevx || inty != prevy) {
			prevx = intx;
			prevy = inty;
			x = (int32_t)intx;
			y = (int32_t)inty;
			return true;
		}
	}
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
