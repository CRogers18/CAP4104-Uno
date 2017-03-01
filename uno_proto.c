#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* PLEASE NOTE: ALL .c FILES ARE COMPILED USING GCC VERSION 4.2.1 
   IF YOU ARE BELOW THIS VERSION OF GCC THE COMPILER MAY FAIL TO COMPILE.
   GCC VERSION CAN BE CHECKED WITH 'gcc -v' IN TERMINAL OR CMD */

/* Global variables suck so this is a temporary 
   fix so I don't have to make a header file */
typedef struct card
{
	char type;		// ex: r = red, b = blue, y = yellow, g = green, x = black
	int special;    // Define whether card is normal or not, so set to 0 or 1
	int value;		// ex: 1, 2, 3, etc. 
}card;

typedef struct stack
{
	card *hand;	// Deck of cards or the stack
	int size;   // Stack size
}stack;

void shuffle(card *deck);	// Deck shuffling function
void push(card c, stack *mainDeck);	// Pushes cards onto the stack 
card pop(card *mainDeck);  // Removes cards from the stack, returns the card removed

int main(void)
{
	int i;
	int colorCount[5] = {0};
	stack *mainDeck = malloc(sizeof(stack));	  // Declare uno main deck
	mainDeck->size = 0;
	mainDeck->hand = malloc(sizeof(card) * 108);   // Create deck of 108 cards

	// Creates empty hand for players 1-4 (will change accordingly w/ requirement list)
	card *hand1 = malloc(sizeof(card) * 8);	   
	card *hand2 = malloc(sizeof(card) * 8);
	card *hand3 = malloc(sizeof(card) * 8);
	card *hand4 = malloc(sizeof(card) * 8);

	shuffle(mainDeck->hand);

	printf("All cards shuffled!\n");

	// Print out the distribution of cards
	for(i = 0; i < 108; i++)
	{
		printf("Card %d color: %c\n", i, mainDeck->hand[i].type);
		switch(mainDeck->hand[i].type)
		{
			case 'r':
				colorCount[0]++;
				break;
			case 'y':
				colorCount[1]++;
				break;
			case 'g':
				colorCount[2]++;
				break;
			case 'b':
				colorCount[3]++;
				break;
			case 'x':
				colorCount[4]++;
				break;
		}
	}

	// Used as a shuffle debug, correct output: 25, 25, 25, 25, 8
	printf("Red: %d, Yellow: %d, Green: %d, Blue: %d, Black: %d\n", 
		   colorCount[0], colorCount[1], colorCount[2], colorCount[3], colorCount[4]);

	return 0;
}

// Unimplemented functions to make
void push(card c, stack *mainDeck);
card pop(card *mainDeck);

/* Issues present in shuffle:

   1) Need a good way of handling pick = color of card with no available
      places to put it in the deck. Ex: all 25 red cards have been placed
      but pick = red, so a new place to put the card is needed. Currently
      just using a '*' to denote these special cases

   2) No way of handling 'special' cards yet. Maybe differentiate
      them in the colorCount array? */

void shuffle(card *deck)
{
	int pick, j, i = 0, deckCount = 108;
	int colorCount[5] = {25, 25, 25, 25, 8};   // Colors being: red, yellow, green, blue, black

	srand(time(NULL));  // This line generates a warning on compile, please ignore.

	while(deckCount > 0)
	{
		card c;	// Make a new blank card each time
		pick = rand() % 5;	// Generate a random value for the blank card

		switch(pick)   // Depending on what is generated, update card info and add it to the deck
		{
			case 0:
				// If we can still place a red card into the deck, do so
				if(colorCount[0] > 0)
				{
					c.type = 'r';
					deck[i] = c;
					colorCount[0]--;
					break;
				}

				// If we cannot, find the next available color that it can be placed in
				if(colorCount[0] == 0)
				{
					for(j = 0; j < 5; j++)
					{
						if(colorCount[j] > 0)
						{	
							c.type = '*';	
							deck[i] = c;
							colorCount[j]--;
							j = 10;			// Breaks the loop without a break statement
						}
					}
				}
				break;
					

			case 1:
				if(colorCount[1] > 0)
				{
					c.type = 'g';
					deck[i] = c;
					colorCount[1]--;
					break;
				}

				if(colorCount[1] == 0)
				{
					for(j = 0; j < 5; j++)
					{
						if(colorCount[j] > 0)
						{
							c.type = '*';
							deck[i] = c;
							colorCount[j]--;
							j = 10;
						}
					}
				}
				break;
				
			case 2:
				if(colorCount[2] > 0)
				{
					c.type = 'y';
					deck[i] = c;
					colorCount[2]--;
					break;
				}

				if(colorCount[2] == 0)
				{
					for(j = 0; j < 5; j++)
					{
						if(colorCount[j] > 0)
						{
							c.type = '*';
							deck[i] = c;
							colorCount[j]--;
							j = 10;
						}
					}
				}
				break;
				
			case 3:
				if(colorCount[3] > 0)
				{
					c.type = 'b';
					deck[i] = c;
					colorCount[3]--;
					break;
				}

				if(colorCount[3] == 0)
				{
					for(j = 0; j < 5; j++)
					{
						if(colorCount[j] > 0)
						{
							c.type = '*';
							deck[i] = c;
							colorCount[j]--;
							j = 10;
						}
					}
				}
				break;

			case 4:
				if(colorCount[4] > 0)
				{
					c.type = 'x';
					deck[i] = c;
					colorCount[4]--;
					break;
				}

				if(colorCount[4] == 0)
				{
					for(j = 0; j < 5; j++)
					{
						if(colorCount[j] > 0)
						{
							c.type = '*';
							deck[i] = c;
							colorCount[j]--;
							j = 10;
						}
					}
				}
				break;

			default:
				c.type = '_';
				deck[i] = c;
				break;
		}

		i++;
		deckCount--;
	}
}