#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 2048

//find the first and last digit in the string
//then make a double digit number 
//find the sum of all the numbers

// ascii digits: 0 - 48 : 9 - 57
// problem: number can be a single digit

int main() {
	
	FILE *fp;
	char buffer[BUFF_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		printf("error, can't open the file");
	} else { fp = fopen("input.txt", "r"); }

	int first_d = 0;
	int second_d = 0;
	int digits = 0;
	int number = 0;
	int sum = 0;

	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
		
		printf("%s", buffer);

		for(int i = 0; i < strlen(buffer); i++) {
			if((buffer[i] > 47) && (buffer[i] < 58)) {
				digits++;
				if(first_d == 0) {
					first_d = (int)buffer[i] - 48;
				} else {
					second_d = (int)buffer[i] - 48;
				}
			}
		}

		if(digits != 1) {
			number = first_d * 10 + second_d;	
		} else { 
			number = first_d * 10 + first_d;
		}
		
		sum += number;

		printf("first_d: %d, second_d: %d, digits: %d, number: %d, sum: %d\n", first_d, second_d, digits, number, sum);

		first_d = 0;
		second_d = 0;
		digits = 0;
	}

	printf("sum: %d", sum);



	return 0;
}
