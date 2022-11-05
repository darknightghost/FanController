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

#include <common/common.h>
#include <common/stc8h.h>

#include <controller/status_led.h>

#define PORT_RED   P5_1
#define PORT_GREEN P3_5

/**
 * @brief       Initialize status led.
 */
void status_led_init()
{
    set_bit(P_SW2, 7);

    // PORT_RED
    clear_bit(P5M0, 1);
    clear_bit(P5M1, 1);
    clear_bit(P5PU.value, 1);

    // PORT_GREEN
    clear_bit(P3M0, 5);
    clear_bit(P3M1, 5);
    clear_bit(P3PU.value, 5);

    clear_bit(P_SW2, 7);

    PORT_RED = 0;
}

/**
 * @brief       Set ready.
 */
void status_led_set_ready()
{
    PORT_RED   = 1;
    PORT_GREEN = 0;
}
