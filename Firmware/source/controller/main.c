/**
    Copyright 2022, ηζθΏ <darknightghost.cn@gmail.com>
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
#include <controller/i2c.h>
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
    i2c_init();
}

/**
 * @brief       Initialize peripherals.
 */
inline void peripherals_init() {}

/**
 * @brief       Main loop.
 */
__xdata uint8_t data = 0;
inline void     main_loop()
{
    volatile bool read_finished  = false;
    volatile bool write_finished = false;
    serial_dma_read(&data, 1, &read_finished);
    data = 7;
    while (1) {
        for (uint8_t i = 0; i < 100; ++i) {
            pwm_set(PWM_TARGET_SCREEN_BTN_LED, i);
            clock_wait(10000);
        }
        serial_dma_write(&data, 1, &write_finished);
        while (! write_finished)
            ;
        if (read_finished) {
            serial_dma_read(&data, 1, &read_finished);
        }
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
