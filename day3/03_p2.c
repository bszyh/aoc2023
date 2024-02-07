#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFF_SIZE 1024

struct Gear {
    long num1;
    long num2;
};

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

void is_gear0(char *store[], int pos, struct Gear *g) {

    int a = pos - 1;
    int b = pos + 1;

    int nc = 1;
    long number = 0;

    // within the line
    if(pos != 0) {
        if(isdigit(store[1][a])) {
            while(isdigit(store[1][a])) {
                number += nc * (store[1][a--] - '0');
                nc *= 10;
            }
            g->num1 = number;
        }
    }

    if(pos != 139) {
        if(isdigit(store[1][b])) {
            char *cp = &store[1][b];
            number = strtol(cp, &cp, 10);
            if(g->num1 == 0) { g->num1 = number; }
            else { g->num2 = number; }
        }
    }
}

void is_gears(char *store[], int level, int pos, struct Gear *g) {

    char *a = &store[level][pos - 1];
    char *b = &store[level][pos];
    char *c = &store[level][pos + 1];

    if(isdigit(*a) == 0 && isdigit(*b) == 0 && isdigit(*c) == 0) { return; }

    if(isdigit(*a) && isdigit(*b) && isdigit(*c)) {
        long number = strtol(a, &a, 10);
        if(g->num1 == 0) { g->num1 = number; }
        else { g->num2 = number; }
    } else {
        char *tmp = a;
        if(isdigit(*(a - 1)) && isdigit(*a)) {
            while(isdigit(*(--a))) {
                tmp = a;
            }
        }
        long num1 = 0, num2 = 0;
        while(tmp <= c) {
            if(isdigit(*tmp)) {
                if(num1 == 0) {
                   num1 = strtol(tmp, &tmp, 10);
                   if(g->num1 == 0) { g->num1 = num1; }
                   else { g->num2 = num1; }
                } else {
                   num2 = strtol(tmp, &tmp, 10);
                   if(g->num1 == 0) { g->num1 = num2; }
                   else { g->num2 = num2; }
                }
            }   
            tmp++;
        }
    }
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
            int i = 0;

            while(*p) {
                    if(*p == '*') {
                        struct Gear g = {0, 0};
                        is_gear0(store, i, &g);
                        is_gears(store, 0, i, &g);
                        is_gears(store, 2, i, &g);
                        
                        if(g.num1 != 0 && g.num2 != 0) {
                            sum += g.num1 * g.num2;
                        }
                    }
                i++;
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
