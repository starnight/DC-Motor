#include "uart.h"

/* Send string in bytes with blocking. */
uint8_t UARTSendStream(uint8_t *s) {
	uint8_t i;

	/* Enumerate each byte in the string until '\0'. */
	for(i = 0; s[i] != '\0'; i++)
		USARTSend1ByteBlocking(s[i]);

	return i;
}
