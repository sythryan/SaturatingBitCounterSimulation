#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TABLE_SIZE 10000000
#define MIN_TABLE_SIZE 1

int All_Taken[MAX_TABLE_SIZE];
int None_Taken[MAX_TABLE_SIZE];
int Alternating[MAX_TABLE_SIZE];

void Populate_Tables(int Chosen_Table_Size)
{
	int r;

	/* Populate the tables */
	printf("Populating Tables...\n");

	for (r = 0; r < Chosen_Table_Size; r++)
	{
		All_Taken[r] = 1;
	}

	for (r = 0; r < Chosen_Table_Size; r++)
	{
		None_Taken[r] = 0;
	}

	for (r = 0; r < Chosen_Table_Size; r++)
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

int Prediction_Plus(int Prediction, int Bit_Size)
{
	if (Prediction < (pow(2, Bit_Size) - 1))
	{
		Prediction++;
	}
	return Prediction;
}

int Prediction_Minus(int Prediction)
{
	if (Prediction > 0)
	{
		Prediction--;
	}
	return Prediction;
}


//Returns Hit Total
int Test_List(int Num_Bits, int Taken_Not_Taken_List[MAX_TABLE_SIZE], int Chosen_Table_Size)
{
	int r;
	int Hit_Total = 0;
	// initial prediction is borderline not taken
	int Prediction = Num_Bits / 2;
	for (r = 0; r < Chosen_Table_Size; r++)
	{
		if (Prediction >= (Num_Bits / 2))
		{
			// predict taken
			// update prediction & record miss or hit
			if (Taken_Not_Taken_List[r] == 1)
			{
				Prediction = Prediction_Plus(Prediction, Num_Bits);
				Hit_Total++;
			}
			else
			{
				Prediction = Prediction_Minus(Prediction);
				Hit_Total--;
			}
		}
		else
		{
			// predict not taken
			// update prediction & record miss or hit
			if (Taken_Not_Taken_List[r] == 1)
			{
				Prediction = Prediction_Plus(Prediction, Num_Bits);
				Hit_Total--;
			}
			else
			{
				Prediction = Prediction_Minus(Prediction);
				Hit_Total++;
			}
		}
	}
	return Hit_Total;
}

int clean_stdin()
{
	while (getchar() != '\n');
	return 1;
}

int main()
{

	int Hit_Total = 0;
	int Miss_Total = 0;
	int Bit_Size = 0;
	int Table_Size = 0;
	char c;

	do
	{
		printf("Choose a size for the Taken / Not Taken tables. \nEnter an integer from 1 to : 1,000,000: ");

	} while (((scanf("%d%c", &Table_Size, &c) != 2 || c != '\n') && clean_stdin()) || Table_Size < MIN_TABLE_SIZE || Table_Size > MAX_TABLE_SIZE);

	do
	{
		printf("\nChoose a size for the saturating bit counter. \nEnter an integer from 1 to : 1,000,000 bits: ");

	} while (((scanf("%d%c", &Bit_Size, &c) != 2 || c != '\n') && clean_stdin()) || Bit_Size < MIN_TABLE_SIZE || Bit_Size > MAX_TABLE_SIZE);
	
	Populate_Tables(Table_Size);

	
	Hit_Total = Test_List(Bit_Size, All_Taken, Table_Size);
	printf("\nAll Taken:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size-((Table_Size + Hit_Total) / 2));
	Hit_Total = Test_List(Bit_Size, None_Taken, Table_Size);
	printf("\nNone Taken:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
	Hit_Total = Test_List(Bit_Size, Alternating, Table_Size);
	printf("\nAlternating:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));

	printf("\nPress enter to continue ...\n");
	getchar();

	return 0;

}