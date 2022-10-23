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
 * @brief       Initialize clock.
 */
void clock_init();

/**
 * @brief       Get system boot time in microseconds.
 *
 * @return      Boot time.
 */
uint32_t clock_get_microseconds();

/**
 * @brief       Wait.
 *
 * @param[in]   milliseconds        Time to wait(microsseconds);
 */
void clock_wait(uint32_t microseconds);

/**
 * @brief       Timer 0 interrupt handler.
 */
extern void __on_clock_timer(void) __interrupt INT_TIMER0;
