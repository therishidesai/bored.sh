#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

struct cmd {
    int size;
    char** cmds;
};

char* read_line() {
    char* buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char* )malloc(bufsize * sizeof(char));
    if (buffer == NULL) {
		perror("Unable to allocate buffer");
		exit(1);
    }

    printf("bored.sh> ");
    getline(&buffer,&bufsize,stdin);

    return buffer;
}

struct cmd split_line(char* buffer) {
    char* whitespace = " \t\v\f\r\n";
    int bufsize = 1;
    char* ptr = strtok(buffer, whitespace);
    char** ptrs = malloc(bufsize * sizeof(char*));
    int i = 0;
    while (ptr != NULL) {
		ptrs[i] = ptr;
		i++;
		if (i >= bufsize) {
			bufsize += bufsize;
			ptrs = realloc(ptrs, bufsize * sizeof(char*));
		}
		ptr = strtok(NULL, whitespace);
    }

    ptrs[i] = NULL;
    i++;
    struct cmd line = {i, ptrs};
    return line;
}

void kill_children(pid_t c_pid) {
	kill(c_pid, SIGKILL);
}

pid_t run_command(char** cmds) {
	pid_t c_pid, pid;
	int status;

	c_pid = fork();

	if (c_pid == 0){
		execvp(cmds[0], cmds);
		perror("execve failed");
	}else if (c_pid > 0){
		if( (pid = wait(&status)) < 0){
			perror("wait");
			_exit(1);
		}
		signal(SIGINT, kill_children);
	}else{
		perror("fork failed");
		_exit(1);
	}

	return c_pid;
}

int main() {
    while (1) {
		char* line = read_line();
		if (*line == 0 || *line == EOF) {
			printf("exit\n");
			break;
		} else if (strcmp(line, "exit\n") == 0) {
			break;
		}
		struct cmd command = split_line(line);
		run_command(command.cmds);
    }
    return(0);
}

