#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	    //char** old_ptrs = ptrs;
	    ptrs = realloc(ptrs, bufsize * sizeof(char*));
	    /*if (!ptrs) {
		free(x)
		}*/
	}
	ptr = strtok(NULL, whitespace);
    }

    struct cmd line = {i, ptrs};
    return line;
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
	printf("%d \n", command.size);
	for (int n = 0; n < command.size; n++) {
	    printf("%s\n", command.cmds[n]);
	}
    }
    return(0);
}

