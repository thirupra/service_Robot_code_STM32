/*
 * ring_buffer.h
 *
 *  Created on: 19-Dec-2022
 *      Author: Anusha
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include "stm32f1xx_hal.h"


/* change the size of the buffer */
#define UART_BUFFER_SIZE 128
#define uart &huart2

typedef struct
{
  uint8_t buffer[UART_BUFFER_SIZE];
  volatile uint8_t head;
  volatile uint8_t tail;
} ring_buffer;

extern ring_buffer rx_buffer;
extern ring_buffer *_rx_buffer;


/* Initialize the ring buffer */
void Ringbuf_init(void);

/* reads the data in the rx_buffer and increment the tail count in rx_buffer */
uint8_t Uart_read(void);


/* Stores the data into buffer*/
void store_byte(uint8_t byte, ring_buffer *buffer);


/* Checks if the data is available to read in the rx_buffer */
int IsDataAvailable(void);


#endif /* INC_RING_BUFFER_H_ */
