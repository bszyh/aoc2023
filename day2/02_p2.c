#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 2048

// find the biggest instance of a color

int smallest_game(char *buffer) {

	int max_r = 0, max_g = 0, max_b = 0;
	char *p = strstr(buffer, ":");

	while(*p) {
		if(isdigit(*p)) {
			long val = strtol(p, &p, 10);
			//printf("number: %ld\n", val);
			p += 1;
			switch (*p) {
				case 'r':
					if(val > max_r) { max_r = val; }
					break;
				case 'g':
					if(val > max_g) { max_g = val; }
					break;
				case 'b':
					if(val > max_b) { max_b = val; }
					break;
			}
		} else { 
			p++;
		}
	}	

	return max_r * max_g * max_b;
}

int main(void) {
	
	FILE *fp;

	if(fopen("input.txt", "r") == NULL) {
		printf("error, can't open the file!");
	} else {
		fp = fopen("input.txt", "r");
	}

	char buffer[BUFFER_SIZE];

	int sum = 0;

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		sum += smallest_game(buffer);
	}

	printf("sum of powers for the possible games: %d\n", sum);
	fclose(fp);

	return 0;
}
