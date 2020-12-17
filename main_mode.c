#include <xc.h>
#include "initialize.h"
#include "master/i2c_master.h"
#include "master/init_master.h"
#include "slave/i2c_slave.h"
#include "slave/init_slave.h"

#define LEADER_ID 0x67
#define single 0xBC

uint8_t leader_feedback=0x00;

void main(void) {
    init();
    PORTA=0X00;
    master_init();//mode一開始先當master
    
    //發信號給leader(slave)
    I2C_Master_Start();
    I2C_Master_Write((LEADER_ID << 1)|0); //7 bit address + Write(0)
    I2C_Master_Write(single);//傳信號給leader
    I2C_Master_Stop();
    
    //跟leader(slave)要編號
    I2C_Master_Start(); 
    I2C_Master_Write((LEADER_ID << 1)|1); //7 bit address + Read(1)
    leader_feedback=I2C_Master_Read(1);//接收leader要定義的編號
    I2C_Master_Stop();//會過2s才stop
    
    //驗證接收到的編號是否正確
    if(leader_feedback==0x5A){
        RA2=1;
        //切換成SLAVE
        init();
        slave_init(leader_feedback);//將編號(0X5A)設為成為slave的mode的ID
        RA3=1;
        for(int i=0;i<=4000;i++){
            SSP1CON1bits.CKP = 0;
        }
    }
    
    //將資料(0xDB)傳給leader
    
    while(1);
}
