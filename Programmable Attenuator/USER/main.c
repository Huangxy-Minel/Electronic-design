#include "sys.h"
#include "delay.h"
#include "Task.h"

int main(void)
{ 
	Init_Task();
	while(1)
	{
		Can_Send();
	}
}
