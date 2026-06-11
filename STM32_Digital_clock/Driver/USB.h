#ifndef __USB_H
#define __USB_H
#include <stdint.h>
//------------------------TYPEDEF---------------------------------------------
#define __IO   volatile
typedef enum{
	RESET = 0,
	SET = !RESET
}FlagStatus ;


typedef struct {
    union {
        __IO uint32_t WORD;
        struct {
            __IO uint32_t EA         : 4;
            __IO uint32_t STAT_TX    : 2;
            __IO uint32_t DTOG_TX    : 1;
            __IO uint32_t CTR_TX     : 1;
            __IO uint32_t EP_KIND    : 1;
            __IO uint32_t EPTYPE     : 2;
            __IO uint32_t SETUP      : 1;
            __IO uint32_t STAT_RX    : 2;
            __IO uint32_t DTOG_RX    : 1;
            __IO uint32_t CTR_RX     : 1;
        } BITS;
    } EPnRp[8];

    uint32_t                    : 32;   /* 0x20 */
    uint32_t                    : 32;   /* 0x24 */
    uint32_t                    : 32;   /* 0x28 */
    uint32_t                    : 32;   /* 0x2C */
    uint32_t                    : 32;   /* 0x30 */
    uint32_t                    : 32;   /* 0x34 */
    uint32_t                    : 32;   /* 0x38 */
    uint32_t                    : 32;   /* 0x3C */

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t FRES       : 1;
            __IO uint32_t PDWN       : 1;
            __IO uint32_t LPMODE     : 1;
            __IO uint32_t FSUSP      : 1;
            __IO uint32_t RESUME     : 1;
            __IO uint32_t            : 3;
            __IO uint32_t ESOFM      : 1;
            __IO uint32_t SOFM       : 1;
            __IO uint32_t RESETM     : 1;
            __IO uint32_t SUSPM      : 1;
            __IO uint32_t WKUPM      : 1;
            __IO uint32_t ERRM       : 1;
            __IO uint32_t PMAOVRM    : 1;
            __IO uint32_t CTRM       : 1;
        } BITS;
    } CNTR;

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t EP_ID      : 4;
            __IO uint32_t DIR        : 1;
            __IO uint32_t            : 3;
            __IO uint32_t ESOF       : 1;
            __IO uint32_t SOF        : 1;
            __IO uint32_t RESET      : 1;
            __IO uint32_t SUSP       : 1;
            __IO uint32_t WKUP       : 1;
            __IO uint32_t ERR        : 1;
            __IO uint32_t PMAOVR     : 1;
            __IO uint32_t CTR        : 1;
        } BITS;
    } ISTR;

    union {
        __IO uint32_t WORD;

        struct {
            __IO uint32_t FN         : 11;
            __IO uint32_t LSOF       : 2;
            __IO uint32_t LCK        : 1;
            __IO uint32_t RXDM       : 1;
            __IO uint32_t RXDP       : 1;
        } BITS;
    } FNR;

    union {
        __IO uint32_t WORD;

        struct
        {
            __IO uint32_t ADD        : 7;
            __IO uint32_t EF         : 1;
        } BITS;
    } DADDR;

    __IO uint32_t BTABLE;
} USB_Typedef;

#define USB_ADD_BASE        0x40005C00
#define USB                 ((USB_Typedef*)(USB_ADD_BASE))
void USB_Init(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void USB_ResetCallBack(void);
void USB_TransactionCallBack(void);

#endif
