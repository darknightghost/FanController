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

#include <controller/i2c.h>

/**
 * @brief       Operation.
 */
typedef enum _i2c_operation {
    I2C_OP_NONE  = 0,
    I2C_OP_TEST  = 1,
    I2C_OP_WRITE = 2,
    I2C_OP_READ  = 3,
} i2c_operation_t;

/**
 * @brief       Test stage.
 */
typedef enum _i2c_test_stage {
    I2C_TEST_STAGE_SEND_ADDR = 0,
    I2C_TEST_STAGE_SEND_STOP = 1,
} i2c_test_stage_t;

/**
 * @brief       Write stage.
 */
typedef enum _i2c_write_stage {
    I2C_WRITE_STAGE_SEND_ADDR = 0,
    I2C_WRITE_STAGE_SEND_DATA = 1,
    I2C_WRITE_STAGE_SEND_STOP = 2,
} i2c_write_stage_t;

/**
 * @brief       Read stage.
 */
typedef enum _i2c_read_stage {
    I2C_READ_STAGE_SEND_ADDR = 0,
    I2C_READ_STAGE_SEND_DATA = 1,
    I2C_READ_STAGE_SEND_STOP = 2,
} i2c_read_stage_t;

/**
 * @brief       Stage.
 */
typedef union _i2c_operation_stage {
    i2c_test_stage_t  test_stage;
    i2c_write_stage_t write_stage;
    i2c_read_stage_t  read_stage;
} i2c_operation_stage_t;

static __idata volatile i2c_operation_t       l_operation;
static __idata volatile i2c_operation_stage_t l_stage;
static uint8_t *                              __idata volatile l_data_ptrs;
static __idata volatile uint8_t               l_remain_bytes;
static __idata volatile uint8_t               l_real_bytes;
static __idata volatile pfinish_flag_t        l_finished;
static __idata volatile pfinish_flag_t        l_test_result;

/**
 * @brief       Initialize i2c.
 */
void i2c_init()
{
    set_bit(P_SW2, 7);

    // Select I2C port.
    // P2.4, P2.5
    set_bit(P_SW2, 4);
    clear_bit(P_SW2, 5);

    // Configure I2C port.
    clear_bit(P2M0, 4);
    clear_bit(P2M1, 4);
    set_bit(P2PU.value, 4);

    clear_bit(P2M0, 5);
    clear_bit(P2M1, 5);
    set_bit(P2PU.value, 5);

    // Configure I2C.
    // 401.7857142857143 KHz, FOSC = 45MHz
    I2CCFG.value   = (0xC0 | 26);
    I2CMSCR.value  = 0x80;
    I2CMSAUX.value = 0x00;
    I2CMSST.value  = 0;

    clear_bit(P_SW2, 7);

    // Status.
    l_operation = I2C_OP_NONE;
}

/**
 * @brief       Test if the i2c slave device exists asynchronously.
 */
bool i2c_test_device_async(uint8_t        address,
                           finish_flag_t *exists,
                           finish_flag_t *finished)
{
    if (l_operation != I2C_OP_NONE) {
        return false;
    }

    __sbit old_ea = EA;
    EA            = 0;

    // Set status and step.
    l_operation                 = I2C_OP_TEST;
    l_stage.test_stage          = I2C_TEST_STAGE_SEND_ADDR;
    l_finished                  = finished;
    l_test_result               = exists;
    __idata uint8_t address_reg = address << 1;

    set_bit(P_SW2, 7);

    // Clear flags.
    I2CMSST.value = 0;

    // Set slave address and write command.
    I2CTXD.value = address_reg;

    // Set command.
    I2CMSCR.value = 0x80 | 0x09;

    clear_bit(P_SW2, 7);
    EA = old_ea;

    return true;
}

/**
 * @brief   On I2C_TEST_STAGE_SEND_ADDR finished.
 */
static inline void on_i2c_test_stage_send_addr_finished()
{
    set_bit(P_SW2, 7);

    // Get result.
    if (I2CMSST.value & 0x02) {
        clear_bit(P_SW2, 7);
        *l_test_result = true;
        set_bit(P_SW2, 7);
    } else {
        clear_bit(P_SW2, 7);
        *l_test_result = false;
        set_bit(P_SW2, 7);
    }

    // Send stop.
    I2CMSCR.value = 0x80 | 0x06;

    clear_bit(P_SW2, 7);
}

/**
 * @brief   On I2C_TEST_STAGE_SEND_STOP finished.
 */
static inline void on_i2c_test_stage_send_stop_finished()
{
    l_operation = I2C_OP_NONE;
    *l_finished = true;
}

/**
 * @brief       Read i2c asynchronously.
 */
bool i2c_read_async(uint8_t        address,
                    uint8_t *      buffer,
                    uint8_t        buffer_size,
                    uint8_t *      data_size,
                    pfinish_flag_t finished)
{}

/**
 * @brief       Write i2c asynchronously.
 */
bool i2c_write_async(uint8_t        address,
                     uint8_t *      data,
                     uint8_t        size,
                     pfinish_flag_t finished)
{}

/**
 * @brief       I2C interrupt handler.
 */
void __on_i2c_int(void) __interrupt INT_I2C
{
    EA = 0;

    switch (l_operation) {
        case I2C_OP_NONE: {
            break;
        }
        case I2C_OP_TEST: {
            switch (l_stage.test_stage) {
                case I2C_TEST_STAGE_SEND_ADDR: {
                    break;
                }

                case I2C_TEST_STAGE_SEND_STOP: {
                    break;
                }
            }
            break;
        }
        case I2C_OP_WRITE: {
            switch (l_stage.write_stage) {
                case I2C_WRITE_STAGE_SEND_ADDR: {
                    break;
                }
                case I2C_WRITE_STAGE_SEND_DATA: {
                    break;
                }
                case I2C_WRITE_STAGE_SEND_STOP: {
                    break;
                }
            }
            break;
        }
        case I2C_OP_READ: {
            switch (l_stage.read_stage) {
                case I2C_READ_STAGE_SEND_ADDR: {
                    break;
                }
                case I2C_READ_STAGE_SEND_DATA: {
                    break;
                }
                case I2C_READ_STAGE_SEND_STOP: {
                    break;
                }
            }
            break;
        }
    }

    clear_bit(I2CMSST.value, 6);
    EA = 1;
}
