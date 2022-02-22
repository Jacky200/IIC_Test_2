#include <stdio.h>
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "eeprom.h"


//写一个字节的数据
void EEPROM_WirteByte(uint16_t addr,uint8_t data){
    uint8_t write_data[10];
    uint8_t data_num;
    
    if(EEPROM_WORD_ADDR_SIZE==0x08){//判别型号
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
    
    //发送给数据和地址
    if(HAL_I2C_Master_Transmit(&hi2c,EEPROM_DEV_ADDR | EEPROM_WR,write_data,data_num,3000)!=HAL_OK){
        Error_Handler();
    }
    while(HAL_I2C_GetState(&hi2c)!=HAL_I2C_STATE_READY);

}

//读一个字节
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
    
    //发送数据
    if(HAL_I2C_Master_Transmit(&hi2c,EEPROM_DEV_ADDR | EEPROM_WR,write_data,data_num,300)!=HAL_OK){
        Error_Handler();
    }
    while(HAL_I2C_GetState(&hi2c)!=HAL_I2C_STATE_READY);
    //接收数据
    if(HAL_I2C_Master_Receive(&hi2c,EEPROM_DEV_ADDR | EEPROM_RD,pdata,1,300)!=HAL_OK){
        Error_Handler();
    }
}

//写N个字节的数据
void EEPROM_WriteNByte(uint16_t addr,uint8_t *pdata,uint16_t size){
    uint16_t i=0;
    
    for(;i<size;i++){
        EEPROM_WirteByte(addr,pdata[i]);
        addr++;
        HAL_Delay(10);//期间要间隔至少5ms
    }
}

void EEPROM_ReadNByte(uint16_t addr,uint8_t *pdata,uint16_t size){
    uint8_t i=0;
    for(;i<size;i++){
        EEPROM_ReadByte(addr,&pdata[i]);
        addr++;
    }

}
