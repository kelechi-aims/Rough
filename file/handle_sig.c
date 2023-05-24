#include "shell.h"

/*int loop_exit = 0;*/
/**
 * sig_handle - signal handler for the interrupt signal (Ctrl+C)
 * @sig: signal to handle
 * Return: void
 */
void sig_handle(int sig)
{
	(void)sig;
	loop_exit = 1;
}
