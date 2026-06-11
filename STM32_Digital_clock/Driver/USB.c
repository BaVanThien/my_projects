#include"USB.h"
#include"EXTI.h"

void USB_Init(void){
	//Enable interupt mask 

	USB->CNTR.WORD = 0xBF00;
	// force  reset
	USB->CNTR.BITS.FRES = 0x01;
	USB->CNTR.BITS.FRES = 0x00;
	NVIC_USB_En();
}
void USB_ResetCallBack(void){
}
void USB_TransactionCallBack(void){
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if (USB->ISTR.BITS.RESET != RESET) 
    {
        USB_ResetCallBack();
    }

    if (USB->ISTR.BITS.CTR != RESET)
    {
        USB_TransactionCallBack();
    }

    if (USB->ISTR.BITS.ERR != RESET)
    {
        USB->ISTR.BITS.ERR = 0;
    }

    if (USB->ISTR.BITS.SOF != RESET)
    {
        USB->ISTR.BITS.SOF = 0;
    }

    if (USB->ISTR.BITS.ESOF != RESET)
    {
        USB->ISTR.BITS.ESOF = 0;
    }

    if (USB->ISTR.BITS.SUSP != RESET)
    {
        USB->ISTR.BITS.SUSP = 0;
    }
}