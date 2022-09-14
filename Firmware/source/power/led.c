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

#include <power/led.h>

#define PIN_RED   P1_7
#define PIN_GREEN P5_4

/// LED color.
static __data status_led_color_t l_color;

/**
 * @brief       Initialize led.
 */
void led_init()
{
    // Default red.
    l_color = STATUS_LED_RED;

    // Enable timer, interval = 1ms.
    AUXR |= 0x40;
    TMOD &= 0x0F;
    TL1 = 0xD0;
    TH1 = 0x8A;
    TF1 = 0;
    ET1 = 1;
    EA  = 1;
    TR1 = 1;
}

/**
 * @brief       Set the color of status led.
 */
void led_set_status_led_color(status_led_color_t color)
{
    EA      = 0;
    l_color = color;
    EA      = 1;
}

/**
 * @brief       Timer 1 interrupt handler.
 */
void __on_led_timer(void) __interrupt INT_TIMER1
{
    EA = 0;
    switch (l_color) {
        case STATUS_LED_RED:
            PIN_RED   = 0;
            PIN_GREEN = 1;
            break;

        case STATUS_LED_GREEN:
            PIN_RED   = 1;
            PIN_GREEN = 0;
            break;

        case STATUS_LED_YELLOW:
            PIN_RED   = ! PIN_RED;
            PIN_GREEN = ! PIN_RED;
            break;
    }
    TF1 = 0;
    EA  = 1;
}
