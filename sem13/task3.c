#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

// Программа принимает в аргументах командной строки 2 параметра:

//     file1 file2
// Требуется скопировать содержимое из file1 в file2 в обратном порядке байт.

int main(int argc, char *argv[]) {
	if (argc < 3) {
		return 1;
	}
	struct stat file_stat;
	stat(argv[1], &file_stat);
	int size1 = file_stat.st_size;
	int fd1 = open(argv[1], O_RDONLY);
	char *file1 = mmap(NULL, size1, PROT_READ, MAP_PRIVATE, fd1, 0);
	int fd2 = open(argv[2], O_RDWR);
	ftruncate(fd2, size1);
 	char *file2 = mmap(NULL, size1, PROT_WRITE, MAP_PRIVATE, fd2, 0);
	if(file1 == MAP_FAILED) {
		puts("File 1 failed");
	}
	if(file2 == MAP_FAILED) {
		puts("File 2 failed");
	}
	for (int i=size1-1; i>=0; --i) {
		file2[size1 - i - 1] = file1[i];
	} 
	munmap(file1, size1);
	munmap(file2, size1);
	close(fd1);
	close(fd2);
	return 0;
}