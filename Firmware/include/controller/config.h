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
 * @brief   Config struct.
 */
typedef struct _config_t {
    uint32_t ip_addr; ///< IP address.
} config_t;

/**
 * @brief       Initialize config.
 */
void config_init();

/**
 * @brief       Get config.
 *
 * @return      Pointer to config.
 */
config_t *config_get();

/**
 * @brief       Save config.
 */
void config_save();
