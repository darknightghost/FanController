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

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

_Static_assert(sizeof(bool) <= 1, "Wrong boolean size.");

#if defined EDITOR_AUTO_COMPLETE
    // Auto-complete.
    #define __data
    #define __idata
    #define __xdata
    #define __at(addr)
    #define __sfr  volatile uint8_t
    #define __sbit volatile uint8_t
    #define __interrupt
#endif

/**
 * @brief       Register type.
 */
typedef union _register_t {
    struct {
        uint8_t bit0 : 1; ///< Bit 0.
        uint8_t bit1 : 1; ///< Bit 1.
        uint8_t bit2 : 1; ///< Bit 2.
        uint8_t bit3 : 1; ///< Bit 3.
        uint8_t bit4 : 1; ///< Bit 4.
        uint8_t bit5 : 1; ///< Bit 5.
        uint8_t bit6 : 1; ///< Bit 6.
        uint8_t bit7 : 1; ///< Bit 7.
    } bits;
    uint8_t value; ///< Value.
} register_t;

/**
 * @brief       Set bit.
 *
 * @param[out]  dest        Destination to set bit.
 * @param[in]   bit         Bit to set.
 */
#define set_bit(dest, bit) ((dest) |= (((uint8_t)1) << (bit)))

/**
 * @brief       Clear bit.
 *
 * @param[out]  dest        Destination to clear bit.
 * @param[in]   bit         Bit to clear.
 */
#define clear_bit(dest, bit) ((dest) &= (~(((uint8_t)1) << (bit))))

/// Finish flag.
typedef volatile bool finish_flag_t;
