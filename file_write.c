#include <stdio.h>
#include <string.h>

//sample string in ./tmp/test1.txt is 00000000000000001; length = 17; maxIndex = 16;output should be -16-1
void compress(char *A, int size);

int main() {
	FILE *fp;
	char buff[255];

	fp = fopen("./tmp/test1.txt", "r+");
	fscanf(fp, "%s",buff);
	int size = sizeof(buff) / sizeof(*buff);
	char A[size];
	memcpy(A, buff, size * sizeof(char));
	printf("Orignal array from fscanf: %s\n", buff);
	printf("Copied array: %s\n", A);
	compress(A, size);
	printf("Compressed array: %s\n", A);
	return 0;
}

void compress(char *A, int size) {
	int index = 0; // used for while loop targeting *A
	int count0 = 0; // used for counting 0s
	int count1 = 0; // used for counting 1s
	char A1[size]; // local array
	// loop through array, terminates when detects null character
	while (A[index] != '\0') {
		// counts 1s or 0s in array
		if (A[index] == '0') {
			count0++;
		} else if (A[index] == '1') {
			count1++;
		}
		// check for every time that a series is broken
		if (count0 > 0 && count1 > 0) {
			if (count0 >= 16) {
				char str[12];                 
				sprintf(str, "-%d-", count0); 
				strcat(A1, str);    
				count0 = 0;
			} else if (count1 >= 16) {
				char str[12];
				sprintf(str, "-%d-", count1);
				strcat(A1, str);
				count1 = 0;
			} else {
				if (A[index] == '0'){
					char str[count1];
					for (int i = 0; i < count1; i++) {
						str[i] = 1;
						strcat(A1, str);
						count1 = 0;
					}
				} else {
					if (A[index] == '1'){
						char str[count0];
						for (int i = 0; i < count0; i++) {
						str[i] = 0;
						strcat(A1, str);
						count0 = 0;
						}
					}
				}
			}
		}
		index++;
	}
	if (count0 > 0) {
		char str[count0];
		for (int i = 0; i < count0; i++) {
			str[i] = '0';
		}
		str[count0] = '\0';
		strcat(A1, str);
	} else if (count1 > 0) {
		char str[count1];
		for (int i = 0; i < count1; i++) {
			str[i] = '1';
		}	
		str[count1] = '\0';
		strcat(A1, str);
	}
	memcpy(A, A1, size * sizeof(char));
}
