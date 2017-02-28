#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Yes, global variables are gross, this is just being used to avoid making a header file for the struct
typedef struct card
{
	char type;		// ex: r = red, b = blue, y = yellow, g = green, x = black
	int special; 	// Define whether card is normal or not, so set to 0 or 1
	int value;		// ex: 1, 2, 3, etc. 
}card;

void shuffle(card *deck);	// Function prototype for shuffle

int main(void)
{
	int i = 0;
	card *deck = malloc(sizeof(card) * 108);   // Create deck of 108 cards
	shuffle(deck);							   // Call shuffle function

	for(i = 0; i < 108; i++)
	{
		printf("Card %d color: %c\n", i, deck[i].type);		// Printout all cards post-shuffle
	}

	return 0;
}

void shuffle(card *deck)
{
	int pick, seed, i = 0, deckCount = 108;
	int colorCount[5] = {25, 25, 25, 25, 8};   // Colors being: red, yellow, green, blue, black

	srand(time(NULL));						   // Seed random number-generator with system time

	while(deckCount > 0)
	{
		pick = rand() % 5;
		card c;

		switch(pick)
		{
			case 0:
				c.type = 'r';
				deck[i] = c;
				break;
			case 1:
				c.type = 'g';
				deck[i] = c;
				break;
			case 2:
				c.type = 'y';
				deck[i] = c;
				break;
			case 3:
				c.type = 'b';
				deck[i] = c;
				break;
			case 4:
				c.type = 'x';
				deck[i] = c;
				break;
			default:				// Something went wrong if this is reached
				c.type = '_';
				deck[i] = c;
				break;
		}

		i++;
		deckCount--;
	}
}
