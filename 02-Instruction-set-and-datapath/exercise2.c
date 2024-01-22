#include <stdio.h>
#include "pico/stdlib.h"


// TODO: insert other definitions and declarations here
__attribute__(( naked )) int asm_test(int v0, int v1, int v2, int v3)
{
	// write your code between push and pop instructions
	asm volatile
	(
			"push {r4, r5, r6, r7} \n" // do not remove
			// do not add any code before this comment

            // M0 = (M0 + M1 * M1) * (M3 + M1 * M1) + M2
            "mul r4, r1, r1 \n" // r4 = M1 * M1
            "add r4, r0, r4 \n" // r4 = M0 + r4
            "mul r5, r1, r1 \n" // r5 = M1 * M1
            "add r5, r3, r5 \n" // r5 = M3 + r5
            "mul r4, r4, r5 \n" // r4 = r4 * r5
            "add r0, r4, r2 \n" // r0 = r4 + M2

			// do not add any code after this comment
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


int main() {

    stdio_init_all();

    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // TODO: insert code here
    int m0;
    int m1;
    int m2;
    int m3;

    m0 = 1; m1 = 2; m2 = 3; m3 = 4;
    m0 = asm_test(m0, m1, m2, m3);
    if(m0 != 43) fail();

    m0 = 8; m1 = 5; m2 = 6; m3 = 21;
    m0 = asm_test(m0, m1, m2, m3);
    if(m0 != 1524) fail();

    m0 = 3; m1 = 4; m2 = 5; m3 = 1;
    m0 = asm_test(m0, m1, m2, m3);
    if(m0 != 328) fail();

    m0 = 3; m1 = 5; m2 = 7; m3 = 8;
    m0 = asm_test(m0, m1, m2, m3);
    if(m0 != 931) fail();

    m0 = 33; m1 = 22; m2 = 11; m3 = 0;
    m0 = asm_test(m0, m1, m2, m3);
    if(m0 != 250239) fail();

    m0 = 42; m1 = 55; m2 = 12; m3 = 1;
    m0 = asm_test(m0, m1, m2, m3);
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
}
