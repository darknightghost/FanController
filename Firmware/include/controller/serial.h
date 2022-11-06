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

#include <common/common.h>
#include <common/stc8h.h>

/**
 * @brief       Initialize serial.
 */
void serial_init();

/**
 * @brief       Read UART1 via DMA.
 *
 * @param[out]  buffer      Buffer.
 * @param[in]   size_read   Size to read.
 * @param[out]  finished    Finished flag.
 *
 * @return      \c true if reading started, \c false if busy.
 */
bool serial_dma_read(uint8_t *__idata buffer,
                     __idata uint8_t  size_read,
                     pfinish_flag_t   finished);

/**
 * @brief       Write UART1 via DMA.
 *
 * @param[in]   data        Data to write.
 * @param[in]   size        Data size.
 * @param[out]  finished    Finished flag.
 *
 * @return      \c true if writing started, \c false if busy.
 */
bool serial_dma_write(uint8_t *__idata data,
                      __idata uint8_t  size,
                      pfinish_flag_t   finished);

/**
 * @brief       UART 1 DMA send interrupt handler.
 */
extern void __on_uart_1_dma_send(void) __interrupt INT_DMA_UR1T;

/**
 * @brief       UART 1 DMA receive interrupt handler.
 */
extern void __on_uart_1_dma_recv(void) __interrupt INT_DMA_UR1R;
