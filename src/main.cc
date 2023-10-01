
#include "../lib/rasp_pico.h"
#include "../lib/some_lib.hpp"
#include <iostream>

int main()
{
    /* Initialize Pico */
    rasp_pico::micro pico;

    /* Blink LED for a while with SLEEP */
    int counter = 0;
    while (counter < 10)
    {
        // Toogle LED
        pico.LedPico->Toogle();
        // Increase the counter
        counter++;
        // Wait
        sleep_ms(500);
    }

    /* Blink LED for a while with TIMER_INTERRUPT
        - This approuch will never froze the CPU allow you to run other things */

    /* Set interrup timer */
    volatile bool flag_timer{false};
    pico.Set_Timer_Interrupt(500000, [&]() { flag_timer = true; });

    counter = 0;
    while (counter < 10)
    {
        if (flag_timer)
        {
            // Toogle LED
            pico.LedPico->Toogle();
            // Increase the counter
            counter++;
            // Reset flag
            flag_timer = false;
        }

        // Other Action to do ....
    }

    /* Dummy Code */
    // First create the object all full the arguments as it needs
    some_lib dummy_lib(1);

    // Use their methods as you need
    int value = dummy_lib.Get_value();

    std::cout << "Value in the object = " << value << std::endl;

    dummy_lib.Set_value(99);
    std::cout << "The new value in the object is = " << dummy_lib.Get_value() << std::endl;
    return 0;
}