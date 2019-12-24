#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argc != 2) {
		fprintf(stderr, "Invalid input\n");
		exit(1);
	}
	pid_t pid;
	int status;
  struct stat statbuf;

	int fd = open(argv[1], O_RDWR);
	if (fd == -1){
		fprintf(stderr, "Cant open file\n");
	}

	if (fstat(fd, &statbuf) < 0 ) {
		fprintf(stderr,"Fstat error\n");
	} else fstat(fd, &statbuf);


	char* filemap = (char*)mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);

	if (filemap == MAP_FAILED){
		fprintf(stderr,"Error mmap");
	}

	if(close(fd) == -1){
		fprintf(stderr, "Cant close file\n");
	} else close(fd);

	pid = fork();

	if(pid < 0) {
		fprintf(stderr, "Prosses not created\n");
		exit(1);
	} else if(pid == 0){

		char a[255] = {0};
		char b[255] = {0};
		int n = 0;

		while(filemap[n] != '\n' && filemap[n] != EOF) {
			if(n == 256) {
      	fprintf(stderr, "Incorrect command\n");
      	munmap(filemap, statbuf.st_size);
			}

			a[n]= filemap[n];
			n++;
		}
    n++;
		
    int k = 0;
		
		while(filemap[n] != '\n' && filemap[n] != EOF)	{
			if(k == 256) {
      	fprintf(stderr, "Incorrect file name\n");
      	munmap(filemap, statbuf.st_size);
			}
			b[k]= filemap[n];
			n++;
			k++;
		}

		if(execlp(a, a, b, (char*)NULL) == -1){
			fprintf(stderr, "Execlp error\n");
		} else execlp(a, a, b, (char*)NULL);

	}else if(pid > 0){
		if (waitpid(pid, &status, 0) == -1){
			fprintf(stderr, "Waitpid error\n");
		} else waitpid(pid, &status, 0);
		munmap(filemap, statbuf.st_size);
	}
	return 0;
}
