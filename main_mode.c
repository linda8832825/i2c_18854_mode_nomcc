#include <xc.h>
#include "initialize.h"
#include "master/i2c_master.h"
#include "master/init_master.h"
#include "slave/i2c_slave.h"
#include "slave/init_slave.h"

#define LEADER_ID 0x67
#define single 0xBC //要傳給leader的值

uint8_t mode_id=0x00;
uint8_t be_master=0x00; //0=初始 1=master 2=slave
uint8_t init_be_slave=0x00; //0=slave 1=master

int i=0;//用來設置一開始當slave的delay時間

void main(void) {
    init();

    while(1){
    

    while((be_master == 0x02)||(init_be_slave==0x00)){//slave
        slave_init(mode_id);//將編號設為成為slave的mode的ID    RA2=1

        //將資料(0xDB)傳給leader
        
        //如果這段時間過完，就轉成master
//        for(i=0;i<=10;i++);
//        if(i==9){
            init_be_slave=0x01;
            be_master=0x01;
            RA2=0;
//        }
    }
    
    while(be_master == 0x01){//master
        master_init();

        //發信號給leader(slave)
        I2C_Master_Start();
        I2C_Master_Write((LEADER_ID << 1)|0); //7 bit address + Write(0)
        I2C_Master_Write(single);//傳信號給leader
        I2C_Master_Stop();

        //跟leader(slave)要編號
        I2C_Master_Start(); 
        I2C_Master_Write((LEADER_ID << 1)|1); //7 bit address + Read(1)
        mode_id=I2C_Master_Read(0);//接收leader要定義的編號
        I2C_Master_Stop(); 

        //可以切換成slave了
        be_master = 0x02;
    }
    }
//    while(1);
}
