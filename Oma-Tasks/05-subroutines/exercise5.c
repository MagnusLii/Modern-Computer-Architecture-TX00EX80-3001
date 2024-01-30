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

			"mov r4, r0 \n" // copy array start loc to r4

			"start: \n" // start of loop
			"ldrb r0, [r4] \n"

			"cmp r0, #0 \n" // compare r0 to 0
			"beq end \n" // if true GOTO end

			"cmp r0, #'A' \n" // compare r0 to 'A'
			"blt print \n" // if less, GOTO print

			"cmp r0, #'Z' \n" // compare r0 to 'Z'
			"bgt print \n" // if more, GOTO print

			"add r0, r0, #32 \n" // convert to lowercase

			"print: \n" // print character
			"bl putchar \n" // call putchar subroutine
			"add r4, r4, #1 \n" // increment r4 by 1
			"b start \n" // GOTO start

			"end: \n" // end of loop
			"pop { r4, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
            // popping to PC will cause return from subroutine (~same as "bx lr")
	);
}

__attribute__(( naked )) int rot13(const char *a)
{
	asm volatile
	(
			"push { r4, lr } \n"

			"mov r4, r0 \n" // Copy array start loc to r4.

			"start1: \n"

			"ldrb r0, [r4] \n" // Load next letter.

			"cmp r0, #0 \n" // Compare r0 to 0.
			"beq end1 \n" // If true, GOTO end.

			"cmp r0, #'a' \n" // Compare r0 to 'a'.
			"bge lowercase \n" // If more, GOTO lowercase.

			"cmp r0, #'A' \n" // Compare r0 to 'A'.
			"bge uppercase \n" // If more, GOTO uppercase.

			"b 1 \n" // else GOTO print.

			"lowercase: \n"
			"cmp r0, #'z' \n" // Compare r0 to 'z'.
			"bgt print1 \n" // If more, GOTO print.
			"add r0, r0, #13 \n" // Add 13 to r0.
			"cmp r0, #'z' \n" // Compare r0 to 'z'.
			"ble print1 \n" // If less or equal, GOTO print.
			"sub r0, r0, #'z' \n" // Subtract 'z' from r0.
			"sub r0, r0, #1 \n" // Subtract 1 from r0 to account for overflow.
			"add r0, r0, #'a' \n" // Add 'a' to r0.
			"b print1 \n" // GOTO print.

			"uppercase: \n"
			"cmp r0, #'Z' \n" // Compare r0 to 'Z'.
			"bgt print1 \n" // If more, GOTO print.
			"add r0, r0, #13 \n" // Add 13 to r0.
			"cmp r0, #'Z' \n" // Compare r0 to 'Z'.
			"ble print1 \n" // If less or equal, GOTO print.
			"sub r0, r0, #'Z' \n" // Subtract 'Z' from r0.
			"sub r0, r0, #1 \n" // Subtract 1 from r0 to account for overflow.
			"add r0, r0, #'A' \n" // Add 'A' to r0.

			"print1: \n"
			"bl putchar \n" // Call putchar subroutine.
			"add r4, r4, #1 \n" // Increment r4 by 1
			"b start1 \n" // GOTO start.

			"end1: \n"
			"pop { r4, pc } \n"
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

	printf("Test 1\n");
	char test1[] = "Computer Architecture\n";
	char test2[] = "Computer Architecture\n";
	printf("lowercase: ");
	prt(test1);
	printf("rot13: ");
	rot13(test1);
	if(strcmp(test1, test2)) {
		fail(); // error - string modified
	}
	printf("\n\nTest 2\n");
	char test3[] = "Johnny Ca$h:Live @Folsom\n";
	char test4[] = "Johnny Ca$h:Live @Folsom\n";
	printf("lowercase: ");
	prt(test3);
	printf("rot13: ");
	if(strcmp(test3, test4)) {
        fail(); // error - string modified
	}
	printf("\n\nTest 3\n");
	char test5[] = "If you like to gamble, I tell you I'm your man\n";
	char test6[] = "If you like to gamble, I tell you I'm your man\n";
	printf("lowercase: ");
	prt(test5);
	printf("rot13: ");
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
