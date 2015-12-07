#include <stdio.h>

#define MAX_TABLE_SIZE 20

int main()
{
	int r;
	int All_Taken[MAX_TABLE_SIZE];

	printf("Populating Tables\n");

	for (r = 0; r < MAX_TABLE_SIZE; r++) {
		All_Taken[r] = 1;
	}

	for (r = 0; r < MAX_TABLE_SIZE; r++) {
		printf("%d\n", All_Taken[r]);
	}
	getchar();

}