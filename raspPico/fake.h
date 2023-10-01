#ifndef _FAKE_H_
#define _FAKE_H_

/*
    Fake of Pico Libs
*/
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <sstream>
#include <thread>

typedef unsigned int uint;

#define GPIO_IN 0
#define GPIO_OUT 1

#define GPIO_FUNC_UART 2
#define GPIO_FUNC_I2C 3
#define GPIO_FUNC_PWM 4

#define PWM_CHAN_B 0
#define i2c0 0

/* FAKE */
namespace FAKE
{
static uint8_t pinsState[29] = {0};
static uint8_t pinsConfig[29] = {0};
}  // namespace FAKE

/* GPIO */
inline void gpio_init(uint gpio) {}
inline void gpio_set_pulls(uint gpio, bool up, bool down) {}
inline void gpio_set_function(uint gpio, uint fn) {}
inline void gpio_put(uint gpio, bool value)
{
    FAKE::pinsState[gpio] = value;
}
inline void gpio_set_dir(uint gpio, bool mode)
{
    FAKE::pinsConfig[gpio] = mode;
}
inline void gpio_pull_up(uint gpio) {}
inline bool gpio_get(uint gpio)
{
    return FAKE::pinsState[gpio];
}

typedef void (*gpio_irq_callback_t)(uint gpio, uint32_t events);
inline void gpio_set_irq_enabled_with_callback(uint gpio, uint32_t events, bool enabled, gpio_irq_callback_t callback)
{
}

/* PWM */
inline uint pwm_gpio_to_slice_num(uint gpio)
{
    return 0;
}
inline void pwm_set_wrap(uint slice_num, uint16_t wrap) {}
inline void pwm_set_clkdiv(uint slice_num, float divider) {}
inline uint pwm_gpio_to_channel(uint gpio)
{
    return 0;
}
inline void pwm_set_chan_level(uint slice_num, uint chan, uint16_t level) {}
inline void pwm_set_enabled(uint slice_num, bool enabled) {}

/* ADC */
inline void adc_init(void) {}
inline void adc_run(bool run) {}
inline void adc_set_clkdiv(float clkdiv) {}
inline void adc_set_round_robin(uint input_mask) {}
inline void adc_select_input(uint input) {}
inline void adc_gpio_init(uint gpio) {}
inline void adc_fifo_drain(void) {}
inline void adc_fifo_setup(bool en, bool dreq_en, uint16_t dreq_thresh, bool err_in_fifo, bool byte_shift) {}
inline uint8_t adc_fifo_get_level(void)
{
    return 0;
}
inline uint adc_get_selected_input(void)
{
    return 0;
}
inline uint16_t adc_read(void)
{
    return 0;
}
inline uint16_t adc_fifo_get(void)
{
    return 0;
}
inline bool adc_fifo_is_empty(void)
{
    return 0;
}

/* I2C */
typedef uint8_t i2c_inst_t;
inline uint i2c_init(i2c_inst_t* i2c, uint baudrate)
{
    return 0;
}
inline void i2c_reset(i2c_inst_t* i2c);
inline int i2c_read_blocking(i2c_inst_t* i2c, uint8_t addr, uint8_t* dst, size_t len, bool nostop)
{
    return 0;
}
inline int i2c_write_blocking(i2c_inst_t* i2c, uint8_t addr, const uint8_t* src, size_t len, bool nostop)
{
    return 0;
}
inline int i2c_write_timeout_us(i2c_inst_t* i2c,
                                uint8_t addr,
                                const uint8_t* src,
                                size_t len,
                                bool nostop,
                                uint timeout_us)
{
    return 0;
}
inline int i2c_read_timeout_us(i2c_inst_t* i2c, uint8_t addr, uint8_t* dst, size_t len, bool nostop, uint timeout_us)
{
    return 0;
}

/* TIME */
typedef struct
{
    int16_t year;  ///< 0..4095
    int8_t month;  ///< 1..12, 1 is January
    int8_t day;    ///< 1..28,29,30,31 depending on month
    int8_t dotw;   ///< 0..6, 0 is Sunday
    int8_t hour;   ///< 0..23
    int8_t min;    ///< 0..59
    int8_t sec;    ///< 0..59
} datetime_t;
typedef struct repeating_timer repeating_timer_t;
typedef bool (*repeating_timer_callback_t)(repeating_timer_t* rt);
struct repeating_timer
{
    int64_t delay_us;
    repeating_timer_callback_t callback;
    void* user_data;
};

/*To Fake Run*/
static std::unique_ptr<std::thread> th_fakeClockCounter;
inline void fakeClockCounter(int64_t delay_us, repeating_timer_callback_t callback, struct repeating_timer* t)
{
    while (1)
    {
        callback(t);
        usleep(delay_us);
    }
}

static inline bool add_repeating_timer_us(int64_t delay_us,
                                          repeating_timer_callback_t callback,
                                          void* user_data,
                                          repeating_timer_t* out)
{
    th_fakeClockCounter = std::unique_ptr<std::thread>(new std::thread(fakeClockCounter, delay_us, callback, out));
    return true;
}

/* Generic */
inline void sleep_ms(uint32_t ms)
{
    usleep(ms * 1000);
}
inline void sleep_us(uint32_t us)
{
    usleep(us);
}
inline void busy_wait_ms(uint32_t delay_ms)
{
    sleep_ms(delay_ms);
}
inline void busy_wait_us_32(uint32_t delay_us)
{
    sleep_us(delay_us);
}

/* UART */
using uart_inst_t = uint8_t;
using uart_parity_t = uint8_t;

#define UART_PARITY_NONE 0
#define UART_PARITY_EVEN 1
#define UART_PARITY_ODD 2
#define uart0 0
#define uart1 1

inline void uart_init(void) {}
inline void uart_init(uint8_t uart, uint32_t baudrate) {}
inline void uart_set_hw_flow(uint8_t uart, bool cts, bool rts) {}
inline void uart_set_format(uint8_t uart, uint data_bits, uint stop_bits, uart_parity_t parity) {}
inline void uart_set_fifo_enabled(uint8_t uart, bool enabled) {}
inline size_t uart_is_readable(uint8_t uart)
{
    return 0;
}
inline char uart_getc(uint8_t uart)
{
    return 0xff;
}
inline void uart_putc(uint8_t uart, char c) {}

/* PICO */
inline void stdio_init_all() {}
inline void rtc_init(void) {}
inline void reset_usb_boot(uint32_t usb_activity_gpio_pin_mask, uint32_t disable_interface_mask) {}
inline void multicore_launch_core1(void (*entry)(void)) {}
inline bool rtc_set_datetime(datetime_t* t)
{
    return true;
}
inline bool rtc_get_datetime(datetime_t* t)
{
    return true;
}
inline void adc_set_temp_sensor_enabled(bool enable) {}

#endif
