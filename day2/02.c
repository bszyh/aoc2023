#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 2048

int find_anomaly(char *buffer) {
	char *p = strstr(buffer, ":");

	while(*p) {
		if(isdigit(*p)) {
			long val = strtol(p, &p, 10);
			//printf("number: %ld\n", val);
			p += 1;
			switch (*p) {
				case 'r':
					if(val > 12) { return 1; }
					break;
				case 'g':
					if(val > 13) { return 1; }
					break;
				case 'b':
					if(val > 14) { return 1; }
					break;
			}
		} else { 
			p++;
		}
	}	
	
	return 0;
}

int main(void) {
	
	FILE *fp;

	if(fopen("input.txt", "r") == NULL) {
		printf("error, can't open the file!");
	} else {
		fp = fopen("input.txt", "r");
	}

	char buffer[BUFFER_SIZE];

	int id = 1;
	int p_games = 0;

	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
		if(find_anomaly(buffer) == 0) {
			p_games += id;
		} else {
			printf("found anomaly at id: %d\n", id);
			printf("%s", buffer);
		}
		id += 1;
	}

	printf("id sum: %d\n", p_games);

	fclose(fp);

	return 0;
}
