#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define BUFF_S 1024


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


void copy_count(struct numbers *num, long *cards) {
	
	int matches = 0;
	static int card_id = 0;

	for(int i = 0; i < 25; i++) { // loop for elf numbers
		if((num->elf_num[i] >= num->min) && (num->elf_num[i] <= num->max)) {
			for(int j = 0; j < 10; j++) { // loop for win numbers
				if(num->elf_num[i] == num->win_num[j]) {
					matches++;
				}
			}
		}
	}

	if(matches != 0) {
		for(int j = 1; j <= cards[card_id]; j++) { // for the amount of cards
			for(int i = 1; i <= matches; i++) { // for num of matches
				cards[card_id + i]++;
			}
		}
	}
	card_id++;
	
}

int main(void) {
	
	FILE *fp;
	if((fp = fopen("input.txt", "r")) == NULL) {
		printf("error, can't open file\n");
		return 1;
	}

	char buffer[BUFF_S];
	
	struct numbers card;

	long cards_count[201] = {1}; // at the start one card of each number
	for(int i = 0; i < 201; i++) {
		cards_count[i] = 1;
	}

	long *cards_ptr = cards_count;

	while(fgets(buffer, BUFF_S, fp) != NULL) {
		parse_card(buffer, &card);
		copy_count(&card, cards_ptr);
	}

	long total_cards = 0;
	for(int i = 0; i < 201; i++) {
		total_cards += cards_count[i];
	}

	printf("total cards %ld\n", total_cards);

	fclose(fp);

	return 0;
}
