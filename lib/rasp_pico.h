#ifndef _RASP_PICO_H_
#define _RASP_PICO_H_

#include <cstdint>
#include <functional>
#include <memory>

#ifdef BUILD_PICO
#include "hardware/gpio.h"
#include "pico.h"
#include "pico/bootrom.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#else
#include "../raspPico/fake.h"
#endif

#define pin_led_pico 25
#define timer_interrupt 500

namespace rasp_pico
{
namespace GPIO
{
enum class Mode : uint8_t
{
    input = 0,
    output = 1
};

enum class Pulls
{
    none,
    up,
    down
};
}  // namespace GPIO

class Digital final
{
  public:
    Digital(uint8_t pin, GPIO::Mode mode, GPIO::Pulls pulls = GPIO::Pulls::none);
    Digital(Digital const&) = delete;
    Digital(Digital const&&) = delete;
    Digital& operator=(Digital const&) = delete;
    ~Digital() = default;

    bool Read();
    void Write(bool state);
    void Toogle();

  private:
    const uint8_t pin_;
};

class micro final
{
  public:
    micro();
    micro(micro const&) = delete;
    micro(micro const&&) = delete;
    micro& operator=(micro const&) = delete;
    ~micro();

    std::shared_ptr<Digital> LedPico{std::make_shared<Digital>(pin_led_pico, GPIO::Mode::output)};

    void Set_Timer_Interrupt(int64_t time_us, std::function<void()> func);

  private:
    inline static std::function<void()> func_;
    static bool timer_IRQ(struct repeating_timer* t)
    {
        func_();
        return true;
    }
};

};  // namespace rasp_pico
#endif
