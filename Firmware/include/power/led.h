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
#include <common/stc8g.h>

/**
 * @brief       Color of status led.
 */
typedef enum _status_led_color {
    STATUS_LED_RED    = 0, ///< Red.
    STATUS_LED_GREEN  = 1, ///< Green.
    STATUS_LED_YELLOW = 2, ///< Yellow.
} status_led_color_t;

/**
 * @brief       Initialize led.
 */
void led_init();

/**
 * @brief       Set the color of status led.
 *
 * @param[in]   color       Color of the status led.
 */
void led_set_status_led_color(status_led_color_t color);

/**
 * @brief       Timer 1 interrupt handler.
 */
extern void __on_led_timer(void) __interrupt INT_TIMER1;
