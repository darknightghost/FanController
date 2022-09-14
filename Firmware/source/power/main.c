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

#include <power/boot_mode.h>
#include <power/clock.h>
#include <power/led.h>

int main()
{
    // Initialize.
    led_init();
    clock_init();
    boot_mode_init();

    // Main loop.
    while (true) {
    }

    // Reboot.
    IAP_CONTR = 0x60;
    return 0;
}
