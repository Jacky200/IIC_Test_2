#include"i2c.h"
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include "stm32f1xx_hal_i2c.h"

I2C_HandleTypeDef hi2c;

//��ʼ��I2C���ʺ͵�ַ��ʽ
void I2C_Init(void){
    hi2c.Instance =I2Cx;  //I2C�Ĵ�������ַ
    hi2c.Init.ClockSpeed    =I2Cx_ClockSpeed;
    hi2c.Init.DutyCycle     =I2C_DUTYCYCLE_2;   //I2C��SCLʱ��ռ�ձ�
    hi2c.Init.GeneralCallMode=I2C_GENERALCALL_DISABLE;//���ù㲥����ģʽ
    hi2c.Init.NoStretchMode =I2C_NOSTRETCH_DISABLE;//���ý�ֹʱ���ӳ�ģʽ
    hi2c.Init.AddressingMode=I2C_ADDRESSINGMODE_7BIT;//����I2CѰַ����
    hi2c.Init.DualAddressMode=I2C_DUALADDRESS_DISABLE;//�Ƿ�ʹ������STM32���豸��ַ
    hi2c.Init.OwnAddress1    =0x0A;     //STM32���豸��ַ1��֧��7��10bit��
    hi2c.Init.OwnAddress2    =0;        //STM32���豸��ַ2��ֻ֧��7bit��
    
    if(HAL_I2C_Init(&hi2c)!=HAL_OK){
        Error_Handler();
    }
}

//ʹ��I2Cʱ�ӣ�����ʱ�ӣ������ø�λ

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c){
    GPIO_InitTypeDef GPIO_InitStruct;
    if(hi2c->Instance==I2Cx){
        I2Cx_CLK_EN(); //ʹ��I2Cʱ��
        SCL_PIN_CLK_EN(); //ʹ������ʱ��
        SDA_PIN_CLK_EN();
        
        GPIO_InitStruct.Pin=SCL_PIN;
        GPIO_InitStruct.Mode=GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pull=GPIO_NOPULL;
        
        HAL_GPIO_Init(SCL_PORT,&GPIO_InitStruct);
        
        GPIO_InitStruct.Pin=SDA_PIN;
        HAL_GPIO_Init(SDA_PORT,&GPIO_InitStruct);
    
        I2Cx_FORCE_RESET(); //ǿ�Ƹ�λ
        I2Cx_RELEASE_RESET();//�ͷŸ�λ  I2C��ʼ���� ��һ������ ��������æµ������I2C_BUSYǿ�Ƹ�λ�и���
    }

}
