#include <stdio.h>
#include <string.h>

void compress(char *A, int size);

int main() {
	FILE *fp;
	char buff[255];

	fp = fopen("./tmp/test2.txt", "r+");
	fgets(buff, 255, (FILE*)fp);
	int size = sizeof(buff) / sizeof(*buff);
	char A[size];
	memcpy(A, buff, size * sizeof(char));
	printf("Orignal array from fgets: %s\n", buff);
	printf("Copied array: %s\n", A);
	compress(A, size);
	printf("Compressed array: %s\n", A);
	printf("\n");
	fgets(buff, 255, (FILE*)fp);
	size = sizeof(buff) / sizeof(*buff);
	char A1[size];
	memcpy(A1, buff, size * sizeof(char));
	printf("Second array from fgets: %s\n", buff);
	printf("Copied array: %s\n", A1);
	compress(A1, size);
	printf("Compressed array: %s\n", A1);
	printf("\n");
	fgets(buff, 255, (FILE*)fp);
	size = sizeof(buff) / sizeof(*buff);
	char A2[size];
	memcpy(A2, buff, size * sizeof(char));
	printf("Third array from fgets: %s\n", buff);
	printf("Copied array: %s\n", A2);
	compress(A2, size);
	printf("Compressed array: %s\n", A2);
	fclose(fp);
	return 0;
}

void compress(char *A, int size) {
	int index = 0; // used for while loop targeting *A
	int count0 = 0; // used for counting 0s
	int count1 = 0; // used for counting 1s
	char A1[size]; // local array
	A1[0] = '\0'; // needed since strcat will be called on A1
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
				sprintf(str, "+%d+", count1);
				strcat(A1, str);
				count1 = 0;
			} else {
				if (A[index] == '0'){
					char str[count1];
					for (int i = 0; i < count1; i++) {
						str[i] = '1';	
					}
					str[count1] = '\0';
					strcat(A1, str);
					count1 = 0;
				} else {
					if (A[index] == '1'){
						char str[count0];
						for (int i = 0; i < count0; i++) {
						str[i] = '0';
						}
						str[count0] = '\0';
						strcat(A1, str);
						count0 = 0;

					}
				}
			}
		}
		index++;
	}
	if (count0 > 0) {
		if (count0 >= 16) {
			char str[12];                 
			sprintf(str, "-%d-", count0); 
			strcat(A1, str);  
		} else {
			char str[count0];
			for (int i = 0; i < count0; i++) {
				str[i] = '0';
			}
			strcat(A1, str);
		}
	} else if (count1 > 0) {
		if (count1 >= 16) {
			char str[12];
			sprintf(str, "+%d+", count1);
			strcat(A1, str);

		} else {
			char str[count1];
			for (int i = 0; i < count1; i++) {
				str[i] = '1';
			}	
			str[count1] = '\0';
			strcat(A1, str);
		}
	}
	memcpy(A, A1, size * sizeof(char));
}
