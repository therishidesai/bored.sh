#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* whitespace = " \t\v\f\r\n";
  char* buffer;
  size_t bufsize = 1;
  size_t characters;

  buffer = (char* )malloc(bufsize * sizeof(char));
  if (buffer == NULL) {
	perror("Unable to allocate buffer");
	exit(1);
  }

  printf("Type something: ");
  characters = getline(&buffer,&bufsize,stdin);
  printf("%zu characters were read.\n",characters);
  printf("You typed: '%s'\n",buffer);
  printf("size: %lu \n", sizeof(buffer));

  char* ptr = strtok(buffer, whitespace);
  char** ptrs = malloc(bufsize * sizeof(char*));
  int i = 0;
  while (ptr != NULL) {
	printf("%s\n", ptr);
	ptrs[i] = ptr;
	i++;
	ptr = strtok(NULL, whitespace);
  }

  printf("%lu \n", sizeof(char**));

  for (int n = 0; n < i; n++) {
	printf("%s\n", ptrs[n]);
  }

  return(0);
}

