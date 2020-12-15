#include <xc.h>
#include "init_master.h"

void master_init(void){
    SSP1CON1=0b00101000;
    SSP1CON2=0x00;
    SSP1STATbits.SMP=1; //1 =�b�зǳt�׼Ҧ��]100 kHz�M1 MHz�^�U�T��slew rate control
    SSP1STATbits.CKE=1; //1 =�����J�޿�A�H���H�ȲŦXSMBus�W�d
    SSP1ADD=0x06;//100k Hz
    SSP1MSK=0xFF;
}
