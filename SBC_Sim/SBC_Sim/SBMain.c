#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 20000

int All_Taken[MAX_TABLE_SIZE];
int None_Taken[MAX_TABLE_SIZE];
int Alternating[MAX_TABLE_SIZE];


void Populate_Tables(void)
{
	int r;

	/* Populate the tables */
	printf("Populating Tables...\n");

	for (r = 0; r < MAX_TABLE_SIZE; r++)
	{
		All_Taken[r] = 1;
	}

	for (r = 0; r < MAX_TABLE_SIZE; r++)
	{
		None_Taken[r] = 0;
	}

	for (r = 0; r < MAX_TABLE_SIZE; r++)
	{
		if (r % 2 == 0)
		{
			Alternating[r] = 1;
		}
		else
		{
			Alternating[r] = 0;
		}

	}
}

// what to return?
void Test_List(int Num_Bits, int Taken_Not_Taken_List[MAX_TABLE_SIZE])
{
	int r;
	// initial prediction is borderline not taken
	int Prediction = Num_Bits / 2;
	for (r = 0; r < MAX_TABLE_SIZE; r++)
	{
		if (Prediction > Num_Bits / 2)
		{
			// predict taken
			// update prediction
			// record miss or hit
		}
		else
		{
			// predict not taken
			// update prediction
			// record miss or hit
		}
	}
}

int clean_stdin()
{
	while (getchar() != '\n');
	return 1;
}

int main()
{
	printf("The current taken / not taken table size is %d\n\n", MAX_TABLE_SIZE);

	int Bit_Size = 0;
	char c;
	do
	{
		printf("Choose a size for the saturating bit counter \nEnter an integer from 1 to : 1,000,000 bits: ");

	} while (((scanf("%d%c", &Bit_Size, &c) != 2 || c != '\n') && clean_stdin()) || Bit_Size<1 || Bit_Size>1000000);

	Populate_Tables();
	printf("\nPress enter to continue ...\n");
	getchar();

	return 0;

}