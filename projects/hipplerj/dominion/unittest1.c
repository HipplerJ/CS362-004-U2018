/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: unittest1.c
**
** Function Test: isGameOver
** int isGameOver(struct gameState *state)
** The game ends at the end of any player's turn in which at least one of the
** following is true:
** - The Province Supply pile is empty (or the Colony Supply pile is empty, in a
**   game with the Colony card from the Prosperity expansion)
** - Any three Supply piles are empty. (Any four piles when playing with five or
**   six players.) This includes all the Supply piles, not just the 10 Kingdom
**   card piles that are selected for each game. So, for instance, if the Estate
**   pile, the Curse pile, and one of the Kingdom card piles is empty, the game
**   ends.
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

#define TEST_FUNC_NAME "isGameOver"
#define TEST_FILE_NAME "unittest1.c"
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
void test_provice_pile(struct gameState);
void all_supplies_empty(struct gameState);
void all_supplies_full(struct gameState);
void print_test_results(int, bool);

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
  test_provice_pile(game);
  all_supplies_empty(game);
  all_supplies_full(game);
  printf("\n\n");
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
*******************************************************************************/

void print_test_details() {
  printf("---------- FUNTION TEST: %s ----------\n", TEST_FUNC_NAME);              // Output the name of the card being tested (smithy)
  printf("==> TEST FILE: %s\n", TEST_FILE_NAME);                                // Output the name of the file used for testing
}

/*******************************************************************************
* Description: print_test_details function
* Test if the game ends if the Province Supply is empty.
*******************************************************************************/

void test_provice_pile(struct gameState game) {\
  bool over = true;
  game.supplyCount[province] = 0;
  printf("==> TEST 1: Testing if Game Ends when Province Supply is empty\n");
  printf("==> Province Card Set to ZERO. Game Should End\n");
  print_test_results(isGameOver(&game), over);
  game.supplyCount[province] = 1;
  over = false;
  printf("==> TEST 2: Testing if Game Ends when Province Supply is NOT empty\n");
  printf("==> Province Card Set to ONE. Game Should NOT End\n");
  print_test_results(isGameOver(&game), over);
}

/*******************************************************************************
* Description: all_supplies_empty function
*******************************************************************************/

void all_supplies_empty(struct gameState game) {
  int i = 0;
  bool over = true;
  printf("==> TEST 3: Testing if Game Ends when ALL Supply Piles are empty\n");
  printf("==> All Supply Piles set to ZERO. Game Should End\n");
  for (i = 0; i < 25; i ++) {
    game.supplyCount[i] = 0;
  }
  print_test_results(isGameOver(&game), over);
}

/*******************************************************************************
* Description: all_supplies_full function
*******************************************************************************/

void all_supplies_full(struct gameState game) {
  int i = 0;
  bool over = false;
  printf("==> TEST 4: Testing if Game Ends when ALL Supply Piles are empty\n");
  printf("==> All Supply Piles set to ONE. Game Should NOT End\n");
  for (i = 0; i < 25; i ++) {
    game.supplyCount[i] = 1;
  }
  print_test_results(isGameOver(&game), over);
}

/*******************************************************************************
* Description: print_test_results function
*******************************************************************************/

void print_test_results(int func_return, bool over) {
  if(over == true) {
    if(func_return == over){
      printf("[%sPASSED%s] Game HAS Ended\n", KGREEN, KNRM);
    } else {
      printf("[%sFAILED%s] Game HAS NOT Ended\n", KRED, KNRM);
    }
  } else {
    if(func_return == over){
      printf("[%sPASSED%s] Game HAS NOT Ended\n", KGREEN, KNRM);
    } else {
      printf("[%sFAILED%s] Game HAS Ended\n", KRED, KNRM);
    }
  }
}
