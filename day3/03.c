#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFF_SIZE 1024

void add_item(char *store[], char *buffer) {
    if (store[0] != NULL) {
        if (store[1] != NULL) {
            // Free the memory of the oldest string in the store
            if(store[2] != NULL) {
                free(store[2]);
            }
            store[2] = store[1];
        }
        store[1] = store[0];
    }

    // Allocate memory for a new string and copy the buffer content
    store[0] = strdup(buffer); // copies sufficient memory and returns a pointer to it
}

int symbol(char *store[], int a, int b) {
    
    //a num b

    //check within the line
    if(a != 0) { 
        a = a - 1;
        if(store[1][a] != '.' && store[1][a] != '\n') { return 1; }
    }

    if(b != 139) { 
        b = b + 1; 
        if(store[1][b] != '.' && store[1][b] != '\n') { return 1; }
    }

    //check below the line
    for(int i = a; i <= b; i++) {
        if(store[0][i] != '.' && store[0][i] != '\n') { return 1; }
    }

    //check above the line
    if(store[2] != NULL) {
        for(int i = a; i <= b; i++) {
            if(store[2][i] != '.' && store[2][i] != '\n') { return 1; }
        }
    }
    return 0;
}

int main(void) {
    FILE *fp;

    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("error, can't open the file!");
        return 1;
    }

    char buffer[BUFF_SIZE];
    char *store[3] = {NULL, NULL, NULL};
    long sum = 0;

    while (fgets(buffer, BUFF_SIZE, fp) != NULL) {
        add_item(store, buffer);

        if(store[2] != NULL) {
            char *p = store[1];

            int start = 0, end = 0;
            int i = 0;

            while(*p) {
                if(isdigit(*p)) {
                    long num = strtol(p, &p, 10); 
                    start = i;
                    if (num > 0 && num < 10) {
                        end = i;
                        i += 2;
                    } else if (num >= 10 && num < 100) {
                        end = i + 1;
                        i += 3;
                    } else if (num >= 100 && num < 1000) {
                        end = i + 2;
                        i += 4;
                    }

                    if(symbol(store, start, end) == 1) { 
                        printf("found match! number: %ld\n", num);
                        sum += num;
                    }
                } else { i++; }
                p++;
            }
        }
    }

    printf("sum: %ld\n", sum);

    // Free the allocated memory for each string in the store
    for (int i = 0; i < 3; ++i) {
        free(store[i]);
    }

    fclose(fp);

    return 0;
}
