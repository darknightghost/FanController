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

#include <controller/i2c.h>

/**
 * @brief       Initialize i2c.
 */
void i2c_init()
{
    set_bit(P_SW2, 7);

    // Select I2C port.
    // P2.4, P2.5
    set_bit(P_SW2, 4);
    clear_bit(P_SW2, 5);

    // Configure I2C port.
    clear_bit(P2M0, 4);
    clear_bit(P2M1, 4);
    set_bit(P2PU.value, 4);

    clear_bit(P2M0, 5);
    clear_bit(P2M1, 5);
    set_bit(P2PU.value, 5);

    // Configure I2C.

    clear_bit(P_SW2, 7);
}

/**
 * @brief       Read i2c asynchronously.
 */
bool i2c_read_async(uint8_t *buffer, uint8_t size_read, finish_flag_t *finished)
{}

/**
 * @brief       Write i2c asynchronously.
 */
bool i2c_write_async(uint8_t *data, uint8_t size, finish_flag_t *finished) {}

/**
 * @brief       I2C interrupt handler.
 */
void __on_i2c_int(void) __interrupt INT_I2C {}
