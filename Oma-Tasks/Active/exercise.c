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
        "push {r4, lr} \n"      // Save r4 and lr
        "loop: \n"
        "ldrb r4, [r0], #1 \n"  // Load a byte from the string and increment the pointer
        "cmp r4, #0 \n"         // Check if the byte is null (end of string)
        "beq end \n"
        "cmp r4, #'A' \n"       // Compare with ASCII code of 'A'
        "blt print_char \n"     // If less than 'A', print the character unmodified
        "cmp r4, #'Z' \n"       // Compare with ASCII code of 'Z'
        "bgt print_char \n"     // If greater than 'Z', print the character unmodified
        "orr r4, r4, #32 \n"    // Convert uppercase to lowercase by setting bit 5
        "print_char: \n"
        "bl putchar \n"          // Call putchar with the modified or unmodified character
        "b loop \n"             // Repeat for the next character
        "end: \n"
        "pop {r4, pc} \n"        // Restore r4 and return
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
