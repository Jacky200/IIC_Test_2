#ifndef _I2C_H
#define _I2C_h
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include "stm32f1xx_hal_conf.h"

#define I2Cx        I2C1
#define I2Cx_CLK_EN()      __HAL_RCC_I2C1_CLK_ENABLE()  //使能I2C1的GPIO时钟

#define I2Cx_ClockSpeed     (400000)
#define I2Cx_FORCE_RESET()  __HAL_RCC_I2C1_FORCE_RESET();
#define I2Cx_RELEASE_RESET()  __HAL_RCC_I2C1_RELEASE_RESET();

#define SCL_PIN     GPIO_PIN_6
#define SCL_PORT    GPIOB
#define SCL_PIN_CLK_EN()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define SDA_PIN     GPIO_PIN_7
#define SDA_PORT    GPIOB
#define SDA_PIN_CLK_EN()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_TIMEOUT_MAX        300

extern I2C_HandleTypeDef hi2c;

void I2C_Init(void);

#endif
