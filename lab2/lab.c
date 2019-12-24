#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
  // Если программе не переданы параметы
	if (argc != 3) {
		fprintf(stderr, "invalid input\n");
		exit(2);
	}

  // идентификатор потока
	pid_t pid;
	int status;

  // создание нового потока
	pid = fork();

  // поток не создан
	if (pid < 0) {
		fprintf(stderr, "prosses not created\n");
		exit(1);
	} else if (pid == 0){ // дочерний процесс
		int fd = open(argv[2], O_RDWR); // откыть для чтения

		if (fd == -1){
			fprintf(stderr, "can`t open file\n");
		} else fprintf(stdout, ">fd: correct\n");

		if(dup2(fd, 0) == -1){ // заменить файловый дескриптор на поток стандартного ввода
			fprintf(stderr, "dup eror\n");
		} else {
			dup2(fd, 0);
			fprintf(stdout, ">dup2: correct\n");
		}

		if (execlp(argv[1], argv[2], NULL) == -1){ // выполнить программу с аргументами agrv[1] и argv[2]
			fprintf(stderr, "exec eror\n");
		} else execl(argv[1], argv[2], NULL);

		if(close(fd) == -1){
			fprintf(stderr, "can`t close file\n"); // закрытие файла связанного с дескриптором
		} else close(fd);

	} else if(pid > 0){ // родительский процесс
      
		if (waitpid(pid, &status, 0) == -1){ // ожидание дочернего процесса
			fprintf(stderr, "smth wrong with parent\n"); // нужно ждать любого дочернего процесса, чей идентификатор группы равен абсолютному значению pid.
		} else {
			waitpid(pid, &status, 0);
			fprintf(stdout, ">waitpid: correct\n"); // корректно
		}
	}
	return 0;
}
