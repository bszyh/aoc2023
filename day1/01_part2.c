#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 2048

//find the first and last digit in the string
//then make a double digit number 
//find the sum of all the numbers

// ascii digits: 0 - 48 : 9 - 57
// problem: number can be a single digit - then the number is single_digit * 10 + single_digit

int main() {
	
	FILE *fp;
	char buffer[BUFF_SIZE];

	if(fopen("input.txt", "r") == NULL) {
		printf("error, can't open the file");
	} else { fp = fopen("input.txt", "r"); }

	int number = 0;
	int sum = 0;

	const char num_words[9][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	
	char *arr_p;

	while(fgets(buffer, BUFF_SIZE, fp) != NULL) {
		
		printf("%s", buffer);

		int last_char = strlen(buffer) - 2; // -1 for the end of line char and another for other "carriage return" garbage

		int first_d = 0;
		int second_d = 0;

		char *first_dp = &buffer[last_char];
		char *second_dp = &buffer[0];

		arr_p = buffer;
		for(int i = 0; buffer[i] != '\n'; i++) {
			if((buffer[i] > 47) && (buffer[i] < 58)) {
				if(first_d == 0) {
					first_d = (int)buffer[i] - 48;
					first_dp = &buffer[i];
				} else {
					second_d = (int)buffer[i] - 48;
					second_dp = &buffer[i];
				}
			}
		}

		printf("(1) first_d = %d, second_d = %d\n", first_d, second_d);
		

		char *first_word = &buffer[last_char];
		char *second_word = &buffer[0];

		for(int i = 0; i < 9; i++) {
			char *haystack = buffer;
			while ((haystack = strstr(haystack, num_words[i])) != NULL) {

				if(second_d == 0) {
					if(haystack > first_dp) { // set haystack as second digit
						second_dp = haystack;
						second_d = i + 1;
					} else if (haystack < first_dp) {
						second_d = first_d;
						second_dp = first_dp;
						first_dp = haystack;
						first_d = i + 1;
					}
				}

				if(second_d != 0 && haystack > second_dp) {
					second_dp = haystack;
					second_d = i + 1;
				}

				if(haystack < first_dp) {
					first_dp = haystack;
					first_d = i + 1;
				}
				haystack += strlen(num_words[i]) - 1;
			}
		}
				
		printf("first_d = %d, second_d = %d\n", first_d, second_d);
		
		if(first_d != 0 && second_d != 0) {
			number = first_d * 10 + second_d;
		} else { number = first_d * 10 + first_d; }
		
		sum += number;

		printf("number: %d, sum: %d\n", number, sum);
	}

	//printf("sum: %d", sum);

	fclose(fp);

	return 0;
}
