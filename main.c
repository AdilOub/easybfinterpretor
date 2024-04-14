#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(int argc, char* argv[]){
    printf("Hello World\n");
    if(argc < 3){
        printf("Usage: %s \"<code en brainfuck>\" <memory>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* command = argv[1];
    int memory = atoi(argv[2]);
    if(memory == 0){
        printf("Memory is 0 or not an interger\n");
        printf("Usage: %s \"<code en brainfuck>\" <memory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return 0;
}

int interpret(char* memory, char* cmd, int index, int size){
    if(index < 0 || index >= size){
        printf("\n ERROR: out of memory");
        return EXIT_FAILURE;
    }
    switch (*cmd)
    {
    case '\0':
        printf("\n FIN DU PROGRAMME\n");
        return EXIT_SUCCESS;
        break;
    case '>':
        interpret(memory+1, cmd+1, index+1, size);
        break;
    case '<':
        interpret(memory-1, cmd+1, index-1, size);
    case '+':
        (*memory)++;
        interpret(memory, cmd+1, index, size);
        break;
    case '-':
        (*memory)--;
        interpret(memory, cmd+1, index, size);    
    case '.':
        printf("%c", *memory);
        interpret(memory, cmd+1, index, size);    
        break;
    case ',':
        char c = getc(stdin);
        *memory = c;
        interpret(memory, cmd+1, index, size); 
    case '[':
        if(*memory == 0){
            char* next = search_closed_bracket(cmd);
            interpret(memory, next, index, size);
        }  
        break;
    case ']':
        if(*memory != 0){
            char* prev = search_opened_bracket(cmd);
            interpret(memory, prev, index, size);
        }  
        break;
    }
}

char* search_closed_bracket(char* cmd){
    int count = 1;
    while(*cmd != '\0'){
        if(*cmd == '['){
            count++;
        }
        if(*cmd == ']'){
            count--;
        }
        if(count == 0){
            return cmd;
        }
        cmd++;
    }
    exit(EXIT_FAILURE);
}

char* search_opened_bracket(char* cmd){
    int count = 1;
    while(*cmd != '\0'){ //TODO UNSAFE CODE HERE
        if(*cmd == ']'){
            count++;
        }
        if(*cmd == '['){
            count--;
        }
        if(count == 0){
            return cmd;
        }
        cmd--;
    }
    exit(EXIT_FAILURE);
}