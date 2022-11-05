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

#include <stdlib.h>

#include <controller/serial.h>

static finish_flag_t *volatile __data l_writing_finished = NULL;
static finish_flag_t *volatile __data l_reading_finished = NULL;

/**
 * @brief       Initialize serial.
 */
void serial_init()
{
    // Baudrate 9600.
    SCON = 0x50;
    AUXR |= 0x01;
    AUXR |= 0x04;
    T2L = 0x6C;
    T2H = 0xFB;
    AUXR |= 0x10;

    // Interrupt.
    ES = 0;

    // DMA.
    l_writing_finished = NULL;
    DMA_UR1T_CFG.value = 0x84;
    DMA_UR1T_CR.value  = 0x80;
    DMA_UR1T_STA.value = 0;

    l_reading_finished = NULL;
    DMA_UR1R_CFG.value = 0x85;
    DMA_UR1R_CR.value  = 0x81;
    DMA_UR1R_STA.value = 0;
}

/**
 * @brief       Read UART1 via DMA.
 */
bool serial_dma_read(uint8_t *      buffer,
                     uint8_t        size_read,
                     finish_flag_t *finished)
{
    if (l_reading_finished != NULL) {
        return false;
    }
    l_reading_finished = finished;

    // Address.
    DMA_UR1R_RXAL.value = (uint8_t)((uint16_t)(buffer)&0xFF);
    DMA_UR1R_RXAH.value = (uint8_t)(((uint16_t)(buffer)&0xFF00) >> 8);

    // Size.
    DMA_UR1R_AMT.value = size_read;

    // Start.
    DMA_UR1R_CR.value = 0xC0;

    return true;
}

/**
 * @brief       Write UART1 via DMA.
 */
bool serial_dma_write(uint8_t *data, uint8_t size, finish_flag_t *finished)
{
    if (l_writing_finished != NULL) {
        return false;
    }

    // Write.
    l_writing_finished = finished;

    // Address.
    DMA_UR1T_TXAL.value = (uint8_t)((uint16_t)(data)&0xFF);
    DMA_UR1T_TXAH.value = (uint8_t)(((uint16_t)(data)&0xFF00) >> 8);

    // Size.
    DMA_UR1T_AMT.value = size;

    // Start.
    DMA_UR1T_CR.value = 0xA1;

    return true;
}

/**
 * @brief       UART 1 DMA send interrupt handler.
 */
void __on_uart_1_dma_send(void) __interrupt INT_DMA_UR1T
{
    EA = 0;
    if (l_writing_finished != NULL) {
        *l_writing_finished = true;
        l_writing_finished  = NULL;
        DMA_UR1T_STA.value  = 0;
    }
    EA = 1;
}

/**
 * @brief       UART 1 DMA receive interrupt handler.
 */
void __on_uart_1_dma_recv(void) __interrupt INT_DMA_UR1R
{
    EA = 0;
    if (l_reading_finished != NULL) {
        *l_reading_finished = true;
        l_reading_finished  = NULL;
        DMA_UR1R_STA.value  = 0;
    }
    EA = 1;
}
