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

			"mov r4, r0 \n" // Copy array start loc to r4.
			"mov r5, #0 \n" // not used

			"loop: \n" // Loop label.

			"ldrb r0, [r4, r5] \n" // Load next letter.

			"cmp r0, #0 \n" // Compare r0 to 0.
			"beq end \n" // If true, GOTO end.

			"cmp r0, #'Z' \n" // Compare r0 to 'z'.
			"bgt print \n" // If more, GOTO print.

			"cmp r0, #'a' \n" // Compare r0 to 'a'.
			"blt print \n" // If less, GOTO print.

			"cmp r0, #'A' \n" // Compare r0 to 'A'.
			"bgt uppercase \n" // If more, GOTO print.

			"lowercase: \n" // Lowercase label.
			"add r0, r0, #13 \n" // Add 13 to r0.
			"cmp r0, #'z' \n" // Compare r0 to 'z'.
			"ble print \n" // If less or equal, GOTO print.
			"sub r0, r0, #'z' \n" // Subtract 'z' from r0.
			"add r0, #97, r0 \n" // Add 'a' to r0. 97 = 'a'
			"b print \n" // GOTO print.

			"uppercase: \n" // Uppercase label.
			"add r0, r0, #13 \n" // Add 13 to r0.
			"cmp r0, #'Z' \n" // Compare r0 to 'Z'.
			"ble print \n" // If less or equal, GOTO print.
			"sub r0, r0, #'Z' \n" // Subtract 'Z' from r0.
			"add r0, #65, r0 \n" // Add 'A' to r0. 65 = 'A'
			"b print \n" // GOTO print.

			"print: \n" // Print label.
			"bl putchar \n" // Call putchar subroutine.
			"add r4, r4, #1 \n" // Increment r4 by 1
			"b start \n" // GOTO start.

			"end: \n"
			"pop { r4, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
            // popping to PC will cause return from subroutine (~same as "bx lr")
	);
}

int main(void) {

    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

	char line[100];
	printf("Enter sentence to encrypt: ");
	fgets(line, 100, stdin);

	prt(line);

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
