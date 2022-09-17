/**
    Copyright 2022, 王思远 <darknightghost.cn@gmail.com>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <common/stc8g.h>
#include <power/command.h>

#define PORT_READY         P3_2
#define PORT_FAN_POWER     P3_3
#define PORT_REBOOT_SIGNAL P3_6

/**
 * @brief       Initialize command.
 */
void command_init()
{
    // PORT_READY
    clear_bit(P3M0, 2);
    clear_bit(P3M1, 2);
    set_bit(P3PU.value, 2);
    PORT_READY = 1;

    // PORT_FAN_POWER
    clear_bit(P3M0, 3);
    clear_bit(P3M1, 3);
    set_bit(P3PU.value, 3);
    PORT_FAN_POWER = 1;

    // PORT_REBOOT_SIGNAL
    clear_bit(P3M0, 6);
    clear_bit(P3M1, 6);
    set_bit(P3PU.value, 6);
    PORT_REBOOT_SIGNAL = 1;
}

/**
 * @brief       Run main loop.
 */
void command_main_loop()
{
    while (true) {
    }
}

/**
 * @brief       INT0 interrupt handler.
 */
void __on_ready_signal(void) __interrupt INT_INT0 {}

/**
 * @brief       INT1 interrupt handler.
 */
void __on_fan_power_signal(void) __interrupt INT_INT1 {}

/**
 * @brief       INT2 interrupt handler.
 */
void __on_reboot_signal(void) __interrupt INT_INT2 {}
