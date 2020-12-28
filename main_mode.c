#include <xc.h>
#include "initialize.h"
#include "master/i2c_master.h"
#include "master/init_master.h"
#include "slave/i2c_slave.h"
#include "slave/init_slave.h"

#define LEADER_ID 0x67
#define single 0xBC //�n�ǵ�leader����

uint8_t mode_id=0x00;
uint8_t be_master=0x00; //0=��l 1=master 2=slave
uint8_t init_be_slave=0x00; //0=slave 1=master

int i=0;//�Ψӳ]�m�@�}�l��slave��delay�ɶ�

void main(void) {
    init();

    while(1){
    

    while((be_master == 0x02)||(init_be_slave==0x00)){//slave
        slave_init(mode_id);//�N�s���]������slave��mode��ID    RA2=1

        //�N���(0xDB)�ǵ�leader
        
        //�p�G�o�q�ɶ��L���A�N�নmaster
//        for(i=0;i<=10;i++);
//        if(i==9){
            init_be_slave=0x01;
            be_master=0x01;
            RA2=0;
//        }
    }
    
    while(be_master == 0x01){//master
        master_init();

        //�o�H����leader(slave)
        I2C_Master_Start();
        I2C_Master_Write((LEADER_ID << 1)|0); //7 bit address + Write(0)
        I2C_Master_Write(single);//�ǫH����leader
        I2C_Master_Stop();

        //��leader(slave)�n�s��
        I2C_Master_Start(); 
        I2C_Master_Write((LEADER_ID << 1)|1); //7 bit address + Read(1)
        mode_id=I2C_Master_Read(0);//����leader�n�w�q���s��
        I2C_Master_Stop(); 

        //�i�H������slave�F
        be_master = 0x02;
    }
    }
//    while(1);
}
