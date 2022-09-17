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
#include <power/command.h>
#include <power/led.h>

#define PORT_READY         P3_2
#define PORT_FAN_POWER     P3_3
#define PORT_REBOOT_SIGNAL P3_6

typedef enum _run_status {
    RUN_STATUS_READY,
    RUN_STATUS_POWER_ON,
    RUN_STATUS_BOOTING,
    RUN_STATUS_BOOTING_FACTORY,
    RUN_STATUS_REBOOT_SIGNAL,
    RUN_STATUS_REBOOTING,
    RUN_STATUS_REBOOTING_FACTORY,
} run_status_t;

static __data volatile run_status_t l_run_status;

/**
 * @brief       Initialize command.
 */
void command_init()
{
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

    l_run_status = RUN_STATUS_POWER_ON;

    EA = 1;
}

static inline void enable_reboot_int()
{
    set_bit(INTCLKO, 4);
}

static inline void disable_reboot_int()
{
    clear_bit(INTCLKO, 4);
}

static inline void enable_fan_power_int()
{
    EX1 = 1;
}

static inline void disable_fan_power_int()
{
    EX1 = 0;
}

static inline void enable_ready_int()
{
    EX0 = 1;
}

static inline void disable_ready_int()
{
    EX0 = 0;
}

static inline void on_status_ready()
{
    EA = 0;
    led_set_status_led_color(STATUS_LED_GREEN);
    disable_ready_int();
    enable_reboot_int();
    enable_fan_power_int();
    EA = 1;
    while (l_run_status == RUN_STATUS_READY) {
        // Sleep.
        set_bit(PCON, 1);
    }
}

static inline void on_status_power_on() {}

static inline void on_status_booting() {}

static inline void on_status_booting_factory() {}

static inline void on_status_reboot_signal() {}

static inline void on_status_rebooting() {}

static inline void on_status_rebooting_factory() {}

/**
 * @brief       Run main loop.
 */
void command_main_loop()
{
    while (true) {
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

/**
 * @brief       INT0 interrupt handler.
 */
void __on_ready_signal(void) __interrupt INT_INT0 {}

/**
 * @brief       INT1 interrupt handler.
 */
void __on_fan_power_signal(void) __interrupt INT_INT1 {}

/**
 * @brief       INT2 interrupt handler.
 */
void __on_reboot_signal(void) __interrupt INT_INT2 {}
