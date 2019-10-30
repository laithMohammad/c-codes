#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InputBuffer {
    char *buffer;
    size_t input_length;
    ssize_t buffer_length;
};

//This Factory will be instantiated only once and then reused again
struct nputBuffer* inputBufferFactory() {
    struct InputBuffer* inputBuffer = malloc(sizeof(struct InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;
    return inputBuffer;
}

void promptREPL() {
	printf("query>");
}

void readInput(struct InputBuffer* input_buffer) {
	size_t input_length = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
	if(input_length > 0) {
		input_buffer->input_length = input_length - 1;
		input_buffer->buffer[input_length - 1] = 0; //Remove the last char (new line) from the inserted string
	}
}

void close_buffer(struct InputBuffer* ib) {
	free(ib->buffer);
	free(ib);
}

int main(int argc, char *argv[]) {
	struct InputBuffer* input_buffer = inputBufferFactory();
	while(true) {
		promptREPL();		
		readInput(input_buffer);
		if(strcmp(input_buffer->buffer, "exit()")== 0) {
			printf("\nExiting...\n");
			close_buffer(input_buffer);
			exit(EXIT_SUCCESS);
		} else {
			printf("\nUnrecognized command: %s\n", input_buffer->buffer);
		}
	}
	return 0;
}


