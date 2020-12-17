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
    master_init();//mode�@�}�l����master
    
    //�o�H����leader(slave)
    I2C_Master_Start();
    I2C_Master_Write((LEADER_ID << 1)|0); //7 bit address + Write(0)
    I2C_Master_Write(single);//�ǫH����leader
    I2C_Master_Stop();
    
    //��leader(slave)�n�s��
    I2C_Master_Start(); 
    I2C_Master_Write((LEADER_ID << 1)|1); //7 bit address + Read(1)
    leader_feedback=I2C_Master_Read(1);//����leader�n�w�q���s��
    I2C_Master_Stop();//�|�L2s�~stop
    
    //���ұ����쪺�s���O�_���T
    if(leader_feedback==0x5A){
        RA2=1;
        //������SLAVE
        init();
        slave_init(leader_feedback);//�N�s��(0X5A)�]������slave��mode��ID
        RA3=1;
        for(int i=0;i<=4000;i++){
            SSP1CON1bits.CKP = 0;
        }
    }
    
    //�N���(0xDB)�ǵ�leader
    
    while(1);
}
