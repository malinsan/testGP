#ifndef STRINGPRINTER_H
#define STRINGPRINTER_H

#include <stm32f4xx_usart.h>

class StringPrinter
{
	public:
		void printStartUp();
		void printText(char * s);
		void printInt(int i);
		StringPrinter();
	private:
		void USART_PutString(char *s);
		void USART_PutChar(char c);
		void init_USART2(void);
		bool usartInit;
};


#endif
