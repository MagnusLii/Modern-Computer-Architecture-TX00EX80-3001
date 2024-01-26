#include <stdio.h>
#include "pico/stdlib.h"

__attribute__(( naked )) int difference(int a, int b)
{
    // the values passed to your program are in registers
    // R0 = a, R1 = b
    // write your code between push and pop instructions
    // make sure return value is in R0 after calculation
    asm volatile
    (
        "push {r4, r5, r6, r7} \n" // do not remove
        
        "sub r0, r0, r1 \n"
        "cmp r0, #0 \n"
        "blt neg \n"

        "neg: \n"
        "mvn r0, r0 \n"
        "add r0, r0, #1 \n"

        "pop {r4, r5, r6, r7} \n" // do not remove
        "bx lr \n" // do not remove
    );
}

void fail() {
    printf("Failed\n"); // set a break point here
    while(1) {
        tight_loop_contents();
    }
}

void ok() {
    printf("All ok\n"); // set a break point here
}


int main()
{
    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();


    if(difference(-9, 7) != 16) fail();
    if(difference(-19, -1) != 18) fail();
    if(difference(22, 5) != 17) fail();
    if(difference(8, 18) != 10) fail();
    if(difference(28, -14) != 42) fail();
    if(difference(0, 7) != 7) fail();
    if(difference(-1, 0) != 1) fail();

    ok();

    // Loop forever
    while (true) {
        // Blink LED
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }

    return 0;
}
