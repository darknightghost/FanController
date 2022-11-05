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
#include <common/stc8h.h>

#include <controller/pwm.h>

#define PORT_SCREEN_BTN_LED P2_2

/// Boot time.
static __data volatile uint8_t l_screen_btn_led_value   = 0;
static __data volatile uint8_t l_screen_btn_led_current = 0;

/**
 * @brief       Initialize pwm.
 */
void pwm_init()
{
    set_bit(P_SW2, 7);

    // Ports.
    set_bit(P2M0, 2);
    clear_bit(P2M1, 2);
    clear_bit(P2PU.value, 2);
    PORT_SCREEN_BTN_LED = 1;

    clear_bit(P_SW2, 7);

    // Timer1.
    AUXR |= 0x40;
    TMOD &= 0x0F;

    // 1us
    TL1 = 0xD3;
    TH1 = 0xFF;

    // Interrupt.
    TF1 = 0;
    ET1 = 1;
    EA  = 1;

    // Run.
    TR1 = 1;
}

/**
 * @brief       Set value.
 */
void pwm_set(uint8_t target, uint8_t value)
{
    if (target & PWM_TARGET_SCREEN_BTN_LED) {
        l_screen_btn_led_value = value;
    }
}

/**
 * @brief       Timer 1 interrupt handler.
 */
void __on_pwm_timer(void) __interrupt INT_TIMER1
{
    EA = 0;

    // Screen button led.
    ++l_screen_btn_led_current;
    if (l_screen_btn_led_current > 100) {
        l_screen_btn_led_current = 0;
    }
    PORT_SCREEN_BTN_LED
        = l_screen_btn_led_current < l_screen_btn_led_value ? 0 : 1;

    TF1 = 0;
    EA  = 1;
}
