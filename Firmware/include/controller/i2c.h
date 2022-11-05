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
 * @brief       Initialize i2c.
 */
void i2c_init();

/**
 * @brief       Read i2c asynchronously.
 *
 * @param[out]  buffer      Buffer.
 * @param[in]   size_read   Size to read.
 * @param[out]  finished    Finished flag.
 *
 * @return      \c true if reading started, \c false if busy.
 */
bool i2c_read_async(uint8_t *      buffer,
                    uint8_t        size_read,
                    finish_flag_t *finished);

/**
 * @brief       Write i2c asynchronously.
 *
 * @param[in]   data        Data to write.
 * @param[in]   size        Data size.
 * @param[out]  finished    Finished flag.
 *
 * @return      \c true if writing started, \c false if busy.
 */
bool i2c_write_async(uint8_t *data, uint8_t size, finish_flag_t *finished);

/**
 * @brief       I2C interrupt handler.
 */
extern void __on_i2c_int(void) __interrupt INT_I2C;
