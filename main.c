#include "msp.h"
//#include "msp432p401r_classic.h"
#include <stdint.h>

/**
 * main.c
 */


void main(void)
{
    uint16_t data[8];
    uint16_t decrypt_data[8];
    int i=0;
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//selecting mode and key length
	AESACTL0 = 0x1000; //enable the AESRDY interrupt flag
	//load the aes key
	for(i=0; i<8; i++){
	    AESAKEY=0xFF;//8 half words
	}
	AESASTAT |= BIT1;
	//loading the data
	for(i=0; i<8; i++){
	    AESADIN=0x1111;//8 half words
	    //AESAXDIN=0x1111;//x-or ???
	    //AESAXIN=0x1111;
	}
	AESASTAT |= BIT2;

	//encryption starts automatically
	while(1)
	{
	    if(AESACTL0==0x1100){
	        AESACTL0 ^= BIT8;//interrupt flag disabled
            int j=0;
            for(j=0; j<8; j++){
                data[j]=AESADOUT;
            }
            break;
	    }
	}
	//////////////////////
	//decryption process
	AESACTL0 = 0x1001;
	//I changed AESOPx so I need to set AESKEYWR in order to use the same key for decryption
	AESASTAT |= BIT1;

	for(i=0; i<8; i++){
	    AESADIN=data[i];
	}

	AESASTAT |= BIT2;

	while(1){
	    if(AESACTL0==0x1101){
	        AESACTL0 ^= BIT8;
	        int j=0;
	        for(j=0; j<8; j++){
	            decrypt_data[j]=AESADOUT;
	        }
	        //break;
	    }
	}
}
//#pragma vector=AES256_IRQHandler
/*__interrupt void AES256_IRQHandler(void)
{
    int j=0;
    for(j=0; j<8; j++){
        data[j]=AESADOUT;
    }//do something
}*/
