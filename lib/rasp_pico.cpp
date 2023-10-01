#include "rasp_pico.h"

namespace rasp_pico
{
/* Digital */
Digital::Digital(uint8_t pin, GPIO::Mode mode, GPIO::Pulls pulls) : pin_{pin}
{
    gpio_init(pin);
    gpio_set_dir(pin, (uint8_t)mode);
    if (mode == GPIO::Mode::input && pulls != GPIO::Pulls::none)
        gpio_set_pulls(pin, pulls == GPIO::Pulls::up, pulls == GPIO::Pulls::down);
}

bool Digital::Read()
{
    return gpio_get(pin_);
}

void Digital::Write(bool state)
{
    gpio_put(pin_, state);
}

void Digital::Toogle()
{
    Write(!Read());
}

/* micro */
micro::micro()
{
    /* Initialise I/O */
    stdio_init_all();
}

micro::~micro()
{
    // This will change for devop mode when the program finish
    reset_usb_boot(0, 0);
}

void micro::Set_Timer_Interrupt(int64_t time_us, std::function<void()> func)
{
    func_ = func;
    static struct repeating_timer timerClock;
    add_repeating_timer_us((time_us), timer_IRQ, NULL, &timerClock);
}

}  // namespace rasp_pico
