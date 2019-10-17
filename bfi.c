#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16
#define MAX_FILE_SIZE 1024 * 1024 // 1MB
#define BUFFER_SIZE 2048 // 2KB

#define true 1
#define false 0

typedef unsigned char bool;

void execute(char* str, const unsigned long length) {
    int heap[SIZE];
    unsigned long pointer = 0;
    bool comment = false;

    for (unsigned long i = 0; i < SIZE; i++)
        heap[i] = 0;

    for (unsigned long i = 0; i < length; i++) {
        char cur = str[i];
     
        if (comment) {
            switch (cur) {
                case '\n':
                    comment = false;
                    break;
            }
        } else {
            switch (cur) {
                case '#':
                    comment = true;
                    break;
                
                case '+':
                    heap[pointer]++;
                    break;
                
                case '-':
                    heap[pointer]--;
                    break;
                
                case '>':
                    pointer++;
                    break;
                
                case '<':
                    pointer--;
                    break;

                case '.':
                    printf("%d\n", heap[pointer]);
                    break;

                case ',':
                    scanf("%d", &heap[pointer]);
                    break;
                
                case '[':

                    if (heap[pointer] == 0) {
                        int paranthesis = 1;
                        int j = i;
                        bool unbalanced = true;

                        while (j < length) {
                            j++;
                            if (str[j] == '[')
                                paranthesis++;
                            else if (str[j] == ']')
                                paranthesis--;
                            
                            if (paranthesis == 0) {
                                i = j;
                                unbalanced = false;
                                break;
                            }
                            printf("%d", paranthesis);
                        }
                        if (unbalanced)
                            printf("Unbalanced pharanthesis error!");
                    }
                    break;
                
                case ']':

                    if (heap[pointer] != 0) {
                        int paranthesis = 1;
                        int j = i;
                        bool unbalanced = true;

                        while (j >= 0) {
                            j--;
                            if (str[j] == ']')
                                paranthesis++;
                            else if (str[j] == '[')
                                paranthesis--;
                            
                            if (paranthesis == 0) {
                                i = j;
                                unbalanced = false;
                                break;
                            }
                        }
                        if (unbalanced)
                            printf("Unbalanced pharanthesis error!");
                    }
                    break;
            }
        }        
    }
    
}


void main(int argv, char** argc) {
    if (argv != 2) {
        printf("usage: bfi <file> \n");
    } else {
        FILE* file = fopen(argc[1], "r");

        if (file == NULL) {
            printf("bfi: cannot find the specified file\n");
            return;
        }

        char content[MAX_FILE_SIZE];
        char buffer[BUFFER_SIZE];

        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
            strcat(content, buffer);

        unsigned long size = 0;

        for (unsigned long i = 0; i < MAX_FILE_SIZE; i++) {
            if (content[i] == 0) {
                size = i + 1;
                break;
            }
        }

        fclose(file);

        execute(content, size);
    }
}