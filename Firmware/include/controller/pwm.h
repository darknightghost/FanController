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

typedef enum _pwm_target_t {
    PWM_TARGET_SCREEN_BTN_LED = 0x01 ///< LED brightness of screen button.
} pwm_target_t;

/**
 * @brief       Initialize pwm.
 */
void pwm_init();

/**
 * @brief       Set value.
 *
 * @param[in]   target      Target to conrol.
 * @param[in]   value       Value[0, 100].
 */
void pwm_set(uint8_t target, uint8_t value);

/**
 * @brief       Timer 1 interrupt handler.
 */
extern void __on_pwm_timer(void) __interrupt INT_TIMER1;
