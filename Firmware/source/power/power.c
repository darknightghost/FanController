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

#include <common/stc8g.h>
#include <power/power.h>

#define PWR_PORT_MCU      P1_0
#define PWR_PORT_SCREEN   P3_7
#define PWR_PORT_UART     P1_1
#define PWR_PORT_ETHERNET P1_6
#define PWR_PORT_FAN      P5_5

/**
 * @brief       Initialize power control.
 */
void power_init()
{
    // MCU
    set_bit(P1M0, 0);
    clear_bit(P1M1, 0);
    clear_bit(P1PU.value, 0);
    PWR_PORT_MCU = 1;

    // Screen
    set_bit(P3M0, 7);
    clear_bit(P3M1, 7);
    clear_bit(P3PU.value, 7);
    PWR_PORT_SCREEN = 1;

    // UART
    set_bit(P1M0, 1);
    clear_bit(P1M1, 1);
    clear_bit(P1PU.value, 1);
    PWR_PORT_UART = 1;

    // Ethernet
    set_bit(P1M0, 6);
    clear_bit(P1M1, 6);
    clear_bit(P1PU.value, 6);
    PWR_PORT_ETHERNET = 1;

    // Fan
    clear_bit(P5M0, 5);
    clear_bit(P5M1, 5);
    clear_bit(P5PU.value, 5);
    PWR_PORT_FAN = 1;
}

/**
 * @brief       Set power on.
 */
void power_on(power_ctrl_option_t ctrl)
{
    if (ctrl & PWR_CTRL_MCU) {
        PWR_PORT_MCU = 0;
    }

    if (ctrl & PWR_CTRL_SCREEN) {
        PWR_PORT_SCREEN = 0;
    }

    if (ctrl & PWR_CTRL_UART) {
        PWR_PORT_UART = 0;
    }

    if (ctrl & PWR_CTRL_ETHERNET) {
        PWR_PORT_ETHERNET = 0;
    }

    if (ctrl & PWR_CTRL_FAN) {
        PWR_PORT_FAN = 0;
    }
}

/**
 * @brief       Set power off.
 */
void power_off(power_ctrl_option_t ctrl)
{
    if (ctrl & PWR_CTRL_MCU) {
        PWR_PORT_MCU = 1;
    }

    if (ctrl & PWR_CTRL_SCREEN) {
        PWR_PORT_SCREEN = 1;
    }

    if (ctrl & PWR_CTRL_UART) {
        PWR_PORT_UART = 1;
    }

    if (ctrl & PWR_CTRL_ETHERNET) {
        PWR_PORT_ETHERNET = 1;
    }

    if (ctrl & PWR_CTRL_FAN) {
        PWR_PORT_FAN = 1;
    }
}
