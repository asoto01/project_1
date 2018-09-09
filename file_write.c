#include <stdio.h>
#include <string.h>

//sample string 00000000000000001; length = 17; maxIndex = 16;output should be -16-1
static char *CompressBinary(char buff[]) {
	int i = 0;
	int count0 = 0, count1 = 0;
	char localString[strlen(buff)];
	char *stringReturn = "Nah, man";
	while (i != strlen(buff)) {
		if(buff[i] == '0') 
			count0++;
		else if (buff[i] == '1')
			count1++;
		if (count0 > 0 && count1 > 0) { 
			if (count0 >= 16) {
				printf("%d\n",count0);

			// printf("%d\n", count0);
			//snprintf(localString, sizeof(localString), "-%d-", count0);
			//printf("%s\n", localString);
			//stringReturn = "HELLO";
			}	
			count0 = 0;
		}	else if (count1 > 0 && count0 > 0) {
			if (count1 >= 16) {
			printf("%d\n",count1);
			}
			count1 = 0;
		}
		i++;
	}
	return stringReturn;
}
int main() {
	FILE *fp;
	char buff[255];

	fp = fopen("./tmp/test1.txt", "r+");
	fscanf(fp, "%s",buff);
	printf("%s\n", buff);
	printf("test\n");
	char *returnedString;
	returnedString = CompressBinary(buff);
	printf("%s\n", returnedString);

	return 0;
}
