/**
    Copyright 2022, 王思远 <darknightghost.cn@gmail.com>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <common/types.h>

// Definations of STC8Gxx
#if defined EDITOR_AUTO_COMPLETE
    #define INT_INT0
    #define INT_TIMER0
    #define INT_INT1
    #define INT_TIMER1
    #define INT_UART1
    #define INT_SPI
    #define INT_INT2
    #define INT_TIMER2
    #define INT_TIMER3
    #define INT_I2C
    #define INT_DMA_SPI
    #define INT_DMA_UR1T
    #define INT_DMA_UR1R

#else
    #define INT_INT0     0
    #define INT_TIMER0   1
    #define INT_INT1     2
    #define INT_TIMER1   3
    #define INT_UART1    4
    #define INT_SPI      9
    #define INT_INT2     10
    #define INT_TIMER2   12
    #define INT_TIMER3   19
    #define INT_I2C      24
    #define INT_DMA_SPI  49
    #define INT_DMA_UR1T 50
    #define INT_DMA_UR1R 51

#endif

// Mode switch.
__sfr __at(0xA2) P_SW1;
__sfr __at(0xBA) P_SW2;

// System clock.
#define CKSEL    (*((volatile __xdata register_t *)0xFE00))
#define CLKDIV   (*((volatile __xdata register_t *)0xFE01))
#define HIRCCR   (*((volatile __xdata register_t *)0xFE02))
#define XOSCCR   (*((volatile __xdata register_t *)0xFE03))
#define IRC32KCR (*((volatile __xdata register_t *)0xFE04))
#define MCLKOCR  (*((volatile __xdata register_t *)0xFE05))

// I/O ports.
// P0
__sfr  __at(0x80) P0;
__sbit __at(0x80) P0_0;
__sbit __at(0x81) P0_1;
__sbit __at(0x82) P0_2;
__sbit __at(0x83) P0_3;
__sbit __at(0x84) P0_4;
__sbit __at(0x85) P0_5;
__sbit __at(0x86) P0_6;
__sbit __at(0x87) P0_7;

__sfr __at(0x93) P0M1;
__sfr __at(0x94) P0M0;

#define P0PU  (*((volatile __xdata register_t *)0xFE10))
#define P0NCS (*((volatile __xdata register_t *)0xFE18))
#define P0SR  (*((volatile __xdata register_t *)0xFE20))
#define P0DR  (*((volatile __xdata register_t *)0xFE28))
#define P0IE  (*((volatile __xdata register_t *)0xFE30))

// P1
__sfr  __at(0x90) P1;
__sbit __at(0x90) P1_0;
__sbit __at(0x91) P1_1;
__sbit __at(0x92) P1_2;
__sbit __at(0x93) P1_3;
__sbit __at(0x94) P1_4;
__sbit __at(0x95) P1_5;
__sbit __at(0x96) P1_6;
__sbit __at(0x97) P1_7;

__sfr __at(0x91) P1M1;
__sfr __at(0x92) P1M0;

#define P1PU  (*((volatile __xdata register_t *)0xFE11))
#define P1NCS (*((volatile __xdata register_t *)0xFE19))
#define P1SR  (*((volatile __xdata register_t *)0xFE21))
#define P1DR  (*((volatile __xdata register_t *)0xFE29))
#define P1IE  (*((volatile __xdata register_t *)0xFE31))

// P2
__sfr  __at(0xA0) P2;
__sbit __at(0xA0) P2_0;
__sbit __at(0xA1) P2_1;
__sbit __at(0xA2) P2_2;
__sbit __at(0xA3) P2_3;
__sbit __at(0xA4) P2_4;
__sbit __at(0xA5) P2_5;
__sbit __at(0xA6) P2_6;
__sbit __at(0xA7) P2_7;

__sfr __at(0x95) P2M1;
__sfr __at(0x96) P2M0;

#define P2PU  (*((volatile __xdata register_t *)0xFE12))
#define P2NCS (*((volatile __xdata register_t *)0xFE1A))
#define P2SR  (*((volatile __xdata register_t *)0xFE22))
#define P2DR  (*((volatile __xdata register_t *)0xFE2A))
#define P2IE  (*((volatile __xdata register_t *)0xFE32))

// P3
__sfr  __at(0xB0) P3;
__sbit __at(0xB0) P3_0;
__sbit __at(0xB1) P3_1;
__sbit __at(0xB2) P3_2;
__sbit __at(0xB3) P3_3;
__sbit __at(0xB4) P3_4;
__sbit __at(0xB5) P3_5;
__sbit __at(0xB6) P3_6;
__sbit __at(0xB7) P3_7;

__sfr __at(0xB1) P3M1;
__sfr __at(0xB2) P3M0;

#define P3PU  (*((volatile __xdata register_t *)0xFE13))
#define P3NCS (*((volatile __xdata register_t *)0xFE1B))
#define P3SR  (*((volatile __xdata register_t *)0xFE23))
#define P3DR  (*((volatile __xdata register_t *)0xFE2B))
#define P3IE  (*((volatile __xdata register_t *)0xFE33))

// P4
__sfr  __at(0xC0) P4;
__sbit __at(0xC0) P4_0;
__sbit __at(0xC1) P4_1;
__sbit __at(0xC2) P4_2;
__sbit __at(0xC3) P4_3;
__sbit __at(0xC4) P4_4;
__sbit __at(0xC5) P4_5;
__sbit __at(0xC6) P4_6;
__sbit __at(0xC7) P4_7;

__sfr __at(0xB3) P4M1;
__sfr __at(0xB4) P4M0;

#define P4PU  (*((volatile __xdata register_t *)0xFE14))
#define P4NCS (*((volatile __xdata register_t *)0xFE1C))
#define P4SR  (*((volatile __xdata register_t *)0xFE24))
#define P4DR  (*((volatile __xdata register_t *)0xFE2C))
#define P4IE  (*((volatile __xdata register_t *)0xFE34))

// P5
__sfr  __at(0xC8) P5;
__sbit __at(0xC8) P5_0;
__sbit __at(0xC9) P5_1;
__sbit __at(0xCA) P5_2;
__sbit __at(0xCB) P5_3;
__sbit __at(0xCC) P5_4;
__sbit __at(0xCD) P5_5;
__sbit __at(0xCE) P5_6;
__sbit __at(0xCF) P5_7;

__sfr __at(0xC9) P5M1;
__sfr __at(0xCA) P5M0;

#define P5PU  (*((volatile __xdata register_t *)0xFE15))
#define P5NCS (*((volatile __xdata register_t *)0xFE1D))
#define P5SR  (*((volatile __xdata register_t *)0xFE25))
#define P5DR  (*((volatile __xdata register_t *)0xFE2D))
#define P5IE  (*((volatile __xdata register_t *)0xFE35))

// Serial
__sfr  __at(0x98) SCON;
__sbit __at(0x98) R1;
__sbit __at(0x99) T1;
__sbit __at(0x9A) RB8;
__sbit __at(0x9B) TB8;
__sbit __at(0x9C) REN;
__sbit __at(0x9D) SM2;
__sbit __at(0x9E) SM1;
__sbit __at(0x9F) SM0_FE;

__sfr __at(0x99) SBUF;
__sfr __at(0x87) PCON;

__sfr __at(0x9A) S2CON;
__sfr __at(0x9B) S2BUF;

// Timer
__sfr  __at(0x88) TCON;
__sbit __at(0x88) IT0;
__sbit __at(0x89) IE0;
__sbit __at(0x8A) IT1;
__sbit __at(0x8B) IE1;
__sbit __at(0x8C) TR0;
__sbit __at(0x8D) TF0;
__sbit __at(0x8E) TR1;
__sbit __at(0x8F) TF1;

__sfr __at(0x89) TMOD;
__sfr __at(0x8A) TL0;
__sfr __at(0x8B) TL1;
__sfr __at(0x8C) TH0;
__sfr __at(0x8D) TH1;
__sfr __at(0x8E) AUXR;

__sfr __at(0xD6) T2H;
__sfr __at(0xD7) T2L;

// Interrupt
__sfr  __at(0xA8) IE;
__sbit __at(0xA8) EX0;
__sbit __at(0xA9) ET0;
__sbit __at(0xAA) EX1;
__sbit __at(0xAB) ET1;
__sbit __at(0xAC) ES;
__sbit __at(0xAD) EADC;
__sbit __at(0xAE) ELVD;
__sbit __at(0xAF) EA;

__sfr __at(0xAF) IE2;
__sfr __at(0x8F) INTCLKO;
__sfr __at(0xB8) IP;
__sfr __at(0xB7) IPH;
__sfr __at(0xB5) IP2;
__sfr __at(0xB6) IP2H;
__sfr __at(0xDF) IP3;
__sfr __at(0xEE) IP3H;

__sfr __at(0xC2) IAP_DATA;
__sfr __at(0xC3) IAP_ADDRH;
__sfr __at(0xC4) IAP_ADDRL;
__sfr __at(0xC5) IAP_CMD;
__sfr __at(0xC6) IAP_TRIG;
__sfr __at(0xC7) IAP_CONTR;
__sfr __at(0xF5) IAP_TPS;

// Watch dog.
__sfr __at(0xC1) WDT_CONTR;

// I2C
#define I2CCFG   (*((volatile __xdata register_t *)0xFE80))
#define I2CMSCR  (*((volatile __xdata register_t *)0xFE81))
#define I2CMSST  (*((volatile __xdata register_t *)0xFE82))
#define I2CSLCR  (*((volatile __xdata register_t *)0xFE83))
#define I2CSLST  (*((volatile __xdata register_t *)0xFE84))
#define I2CSLADR (*((volatile __xdata register_t *)0xFE85))
#define I2CTXD   (*((volatile __xdata register_t *)0xFE86))
#define I2CRXD   (*((volatile __xdata register_t *)0xFE87))
#define I2CMSAUX (*((volatile __xdata register_t *)0xFE88))

// DMA
#define DMA_M2M_CFG   (*((volatile __xdata register_t *)0xFA00))
#define DMA_M2M_CR    (*((volatile __xdata register_t *)0xFA01))
#define DMA_M2M_STA   (*((volatile __xdata register_t *)0xFA02))
#define DMA_M2M_AMT   (*((volatile __xdata register_t *)0xFA03))
#define DMA_M2M_DONE  (*((volatile __xdata register_t *)0xFA04))
#define DMA_M2M_TXAH  (*((volatile __xdata register_t *)0xFA05))
#define DMA_M2M_TXAL  (*((volatile __xdata register_t *)0xFA06))
#define DMA_M2M_RXAH  (*((volatile __xdata register_t *)0xFA07))
#define DMA_M2M_RXAL  (*((volatile __xdata register_t *)0xFA08))
#define DMA_ADC_CFG   (*((volatile __xdata register_t *)0xFA10))
#define DMA_ADC_CR    (*((volatile __xdata register_t *)0xFA11))
#define DMA_ADC_STA   (*((volatile __xdata register_t *)0xFA12))
#define DMA_ADC_RXAH  (*((volatile __xdata register_t *)0xFA17))
#define DMA_ADC_RXAL  (*((volatile __xdata register_t *)0xFA18))
#define DMA_ADC_CFG2  (*((volatile __xdata register_t *)0xFA19))
#define DMA_ADC_CHSW0 (*((volatile __xdata register_t *)0xFA1A))
#define DMA_ADC_CHSW1 (*((volatile __xdata register_t *)0xFA1B))
#define DMA_SPI_CFG   (*((volatile __xdata register_t *)0xFA20))
#define DMA_SPI_CR    (*((volatile __xdata register_t *)0xFA21))
#define DMA_SPI_STA   (*((volatile __xdata register_t *)0xFA22))
#define DMA_SPI_AMT   (*((volatile __xdata register_t *)0xFA23))
#define DMA_SPI_DONE  (*((volatile __xdata register_t *)0xFA24))
#define DMA_SPI_TXAH  (*((volatile __xdata register_t *)0xFA25))
#define DMA_SPI_TXAL  (*((volatile __xdata register_t *)0xFA26))
#define DMA_SPI_RXAH  (*((volatile __xdata register_t *)0xFA27))
#define DMA_SPI_RXAL  (*((volatile __xdata register_t *)0xFA28))
#define DMA_SPI_CFG2  (*((volatile __xdata register_t *)0xFA29))
#define DMA_UR1T_CFG  (*((volatile __xdata register_t *)0xFA30))
#define DMA_UR1T_CR   (*((volatile __xdata register_t *)0xFA31))
#define DMA_UR1T_STA  (*((volatile __xdata register_t *)0xFA32))
#define DMA_UR1T_AMT  (*((volatile __xdata register_t *)0xFA33))
#define DMA_UR1T_DONE (*((volatile __xdata register_t *)0xFA34))
#define DMA_UR1T_TXAH (*((volatile __xdata register_t *)0xFA35))
#define DMA_UR1T_TXAL (*((volatile __xdata register_t *)0xFA36))
#define DMA_UR1R_CFG  (*((volatile __xdata register_t *)0xFA38))
#define DMA_UR1R_CR   (*((volatile __xdata register_t *)0xFA39))
#define DMA_UR1R_STA  (*((volatile __xdata register_t *)0xFA3A))
#define DMA_UR1R_AMT  (*((volatile __xdata register_t *)0xFA3B))
#define DMA_UR1R_DONE (*((volatile __xdata register_t *)0xFA3C))
#define DMA_UR1R_RXAH (*((volatile __xdata register_t *)0xFA3D))
#define DMA_UR1R_RXAL (*((volatile __xdata register_t *)0xFA3E))
#define DMA_UR2T_CFG  (*((volatile __xdata register_t *)0xFA40))
#define DMA_UR2T_CR   (*((volatile __xdata register_t *)0xFA41))
#define DMA_UR2T_STA  (*((volatile __xdata register_t *)0xFA42))
#define DMA_UR2T_AMT  (*((volatile __xdata register_t *)0xFA43))
#define DMA_UR2T_DONE (*((volatile __xdata register_t *)0xFA44))
#define DMA_UR2T_TXAH (*((volatile __xdata register_t *)0xFA45))
#define DMA_UR2T_TXAL (*((volatile __xdata register_t *)0xFA46))
#define DMA_UR2R_CFG  (*((volatile __xdata register_t *)0xFA48))
#define DMA_UR2R_CR   (*((volatile __xdata register_t *)0xFA49))
#define DMA_UR2R_STA  (*((volatile __xdata register_t *)0xFA4A))
#define DMA_UR2R_AMT  (*((volatile __xdata register_t *)0xFA4B))
#define DMA_UR2R_DONE (*((volatile __xdata register_t *)0xFA4C))
#define DMA_UR2R_RXAH (*((volatile __xdata register_t *)0xFA4D))
#define DMA_UR2R_RXAL (*((volatile __xdata register_t *)0xFA4E))
#define DMA_UR3T_CFG  (*((volatile __xdata register_t *)0xFA50))
#define DMA_UR3T_CR   (*((volatile __xdata register_t *)0xFA51))
#define DMA_UR3T_STA  (*((volatile __xdata register_t *)0xFA52))
#define DMA_UR3T_AMT  (*((volatile __xdata register_t *)0xFA53))
#define DMA_UR3T_DONE (*((volatile __xdata register_t *)0xFA54))
#define DMA_UR3T_TXAH (*((volatile __xdata register_t *)0xFA55))
#define DMA_UR3T_TXAL (*((volatile __xdata register_t *)0xFA56))
#define DMA_UR3R_CFG  (*((volatile __xdata register_t *)0xFA58))
#define DMA_UR3R_CR   (*((volatile __xdata register_t *)0xFA59))
#define DMA_UR3R_STA  (*((volatile __xdata register_t *)0xFA5A))
#define DMA_UR3R_AMT  (*((volatile __xdata register_t *)0xFA5B))
#define DMA_UR3R_DONE (*((volatile __xdata register_t *)0xFA5C))
#define DMA_UR3R_RXAH (*((volatile __xdata register_t *)0xFA5D))
#define DMA_UR3R_RXAL (*((volatile __xdata register_t *)0xFA5E))
#define DMA_UR4T_CFG  (*((volatile __xdata register_t *)0xFA60))
#define DMA_UR4T_CR   (*((volatile __xdata register_t *)0xFA61))
#define DMA_UR4T_STA  (*((volatile __xdata register_t *)0xFA62))
#define DMA_UR4T_AMT  (*((volatile __xdata register_t *)0xFA63))
#define DMA_UR4T_DONE (*((volatile __xdata register_t *)0xFA64))
#define DMA_UR4T_TXAH (*((volatile __xdata register_t *)0xFA65))
#define DMA_UR4T_TXAL (*((volatile __xdata register_t *)0xFA66))
#define DMA_UR4R_CFG  (*((volatile __xdata register_t *)0xFA68))
#define DMA_UR4R_CR   (*((volatile __xdata register_t *)0xFA69))
#define DMA_UR4R_STA  (*((volatile __xdata register_t *)0xFA6A))
#define DMA_UR4R_AMT  (*((volatile __xdata register_t *)0xFA6B))
#define DMA_UR4R_DONE (*((volatile __xdata register_t *)0xFA6C))
#define DMA_UR4R_RXAH (*((volatile __xdata register_t *)0xFA6D))
#define DMA_UR4R_RXAL (*((volatile __xdata register_t *)0xFA6E))
#define DMA_LCM_CFG   (*((volatile __xdata register_t *)0xFA70))
#define DMA_LCM_CR    (*((volatile __xdata register_t *)0xFA71))
#define DMA_LCM_STA   (*((volatile __xdata register_t *)0xFA72))
#define DMA_LCM_AMT   (*((volatile __xdata register_t *)0xFA73))
#define DMA_LCM_DONE  (*((volatile __xdata register_t *)0xFA74))
#define DMA_LCM_TXAH  (*((volatile __xdata register_t *)0xFA75))
#define DMA_LCM_TXAL  (*((volatile __xdata register_t *)0xFA76))
#define DMA_LCM_RXAH  (*((volatile __xdata register_t *)0xFA77))
#define DMA_LCM_RXAL  (*((volatile __xdata register_t *)0xFA78))

// Generate bit mask.
#define MASK(type, value) (~((type)(value)))
