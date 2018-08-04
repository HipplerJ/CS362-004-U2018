/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 4
** Due: Sunday, August 05, 2018
**
** Filename: randomtestadventurer.c
**
** TEST CARD: adventurer
** Reveal cards from your deck until you reveal 2 Treasure cards.  Put those
** Treasure cards into your hand and discard the other revealed cards.
**
** GAME STATE STRUCTURE
** struct gameState {
**   int numPlayers; //number of players
**   int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
**   int embargoTokens[treasure_map+1];
**   int outpostPlayed;
**   int outpostTurn;
**   int whoseTurn;
**   int phase;
**   int numActions; // Starts at 1 each turn
**   int coins; // Use as you see fit!
**   int numBuys; // Starts at 1 each turn
**   int hand[MAX_PLAYERS][MAX_HAND];
**   int handCount[MAX_PLAYERS];
**   int deck[MAX_PLAYERS][MAX_DECK];
**   int deckCount[MAX_PLAYERS];
**   int discard[MAX_PLAYERS][MAX_DECK];
**   int discardCount[MAX_PLAYERS];
**   int playedCards[MAX_DECK];
**   int playedCardCount;
** };
**
** OBJECTIVES:
** Write an automated random test generator for three Dominion cards “use the
** refactored code you created for assignment-2”, one of them being the
** adventurer card, and at least one being a card you wrote unit tests for in
** assignment-3. Check these testers in as randomtestcard1.c, randomtestcard2.c,
** and randomtestadventurer.c. (45 Points)
*******************************************************************************/

/*******************************************************************************
** IMPORTED HEADER FILES
*******************************************************************************/

#include "dominion.h"                                                           // Include the dominion.h header file
#include "dominion_helpers.h"                                                   // Include the dominion_helpers.h header file
#include "rngs.h"                                                               // Include the rngs.h header file

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_CARD_NAME "Adventurer"                                             // Define global variable for card name "smithy"
#define TEST_FILE_NAME "randomtestadventurer.c"                                 // Define global variable for the file name used for testing
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** PREPROCESSOR DIRECTIVES
*******************************************************************************/

#include <stdio.h>                                                              // Include the stdio.h C Library (necessary for I/O)
#include <stdlib.h>                                                             // Include the stdlib.h C Library (necessary for standard C functions)
#include <string.h>                                                             // Include the string.h C Library (necessary for memcpy)
#include <time.h>
#include <math.h>
#include <assert.h>

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_header();
void adventurer_rand_test();

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  print_header();
  adventurer_rand_test();
  return 0;
}

/*******************************************************************************
* Description: print_header function
*******************************************************************************/

void print_header(){
  printf("---------- Random Card Test: %s ----------\n", TEST_CARD_NAME);
  printf("==> TEST FILE: %s\n", TEST_FILE_NAME);
}

/*******************************************************************************
* Description: adventurer_rand_test function
*******************************************************************************/

void adventurer_rand_test(){
  printf("In the smithy random test\n");
}
