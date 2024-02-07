#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define BUFF_S 1024

/*
 * 1. parse the winning numbers
 * 2. get the biggest and smallest winning number
 * 3. parse other numbers
 * 4. check if number is in range (smallest win num, biggest win num)
 * 5. if yes, check num by num if its a winning number
 */

struct numbers {
	long win_num[10];
	long max, min;
	long elf_num[25];
};

void parse_card(char *buffer, struct numbers *card_num) {


	// winning numbers
	char *p = &buffer[9]; // start after the "Card num:"
	int i = 0;
	card_num->max = 0; 
	card_num->min = 100; //min as 100 cuz all nums are two digits

	while(*(p++) != '|') {
		if(isdigit(*p)) {
			long number = strtol(p, &p, 10);	
			card_num->win_num[i] = number;
			if(number > card_num->max) { card_num->max = number; }
			if(number < card_num->min) { card_num->min = number; }
			i++;
		}
	}
	
	// now the numbers we have
	p = &buffer[40]; //set p to "|" char in string
	int j = 0;

	while(*(++p)) {
		long number = strtol(p, &p, 10);	
		card_num->elf_num[j] = number;
		j++;
	}
}

int win_points(struct numbers *num) {
	
	int points, power = 0, flag = 0;

	for(int i = 0; i < 25; i++) { // loop for elf numbers
		if((num->elf_num[i] >= num->min) && (num->elf_num[i] <= num->max)) {
			for(int j = 0; j < 10; j++) { // loop for win numbers
				if(num->elf_num[i] == num->win_num[j]) {
					//printf("win! %ld and %ld\n", num->elf_num[i], num->win_num[j]);
					flag = 1;
					points = pow(2, power);
					power++;
				}
			}
		}
	}
	
	if(flag) { return points; }
	else { return 0; }
}

int main(void) {
	
	FILE *fp;
	if((fp = fopen("input.txt", "r")) == NULL) {
		printf("error, can't open file\n");
		return 1;
	}

	char buffer[BUFF_S];
	
	struct numbers card;
	int sum = 0;

	while(fgets(buffer, BUFF_S, fp) != NULL) {
		parse_card(buffer, &card);
		sum += win_points(&card);
	}
	
	printf("sum: %d\n", sum);

	fclose(fp);

	return 0;
}
