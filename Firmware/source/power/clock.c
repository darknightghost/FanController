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

#include <power/clock.h>

/// Boot time.
static __data uint32_t l_milliseconds = 0;

/**
 * @brief       Initialize clock.
 */
void clock_init()
{
    l_milliseconds = 0;

    AUXR |= 0x80;
    TMOD &= 0xF0;

    // 1 ms.
    TL0 = 0xD0;
    TH0 = 0x8A;

    // Interrupt.
    TF0 = 0;
    ET0 = 1;
    EA  = 1;

    // Run.
    TR0 = 1;
}

/**
 * @brief       Get system boot time in milliseconds.
 */
uint32_t clock_get_milliseconds()
{
    EA           = 0;
    uint32_t ret = l_milliseconds;
    EA           = 1;
    return ret;
}

/**
 * @brief       Timer 0 interrupt handler.
 */
void __on_clock_timer(void) __interrupt INT_TIMER0
{
    EA = 0;
    ++l_milliseconds;
    TF0 = 0;
    EA  = 1;
}
