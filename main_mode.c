#include <xc.h>
#include "initialize.h"
#include "master/i2c_master.h"
#include "master/init_master.h"
#include "slave/i2c_slave.h"
#include "slave/init_slave.h"

#define LEADER_ID 0x67
#define single 0xBC

uint8_t mode_id=0x00;
uint8_t ever_be_master=0x00;

void main(void) {
    init();
//    while(1){
        while(ever_be_master == 0x00){//master
            master_init();//mode�@�}�l����master

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
            ever_be_master = 0x01;
        }

        while(ever_be_master == 0x01){//slave
            slave_init(mode_id);//�N�s���]������slave��mode��ID    RA2=1

            //�N���(0xDB)�ǵ�leader
        }
//    }
    while(1);
}
