#include <xc.h>
#include "init_master.h"

void master_init(void){
    INTCONbits.GIE = 0;//���_������
    INTCONbits.PEIE = 0;//���_������
    PIR3bits.SSP1IF = 1;//���ݶǿ�
    PIR3bits.BCL1IF = 1;//���˴���Ĭ�
    PIE3bits.SSP1IE = 0;//�����\���_
    PIE3bits.BCL1IE = 0;//�Ĭ𤣤��\���_
    SSP1CON1=0x00;
    SSP1CON1=0x28;
    SSP1CON2=0x00;
    SSP1CON3 = 0x00;
    SSP1STAT=0x00;
    SSP1BUF = 0x00;
    SSP1STATbits.SMP=1; //1 =�b�зǳt�׼Ҧ��]100 kHz�M1 MHz�^�U�T��slew rate control
    SSP1STATbits.CKE=1; //1 =�����J�޿�A�H���H�ȲŦXSMBus�W�d
    SSP1ADD=0x06;//100k Hz=0x06 �Ʀr�V���W�v�V�C
    SSP1MSK=0xFF;
}
