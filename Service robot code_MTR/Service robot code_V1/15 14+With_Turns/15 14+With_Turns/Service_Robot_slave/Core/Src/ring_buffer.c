/*
 * ring_buffer.c
 *
 *  Created on: 19-Dec-2022
 *      Author: Anusha
 */


/*
 * ring_buffer.c
 *
 *  Created on: 08-Dec-2022
 *      Author: Anusha
 */


#include "ring_buffer.h"
#include <string.h>
#include "usart.h"
#include "main.h"
#include "rgb.h"

/**** define the UART you are using  ****/





/****************=======================>>>>>>>>>>> NO CHANGES AFTER THIS =======================>>>>>>>>>>>**********************/

ring_buffer rx_buffer = {{ 0 }, 0, 0};

ring_buffer *_rx_buffer;



void Ringbuf_init(void)
{
  _rx_buffer = &rx_buffer;

  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(uart, UART_IT_ERR);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(uart, UART_IT_RXNE);
}


void store_byte(uint8_t byte, ring_buffer *buffer)
{
	int i = (unsigned int)(buffer->head + 1) % UART_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if(i != buffer->tail) {
    buffer->buffer[buffer->head] = byte;
    buffer->head = i;
  }

  /*
  Reporting Pi as buffer has been overflow
  Reporting packet:
  F7 F6 00 00 00 00 00 00 09 00 08 00 00 00 00 00 00 00 00 00 00 F8
  if 4th byte in the frame is 0, that indicates buffer flow
  tx_frame[4]=0x00;

  And also RGB ring lights up in Red
  */

  else{
	  tx_frame[4]=0x00;
	  HAL_UART_Transmit(&huart2, tx_frame, 22,25);
	  Set_RGB_Red();
  }

}



uint8_t Uart_read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if(_rx_buffer->head == _rx_buffer->tail)
  {
    return -1;
  }
  else
  {
    uint8_t c = _rx_buffer->buffer[_rx_buffer->tail];
    _rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
    return c;
  }
}

/* checks if the new data is available in the incoming buffer
 */
int IsDataAvailable(void)
{

	return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % UART_BUFFER_SIZE;
}

