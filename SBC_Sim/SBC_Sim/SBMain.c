#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

//#define BASIC_TABLES // uncomment to view basic static table results
//#define RANDOM_TABLES // uncomment to view random table results
#define CUSTOM_TABLES // uncomment to enable cutom table functionality

#define MAX_TABLE_SIZE 10000000
#define MIN_TABLE_SIZE 1

#ifdef BASIC_TABLES
int All_Taken[MAX_TABLE_SIZE];
int None_Taken[MAX_TABLE_SIZE];
int Alternating[MAX_TABLE_SIZE];
#endif // BASIC_TABLES

#ifdef RANDOM_TABLES
int Random_One[MAX_TABLE_SIZE];
int Random_Two[MAX_TABLE_SIZE];
#endif // RANDOM_TABLES

#ifdef CUSTOM_TABLES
int Custom_Table[MAX_TABLE_SIZE];
#endif // CUSTOM_TABLES


void Populate_Tables(int Chosen_Table_Size)
{
	int r;
	srand(time(NULL));
	int random = rand();

	/* Populate the tables */
	printf("Populating Tables...\n");
#ifdef BASIC_TABLES
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
#endif // BASIC TABLES
#ifdef RANDOM_TABLES
	for (r = 0; r < Chosen_Table_Size; r++)
	{
		random = rand();
		if (random % 2 == 0)
		{
			Random_One[r] = 1;
		}
		else
		{
			Random_One[r] = 0;
		}
	}

	for (r = 0; r < Chosen_Table_Size; r++)
	{
		random = rand();
		if (random % 2 == 0)
		{
			Random_Two[r] = 1;
		}
		else
		{
			Random_Two[r] = 0;
		}
	}
#endif // RANDOM_TABLES

}

void Populate_Custom_Table(int Chosen_Table_Size, char Pattern[50])
{
	int r;
	for (r = 0; r < Chosen_Table_Size; r++)
	{
		
		if ((Pattern[r % strlen(Pattern)] == 'T') || (Pattern[r % strlen(Pattern)] == 't'))
		{
			Custom_Table[r] = 1;
		}
		else if ((Pattern[r % strlen(Pattern)] == 'N') || (Pattern[r % strlen(Pattern)] == 'n'))
		{
			Custom_Table[r] = 0;
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
	char str[50] = { 0 };
	char* pStr = NULL;
	pStr = (char*)malloc(50);

	char c;

	while (1)
	{

		do
		{
			printf("Choose a size for the Taken / Not Taken tables. \nEnter an integer from %d to : %d: ", MIN_TABLE_SIZE, MAX_TABLE_SIZE);

		} while (((scanf("%d%c", &Table_Size, &c) != 2 || c != '\n') && clean_stdin()) || Table_Size < MIN_TABLE_SIZE || Table_Size > MAX_TABLE_SIZE);


		do
		{
			printf("\nChoose a size for the saturating bit counter. \nEnter an integer from 1 to : 1,000,000 bits: ");

		} while (((scanf("%d%c", &Bit_Size, &c) != 2 || c != '\n') && clean_stdin()) || Bit_Size < MIN_TABLE_SIZE || Bit_Size > MAX_TABLE_SIZE);


#ifdef CUSTOM_TABLES
		printf("\nChoose a pattern for your custom table. \n");
		printf("[Example: TTTNNTN\n");
		printf("please enter up to 48: ");
		scanf("%s", &str);
		Populate_Custom_Table(Table_Size, str);
#endif // CUSTOM_TABLES

		Populate_Tables(Table_Size);

#ifdef BASIC_TABLES
		Hit_Total = Test_List(Bit_Size, All_Taken, Table_Size);
		printf("\nAll Taken:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
		Hit_Total = Test_List(Bit_Size, None_Taken, Table_Size);
		printf("\nNone Taken:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
		Hit_Total = Test_List(Bit_Size, Alternating, Table_Size);
		printf("\nAlternating:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
#endif // BASIC_TABLES
#ifdef RANDOM_TABLES
		Hit_Total = Test_List(Bit_Size, Random_One, Table_Size);
		printf("\nRandom version one:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
		Hit_Total = Test_List(Bit_Size, Random_Two, Table_Size);
		printf("\nRandom version two:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
#endif // RANDOM_TABLES
#ifdef CUSTOM_TABLES
		Hit_Total = Test_List(Bit_Size, Custom_Table, Table_Size);
		printf("\nCustom:\nHits = %d\nMisses = %d\n", (Table_Size + Hit_Total) / 2, Table_Size - ((Table_Size + Hit_Total) / 2));
#endif // CUSTOM_TABLES
		printf("\nPress enter to start over ...\n");
		getchar();

		printf("---------------------------------------------\n\n");
	}
}