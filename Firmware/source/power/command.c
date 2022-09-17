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

/**
 * @brief       Initialize command.
 */
void command_init() {}

/**
 * @brief       Run main loop.
 */
void command_main_loop()
{
    while (true)
        ;
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
