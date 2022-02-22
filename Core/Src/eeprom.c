#include <stdio.h>
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "eeprom.h"


//дһ���ֽڵ�����
void EEPROM_WirteByte(uint16_t addr,uint8_t data){
    uint8_t write_data[10];
    uint8_t data_num;
    
    if(EEPROM_WORD_ADDR_SIZE==0x08){//�б��ͺ�
        write_data[0]=(uint8_t)(addr & 0x00ff);
        write_data[1]=data;
        data_num=2;
    }else
    {
        write_data[0]=(uint8_t)(addr>>8);
        write_data[1]=(uint8_t)(addr & 0xff);
        write_data[2]=data;
        data_num=3;
    }
    
    //���͸����ݺ͵�ַ
    if(HAL_I2C_Master_Transmit(&hi2c,EEPROM_DEV_ADDR | EEPROM_WR,write_data,data_num,3000)!=HAL_OK){
        Error_Handler();
    }
    while(HAL_I2C_GetState(&hi2c)!=HAL_I2C_STATE_READY);

}

//��һ���ֽ�
void EEPROM_ReadByte(uint16_t addr,uint8_t *pdata){
    uint8_t write_data[10];
    uint8_t data_num;
    
    if(EEPROM_WORD_ADDR_SIZE==0x08){
        write_data[0]=(uint8_t)(addr & 0x00ff);
        data_num=1;
    }
    else{
        write_data[0]=(uint8_t)(addr>>8);
        write_data[1]=(uint8_t)(addr & 0x00ff);
        data_num=2;
    }
    
    //��������
    if(HAL_I2C_Master_Transmit(&hi2c,EEPROM_DEV_ADDR | EEPROM_WR,write_data,data_num,300)!=HAL_OK){
        Error_Handler();
    }
    while(HAL_I2C_GetState(&hi2c)!=HAL_I2C_STATE_READY);
    //��������
    if(HAL_I2C_Master_Receive(&hi2c,EEPROM_DEV_ADDR | EEPROM_RD,pdata,1,300)!=HAL_OK){
        Error_Handler();
    }
}

//дN���ֽڵ�����
void EEPROM_WriteNByte(uint16_t addr,uint8_t *pdata,uint16_t size){
    uint16_t i=0;
    
    for(;i<size;i++){
        EEPROM_WirteByte(addr,pdata[i]);
        addr++;
        HAL_Delay(10);//�ڼ�Ҫ�������5ms
    }
}

void EEPROM_ReadNByte(uint16_t addr,uint8_t *pdata,uint16_t size){
    uint8_t i=0;
    for(;i<size;i++){
        EEPROM_ReadByte(addr,&pdata[i]);
        addr++;
    }

}
