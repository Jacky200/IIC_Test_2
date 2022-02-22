#include"i2c.h"
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include "stm32f1xx_hal_i2c.h"

I2C_HandleTypeDef hi2c;

//初始化I2C速率和地址格式
void I2C_Init(void){
    hi2c.Instance =I2Cx;  //I2C寄存器基地址
    hi2c.Init.ClockSpeed    =I2Cx_ClockSpeed;
    hi2c.Init.DutyCycle     =I2C_DUTYCYCLE_2;   //I2C的SCL时钟占空比
    hi2c.Init.GeneralCallMode=I2C_GENERALCALL_DISABLE;//设置广播呼叫模式
    hi2c.Init.NoStretchMode =I2C_NOSTRETCH_DISABLE;//设置禁止时钟延长模式
    hi2c.Init.AddressingMode=I2C_ADDRESSINGMODE_7BIT;//设置I2C寻址长度
    hi2c.Init.DualAddressMode=I2C_DUALADDRESS_DISABLE;//是否使用两个STM32的设备地址
    hi2c.Init.OwnAddress1    =0x0A;     //STM32的设备地址1（支持7和10bit）
    hi2c.Init.OwnAddress2    =0;        //STM32的设备地址2（只支持7bit）
    
    if(HAL_I2C_Init(&hi2c)!=HAL_OK){
        Error_Handler();
    }
}

//使能I2C时钟，引脚时钟，并设置复位

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c){
    GPIO_InitTypeDef GPIO_InitStruct;
    if(hi2c->Instance==I2Cx){
        I2Cx_CLK_EN(); //使能I2C时钟
        SCL_PIN_CLK_EN(); //使能引脚时钟
        SDA_PIN_CLK_EN();
        
        GPIO_InitStruct.Pin=SCL_PIN;
        GPIO_InitStruct.Mode=GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pull=GPIO_NOPULL;
        
        HAL_GPIO_Init(SCL_PORT,&GPIO_InitStruct);
        
        GPIO_InitStruct.Pin=SDA_PIN;
        HAL_GPIO_Init(SDA_PORT,&GPIO_InitStruct);
    
        I2Cx_FORCE_RESET(); //强制复位
        I2Cx_RELEASE_RESET();//释放复位  I2C初始化后 有一定概率 处于总线忙碌，返回I2C_BUSY强制复位有改善
    }

}
