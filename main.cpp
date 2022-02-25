#include <iostream>
#include "pico/stdlib.h"

int main()
{
    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true)
    {
        // Blink LED
        std::cout << "Blinking!\n";
        sleep_ms(1000);
    }
    return 0;
}
