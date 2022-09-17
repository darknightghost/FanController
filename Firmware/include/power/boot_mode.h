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
 * @brief       Boot mode.
 */
typedef enum _boot_mode {
    BOOT_MODE_NORMAL  = 0, ///< Boot to normal mode.
    BOOT_MODE_FACTORY = 1, ///< Boot to factory mode.
} boot_mode_t;

/**
 * @brief       Initialize boot mode.
 */
void boot_mode_init();

/**
 * @brief       Set next boot mode to factory mode.
 */
void boot_mode_set_next_factory();

/**
 * @brief       Get next boot mode.
 *
 * @return      Boot mode.
 */
boot_mode_t boot_mode_get_next();
