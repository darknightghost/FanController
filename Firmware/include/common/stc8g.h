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
    #define INT_TIMER0
    #define INT_INT1
    #define INT_TIMER1
    #define INT_UART1
    #define INT_INT2

#else
    #define INT_TIMER0 1
    #define INT_INT1   2
    #define INT_TIMER1 3
    #define INT_UART1  4
    #define INT_INT2   10

#endif

// System clock.
#define CKSEL    (*((volatile __xdata register_t *)0xFE00))
#define CLKDIV   (*((volatile __xdata register_t *)0xFE01))
#define HIRCCR   (*((volatile __xdata register_t *)0xFE02))
#define XOSCCR   (*((volatile __xdata register_t *)0xFE03))
#define IRC32KCR (*((volatile __xdata register_t *)0xFE04))
#define MCLKOCR  (*((volatile __xdata register_t *)0xFE05))

// I/O ports.
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

#define P3PU  (*((volatile __xdata register_t *)0xFE12))
#define P3NCS (*((volatile __xdata register_t *)0xFE1B))
#define P3SR  (*((volatile __xdata register_t *)0xFE23))
#define P3DR  (*((volatile __xdata register_t *)0xFE2B))
#define P3IE  (*((volatile __xdata register_t *)0xFE33))

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
__sfr __at(0x98) SCON;
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

// Generate bit mask.
#define MASK(type, value) (~((type)(value)))
