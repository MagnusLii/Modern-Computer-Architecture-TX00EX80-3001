#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

__attribute__(( naked )) int prt(const char *a)
{
	// the pointer to a character array is passed to the
	// subroutine in R0
	// remember to follow AAPCS:
	// push any register above r3 at the beginning and pop the same registers at the end
	// note: lr needs to be pushed because we are calling another subroutine
    // cortex-M0 requires popping to PC if LR was pushed. See the code below
	asm volatile
	(
			"push { r4, lr } \n" // we need to save return address because we call another subroutine
			// r0 - r3 can (and will be) modified by putchar
			// so you have save the values yourself if you wish to keep
			// them safe. R4-R7 will not be modified by Board_UARTPutChar

			"start: \n" // start of loop
			"ldrb r4, [r0], #1 \n" // load byte from str.
			"cmp r4, #0 \n" // compare byte to 0
			"beq end \n" // if if 0 GOTO end
			
			"cmp r4, #'A' \n" // compare byte to A
			"blt print \n" // if less GOTO print

			"cmp r4, #'Z' \n" // compare byte to Z
			"bgt print \n" // if higher GOTO print

			"orr r4, r4, #0x20 \n" // convert to lower case

			"print: \n"
			"bl putchar \n"  // print r0.

			"end: \n" // end of func
			"pop { r4, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
            // popping to PC will cause return from subroutine (~same as "bx lr")
	);
}

void fail() {
    printf("Failed\n"); // set a break point here
    while(1) {
        tight_loop_contents();
    }
}

void ok() {
    printf("\nAll ok\n"); // set a break point here
}

int main(void) {

    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

	// TODO: insert code here
	printf("\nExercise5\n");

	char test1[] = "Computer Architecture\n";
	char test2[] = "Computer Architecture\n";
	prt(test1);
	if(strcmp(test1, test2)) {
		fail(); // error - string modified
	}
	char test3[] = "Johnny Ca$h:Live @Folsom\n";
	char test4[] = "Johnny Ca$h:Live @Folsom\n";
	prt(test3);
	if(strcmp(test3, test4)) {
        fail(); // error - string modified
	}

	char test5[] = "If you like to gamble, I tell you I'm your man\n";
	char test6[] = "If you like to gamble, I tell you I'm your man\n";
	prt(test5);
	if(strcmp(test5, test6)) {
        fail(); // error - string modified
	}

    ok();

    // Loop forever
    while (true) {
        // Blink LED
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
	return 0 ;
}
