/**
    Copyright 2022, 王思远 <darknightghost.cn@gmail.com>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <common/stc8g.h>
#include <power/boot_mode.h>
#include <power/clock.h>
#include <power/command.h>
#include <power/led.h>
#include <power/power.h>

#define POWER_MCU_MS    1000
#define POWER_UART_MS   1000
#define POWER_REBOOT_MS 100

#define REBOOT_FACTORY_MS 50

#define RESET_MS 5000

#define PORT_READY         P3_2
#define PORT_FAN_POWER     P3_3
#define PORT_REBOOT_SIGNAL P3_6
#define PORT_RESET         P3_4

typedef enum _run_status {
    RUN_STATUS_READY,             /// All units ready.
    RUN_STATUS_POWER_ON,          ///< System power on.
    RUN_STATUS_BOOTING,           ///< Normal mode booting.
    RUN_STATUS_BOOTING_FACTORY,   ///< Factory mode booting.
    RUN_STATUS_REBOOT_SIGNAL,     ///< Parse reboot signal.
    RUN_STATUS_REBOOTING,         ///< Rebooting to normal mode.
    RUN_STATUS_REBOOTING_FACTORY, ///< Rebooting to factory mode.
} run_status_t;

static __data volatile run_status_t l_run_status;

/**
 * @brief       Initialize command.
 */
void command_init()
{
    power_off(PWR_CTRL_ALL);

    // PORT_READY
    clear_bit(P3M0, 2);
    clear_bit(P3M1, 2);
    set_bit(P3PU.value, 2);
    PORT_READY = 1;

    // PORT_FAN_POWER
    clear_bit(P3M0, 3);
    clear_bit(P3M1, 3);
    set_bit(P3PU.value, 3);
    PORT_FAN_POWER = 1;

    // PORT_REBOOT_SIGNAL
    clear_bit(P3M0, 6);
    clear_bit(P3M1, 6);
    set_bit(P3PU.value, 6);
    PORT_REBOOT_SIGNAL = 1;

    // PORT_RESET
    clear_bit(P3M0, 4);
    clear_bit(P3M1, 4);
    set_bit(P3PU.value, 4);
    PORT_RESET = 1;

    l_run_status = RUN_STATUS_POWER_ON;

    EA = 1;
}

static inline bool check_reset(bool *pressed_cache, uint32_t *pressed_time)
{
    if (*pressed_cache) {
        if (PORT_RESET == 1) {
            // Released.
            *pressed_cache = false;
        } else {
            if (clock_get_milliseconds() - *pressed_time >= RESET_MS) {
                return true;
            }
        }

    } else {
        if (PORT_RESET == 0) {
            // Pressed.
            *pressed_time  = clock_get_milliseconds();
            *pressed_cache = true;
        }
    }

    return false;
}

static inline void on_status_ready()
{
    led_set_status_led_color(STATUS_LED_GREEN);
    power_on(PWR_CTRL_READY);

    bool     reset_pressed      = false;
    uint32_t reset_pressed_time = 0;

    while (l_run_status == RUN_STATUS_READY) {
        // Check fan status.
        if (PORT_FAN_POWER == 0) {
            power_on(PWR_CTRL_FAN);
        } else {
            power_off(PWR_CTRL_FAN);
        }

        // Check reset.
        if (check_reset(&reset_pressed, &reset_pressed_time)) {
            boot_mode_t boot_mode = boot_mode_get_next();
            if (boot_mode == BOOT_MODE_NORMAL) {
                l_run_status = RUN_STATUS_REBOOTING;

            } else {
                l_run_status = RUN_STATUS_REBOOTING_FACTORY;
            }
            continue;
        }

        // Check reboot signal.
        if (PORT_REBOOT_SIGNAL == 0) {
            l_run_status = RUN_STATUS_REBOOT_SIGNAL;
            continue;
        }
    }
}

