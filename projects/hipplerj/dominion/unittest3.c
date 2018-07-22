/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: unittest3.c
**
** Function Test: discardCard
** int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)

**
** OBJECTIVES:
** The primary goal of this assignment is to learn how to create unit tests.
** Write unit tests for four functions (not card implementations, and not
** cardEffect) in dominion.c “the refactored code you created for assignment-2”.
** Check these tests in as unittest1.c,unittest2.c, unittest3.c, and
** unittest4.c. At least two of these functions should be more than 5 lines of
** code. (20 points)
*******************************************************************************/

/*******************************************************************************
** IMPORTED HEADER FILES
*******************************************************************************/

#include "dominion.h"                                                           // Include the dominion.h header file
#include "dominion_helpers.h"                                                   // Include the dominion_helpers.h header file
#include "rngs.h"                                                               // Include the rngs.h header file

/*******************************************************************************
** PREPROCESSOR DIRECTIVES
*******************************************************************************/

#include <stdio.h>                                                              // Include the stdio.h C Library (necessary for I/O)
#include <stdlib.h>                                                             // Include the stdlib.h C Library (necessary for standard C functions)
#include <string.h>                                                             // Include the string.h C Library (necessary for memcpy)
#include <stdbool.h>                                                            // Include the stdbool.h C Library (necessary for booleans)

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_FUNC_NAME "discardCard"
#define TEST_FILE_NAME "unittest3.c"
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  struct gameState game;                                                        // Initialize a game state structure for default game values
  int numPlayers = 2,                                                           // Initialize an integer variable for the number of players as 2
      randomSeed = 1000;                                                        // Initialize an integer variable for random seed numbers
  int kingdomCards[10] = {
                           adventurer, embargo, village, minion, mine,
                           cutpurse, sea_hag, tribute, smithy, council_room
                         };
  print_test_details();
  initializeGame(numPlayers, kingdomCards, randomSeed, &game);
  printf("\n\n");
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
*******************************************************************************/

void print_test_details() {
  printf("---------- FUNTION TEST: %s ----------\n", TEST_FUNC_NAME);           // Output the name of the card being tested (smithy)
  printf("==> TEST FILE: %s\n", TEST_FILE_NAME);                                // Output the name of the file used for testing
}

void check_trash(struct gameState game) {
  int trashFlag = 0;

}
