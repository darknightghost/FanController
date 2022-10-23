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
 * @brief       Initialize power control.
 */
void power_init();

/**
 * @brief       Send ready signal.
 */
void power_send_ready();

/**
 * @brief       Send reboot signal.
 */
void power_send_reboot();

/**
 * @brief       Send reboot to factory mode signal.
 */
void power_send_reboot_factory();

/**
 * @brief       Set fan power status.
 *
 * @param[in]   on  Status.
 */
void power_set_fan_power(bool on);