static inline void on_status_power_on()
{
    led_set_status_led_color(STATUS_LED_RED);

    // Check boot mode.
    boot_mode_t boot_mode = boot_mode_get_next();
    if (boot_mode == BOOT_MODE_NORMAL) {
        l_run_status = RUN_STATUS_BOOTING;

    } else {
        l_run_status = RUN_STATUS_BOOTING_FACTORY;
    }
}

static inline void on_status_booting()
{
    led_set_status_led_color(STATUS_LED_YELLOW);

    // Power on MCU.
    power_on(PWR_CTRL_MCU);
    clock_wait(POWER_MCU_MS);

    // Wait for ready.
    bool     reset_pressed      = false;
    uint32_t reset_pressed_time = 0;

    while (PORT_READY != 0) {
        // Check reset.
        if (check_reset(&reset_pressed, &reset_pressed_time)) {
            boot_mode_t boot_mode = boot_mode_get_next();
            if (boot_mode == BOOT_MODE_NORMAL) {
                l_run_status = RUN_STATUS_REBOOTING;

            } else {
                l_run_status = RUN_STATUS_REBOOTING_FACTORY;
            }
            return;
        }
    };

    l_run_status = RUN_STATUS_READY;
}

static inline void on_status_booting_factory()
{
    led_set_status_led_color(STATUS_LED_YELLOW);

    // Power on UART.
    power_on(PWR_CTRL_UART);
    clock_wait(POWER_UART_MS);

    // Power on MCU.
    power_on(PWR_CTRL_MCU);
    clock_wait(POWER_MCU_MS);

    // Wait for ready.
    bool     reset_pressed      = false;
    uint32_t reset_pressed_time = 0;

    while (PORT_READY != 0) {
        // Check reset.
        if (check_reset(&reset_pressed, &reset_pressed_time)) {
            boot_mode_t boot_mode = boot_mode_get_next();
            if (boot_mode == BOOT_MODE_NORMAL) {
                l_run_status = RUN_STATUS_REBOOTING;

            } else {
                l_run_status = RUN_STATUS_REBOOTING_FACTORY;
            }
            return;
        }
    };

    l_run_status = RUN_STATUS_READY;
}

static inline void on_status_reboot_signal()
{
    // Get low-level duration.
    uint32_t begin_time = clock_get_milliseconds();
    while (PORT_REBOOT_SIGNAL == 0) {
    }

    uint32_t duration = clock_get_milliseconds() - begin_time;

    // Select reboot mode.
    if (duration >= REBOOT_FACTORY_MS) {
        l_run_status = RUN_STATUS_REBOOTING_FACTORY;
    } else {
        l_run_status = RUN_STATUS_REBOOTING;
    }
}

static inline void on_status_rebooting()
{
    // Power off.
    power_off(PWR_CTRL_ALL);
    led_set_status_led_color(STATUS_LED_RED);
    clock_wait(POWER_REBOOT_MS);
    l_run_status = RUN_STATUS_POWER_ON;
}

static inline void on_status_rebooting_factory()
{
    // Power off.
    power_off(PWR_CTRL_WITHOUT_UART);
    power_on(PWR_CTRL_UART);
    led_set_status_led_color(STATUS_LED_RED);
    clock_wait(POWER_REBOOT_MS);
    l_run_status = RUN_STATUS_POWER_ON;

    // Set next boot mode.
    boot_mode_set_next_factory();
}

/**
 * @brief       Run main loop.
 */
void command_main_loop()
{
    while (true) {
        // Dispatch.
        switch (l_run_status) {
            case RUN_STATUS_READY:
                on_status_ready();
                break;

            case RUN_STATUS_POWER_ON:
                on_status_power_on();
                break;

            case RUN_STATUS_BOOTING:
                on_status_booting();
                break;

            case RUN_STATUS_BOOTING_FACTORY:
                on_status_booting_factory();
                break;

            case RUN_STATUS_REBOOT_SIGNAL:
                on_status_reboot_signal();
                break;

            case RUN_STATUS_REBOOTING:
                on_status_rebooting();
                break;

            case RUN_STATUS_REBOOTING_FACTORY:
                on_status_rebooting_factory();
                break;
        }
    }
}
