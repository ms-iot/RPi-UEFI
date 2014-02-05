#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
 

#define FILE_CHUNK	(32*512)
 
int main (int argc, char* argv[])
{
	unsigned char *buffer = NULL;
	int src_fd = -1;
	int size, offset;
	int dest_fd = -1;
	unsigned int checksum, addr, i;

	buffer = (unsigned char *)malloc(FILE_CHUNK);
	if(NULL == buffer) {
		printf("buffer allocation failed\n");
		goto Exit;
	}

	src_fd = open(argv[1], O_RDONLY);	
	if(src_fd == -1) {
		printf("source file(%s) open error\n", argv[1]);
		goto Exit;
	}

	offset = lseek(src_fd, 0, SEEK_END);	
	if(offset == -1) {
		printf("source file seek error SEEK_END\n");
		goto Exit;
	}

	printf("source file(%s) size = %d bytes\n", argv[1], offset);

	offset = lseek(src_fd, 0, SEEK_SET);	
	if(offset == -1) {
		printf("source file seek error SEEK_SET\n");
		goto Exit;
	}

	size = read(src_fd, (void *)buffer, FILE_CHUNK);
	if(size != FILE_CHUNK) {
		printf("source file read error, size=%d\n", size);
		goto Exit;
	}

	addr = (unsigned int)buffer;

	for(i=0, checksum=0;i<((14*1024) -4);i++)
		checksum += *((unsigned char *)addr++);

	*((unsigned int *)addr) = checksum;

	dest_fd = open("./fwbl2.bin", (O_CREAT|O_RDWR), (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH));
	if(dest_fd == -1) {
		printf("target file(fwbl2.bin) open error\n");
		goto Exit;
	}

	size = write(dest_fd, (void *)buffer, FILE_CHUNK);
	if(size != FILE_CHUNK) {
		printf("target file write error, size=%d\n", size);
		goto Exit;
	}

	offset = lseek(dest_fd, 0, SEEK_END);	
	if(offset == -1) {
		printf("target file seek error SEEK_END\n");
		goto Exit;
	}

	printf("target file(./fwbl2.bin) size = %d bytes\n", offset);

Exit:	
	if(buffer != NULL)
		free(buffer);

	if(src_fd != -1)
		close(src_fd);

	if(dest_fd != -1)
		close(dest_fd);

	return 0;
}
