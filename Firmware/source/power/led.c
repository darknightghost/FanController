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

#define PORT_RED   P1_7
#define PORT_GREEN P5_4

/// LED color.
static __data status_led_color_t l_color;
static __data uint8_t            l_green_count;

/**
 * @brief       Initialize led.
 */
void led_init()
{
    // Default red.
    l_color       = STATUS_LED_RED;
    l_green_count = 0;

    set_bit(P_SW2, 7);

    // Port.
    clear_bit(P1M0, 7);
    clear_bit(P1M1, 7);
    clear_bit(P1PU.value, 7);
    PORT_RED = 0;

    clear_bit(P5M0, 4);
    clear_bit(P5M1, 4);
    set_bit(P5PU.value, 4);
    PORT_GREEN = 1;

    clear_bit(P_SW2, 7);

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
        case STATUS_LED_RED: {
            PORT_RED   = 0;
            PORT_GREEN = 1;
        } break;

        case STATUS_LED_GREEN: {
            PORT_RED   = 1;
            PORT_GREEN = 0;
        } break;

        case STATUS_LED_YELLOW: {
            if (! PORT_RED) {
                PORT_RED      = 1;
                PORT_GREEN    = 0;
                l_green_count = 0;
            } else {
                ++l_green_count;
                if (l_green_count >= 4) {
                    PORT_RED   = 0;
                    PORT_GREEN = 1;
                }
            }
        } break;
    }

    TF1 = 0;
    EA  = 1;
}
