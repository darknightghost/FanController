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

#include <controller/clock.h>
#include <controller/power.h>
#include <controller/pwm.h>
#include <controller/serial.h>
#include <controller/status_led.h>

/**
 * @brief       Initialize MCU.
 */
inline void mcu_init()
{
    status_led_init();
    clock_init();
    pwm_init();
    power_init();
    serial_init();
}

/**
 * @brief       Initialize peripherals.
 */
inline void peripherals_init() {}

/**
 * @brief       Main loop.
 */
inline void main_loop()
{
    uint8_t       count = 0;
    volatile bool finished;
    while (1) {
        for (uint8_t i = 0; i < 100; ++i) {
            pwm_set(PWM_TARGET_SCREEN_BTN_LED, i);
            clock_wait(10000);
        }
        serial_dma_write(&count, 1, &finished);
        while (! finished)
            ;

        ++count;
    }
}

int main()
{
    // Initialize mcu.
    mcu_init();

    // Send ready signal.
    power_send_ready();
    clock_wait(100000);

    // Initialize peripherals.
    peripherals_init();
    status_led_set_ready();

    // Main loop.
    main_loop();
}
