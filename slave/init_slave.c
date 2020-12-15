#include <pic16f18854.h>
#include "init_slave.h"

void slave_init(uint8_t address){
    SSP1STAT = 0xC0;//�����J�޿�
    SSP1ADD = (uint8_t)(address<<1);
    SSP1MSK = 0xFF;
    SSP1CON1 = 0x26;
    SSP1CON2 = 0x01;
    SSP1CON3 = 0x00;//�ݨ쪺��Ƴ����]�o�ӡAı�o���I��
    SSP1CON3bits.BOEN=1;//��sSSP1BUF
    SSP1BUF = 0x00;
    GIE = 1;//���_����
    PEIE = 1;//���_����
    PIR3bits.SSP1IF = 0;//���ݶǿ�
    PIR3bits.BCL1IF = 0;//���˴���Ĭ�
    PIE3bits.SSP1IE = 1;//���\���_
    PIE3bits.BCL1IE = 1;//�Ĭ𤹳\���_
}
