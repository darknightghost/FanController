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
#include <common/stc8g.h>

#include <power/boot_mode.h>

#define BOOT_MODE_PORT P3_5

static __idata boot_mode_t l_next_boot_mode;

/**
 * @brief       Initialize boot mode.
 */
void boot_mode_init()
{
    l_next_boot_mode = BOOT_MODE_NORMAL;

    set_bit(P_SW2, 7);

    clear_bit(P3M0, 5);
    clear_bit(P3M1, 5);
    set_bit(P3PU.value, 5);

    clear_bit(P_SW2, 7);

    BOOT_MODE_PORT = 1;
}

/**
 * @brief       Set next boot mode to factory mode.
 */
void boot_mode_set_next_factory()
{
    l_next_boot_mode = BOOT_MODE_FACTORY;
}

/**
 * @brief       Get next boot mode.
 */
boot_mode_t boot_mode_get_next()
{
    if (l_next_boot_mode == BOOT_MODE_FACTORY) {
        l_next_boot_mode = BOOT_MODE_NORMAL;
        return BOOT_MODE_FACTORY;
    } else {
        if (BOOT_MODE_PORT == 0) {
            return BOOT_MODE_FACTORY;
        } else {
            return BOOT_MODE_NORMAL;
        }
    }
}
