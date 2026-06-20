#ifndef __AFAO_H
#define __AFAO_H

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    union
    {
        uint32_t REG;
        struct
        {
            uint32_t PIN: 4;
            uint32_t PORT: 3;
            uint32_t EVOE: 1;
            uint32_t Resever: 24;
        } BIST;
    } EVCR;

    uint32_t MAPR;

    union
    {
        uint32_t REG;
        struct
        {
            uint32_t EXTI0: 4;
            uint32_t EXTI1: 4;
            uint32_t EXTI2: 4;
            uint32_t EXTI3: 4;
            uint32_t reserver: 16;
        } BIST;
    } EXTICR1;

    union
    {
        uint32_t REG;
        struct
        {
            uint32_t EXTI0: 4;
            uint32_t EXTI1: 4;
            uint32_t EXTI2: 4;
            uint32_t EXTI3: 4;
            uint32_t reserver: 16;
        } BIST;
    } EXTICR2;

    union
    {
        uint32_t REG;
        struct
        {
            uint32_t EXTI0: 4;
            uint32_t EXTI1: 4;
            uint32_t EXTI2: 4;
            uint32_t EXTI3: 4;
            uint32_t reserver: 16;
        } BIST;
    } EXTICR3;

    union
    {
        uint32_t REG;
        struct
        {
            uint32_t EXTI0: 4;
            uint32_t EXTI1: 4;
            uint32_t EXTI2: 4;
            uint32_t EXTI3: 4;
            uint32_t reserver: 16;
        } BIST;
    } EXTICR4;

    uint32_t MAPR2;


} AFIO_Typedef;


#define AFIO     ((volatile AFIO_Typedef*)0x40010000UL)
#endif
