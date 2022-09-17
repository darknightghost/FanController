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

/**
 * @brief       Power ctrl option.
 */
typedef enum _power_ctrl_option {
    PWR_CTRL_MCU      = 0x01, ///< Controller MCU.
    PWR_CTRL_SCREEN   = 0x02, ///< Screen.
    PWR_CTRL_UART     = 0x04, ///< UART.
    PWR_CTRL_ETHERNET = 0x08, ///< Ethernet.
    PWR_CTRL_FAN      = 0x10, ///< Fan.
    PWR_CTRL_READY    = PWR_CTRL_MCU | PWR_CTRL_SCREEN | PWR_CTRL_UART
                     | PWR_CTRL_ETHERNET, ///< Without fan.
    PWR_CTRL_ALL = PWR_CTRL_MCU | PWR_CTRL_SCREEN | PWR_CTRL_UART
                   | PWR_CTRL_ETHERNET | PWR_CTRL_FAN ///< All.
} power_ctrl_option_t;

/**
 * @brief       Initialize power control.
 */
void power_init();

/**
 * @brief       Set power on.
 *
 * @param[in]   ctrl        Control options.
 */
void power_on(power_ctrl_option_t ctrl);

/**
 * @brief       Set power off.
 *
 * @param[in]   ctrl        Control options.
 */
void power_off(power_ctrl_option_t ctrl);
