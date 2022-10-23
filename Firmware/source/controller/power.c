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

#include <controller/clock.h>

#define PORT_READY         P0_6
#define PORT_FAN_POWER     P0_5
#define PORT_REBOOT_SIGNAL P5_3

/**
 * @brief       Initialize power control.
 */
void power_init()
{
    // PORT_READY
    PORT_READY = 1;
    set_bit(P0M0, 6);
    clear_bit(P0M1, 6);
    clear_bit(P0PU.value, 6);

    // PORT_FAN_POWER
    PORT_FAN_POWER = 1;
    set_bit(P0M0, 5);
    clear_bit(P0M1, 5);
    clear_bit(P0PU.value, 5);

    // PORT_REBOOT_SIGNAL
    PORT_REBOOT_SIGNAL = 1;
    set_bit(P5M0, 3);
    clear_bit(P5M1, 3);
    clear_bit(P5PU.value, 3);
}

/**
 * @brief       Send ready signal.
 */
void power_send_ready()
{
    PORT_READY = 0;
    clock_wait(1000000);
    PORT_READY = 1;
}

/**
 * @brief       Send reboot signal.
 */
void power_send_reboot()
{
    PORT_REBOOT_SIGNAL = 0;
    clock_wait(10000);
    PORT_REBOOT_SIGNAL = 1;
}

/**
 * @brief       Send reboot to factory mode signal.
 */
void power_send_reboot_factory()
{
    PORT_REBOOT_SIGNAL = 0;
    clock_wait(100000);
    PORT_REBOOT_SIGNAL = 1;
}

/**
 * @brief       Set fan power status.
 */
void power_set_fan_power(bool on)
{
    if (on) {
        PORT_FAN_POWER = 0;
    } else {
        PORT_FAN_POWER = 1;
    }
}
