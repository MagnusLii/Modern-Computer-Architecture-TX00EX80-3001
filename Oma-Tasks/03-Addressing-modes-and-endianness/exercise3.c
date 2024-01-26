#include <stdio.h>
#include "pico/stdlib.h"

__attribute__(( naked )) void asm_test(int *a, int *b, int *c, int *d)
{
  // write your code between push and pop instructions
  asm volatile
  (
	"push {r4, r5, r6, r7} \n" // do not remove

	"ldr r7, [r0] \n" // example assembly code - replace with your own code
	"add r4, r7, r2 \n" // example assembly code replace with your own code
	// add more code here

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

    int m0;
    int m1;
    int m2;
    int m3;

    m0 = 1; m1 = 2; m2 = 3; m3 = 4;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 43) fail();

    m0 = 8; m1 = 5; m2 = 6; m3 = 21;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 1524) fail();

    m0 = 3; m1 = 4; m2 = 5; m3 = 1;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 328) fail();

    m0 = 3; m1 = 5; m2 = 7; m3 = 8;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 931) fail();

    m0 = 33; m1 = 22; m2 = 11; m3 = 0;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 250239) fail();

    m0 = 42; m1 = 55; m2 = 12; m3 = 1;
    asm_test(&m0, &m1, &m2, &m3);
    if(m0 != 9280754) fail();

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
	
