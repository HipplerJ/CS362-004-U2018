/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: unittest4.c
**
** Function Test: gainCard
** int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
**
** added card for [whoseTurn] current player:
** toFlag = 0 : add to discard
** toFlag = 1 : add to deck
** toFlag = 2 : add to hand
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

#define TEST_FUNC_NAME "gainCard"
#define TEST_FILE_NAME "unittest4.c"
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
void supply_pile_empty(struct gameState);
void add_discard_flag(struct gameState);
void add_deck_flag(struct gameState);
void add_hand_flag(struct gameState);
void check_supply_count_decrease(struct gameState);

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
  supply_pile_empty(game);
  add_discard_flag(game);
  add_deck_flag(game);
  add_hand_flag(game);
  check_supply_count_decrease(game);
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

/*******************************************************************************
* Description: supply_pile_empty function
*******************************************************************************/

void supply_pile_empty(struct gameState game){
  int status = 0;
  printf("==> TEST 1: Testing When Supply is Empty\n");
  printf("==> supplyCount[0] has been set to ZERO\n");
  game.supplyCount[0] = 0;
  status = gainCard(0, &game, 1, 0);
  if(status == -1) {
    printf("[%sPASSED%s] Supply is empty.  No Card should be gained\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Supply is Empty.  No Card should be gained\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: add_discard_flag function
*******************************************************************************/

void add_discard_flag(struct gameState game) {
  int pre = game.discardCount[0];
  printf("==> TEST 2: Testing toFlag 0 (Add Card to Discard)\n");
  printf("==> Player Discard Should Increase by One\n");
  gainCard(0, &game, 0, 0);
  if((pre + 1) == game.discardCount[0]){
    printf("[%sPASSED%s] Player Discard Increased\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Player Discard DID NOT Increase\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: add_deck_flag function
*******************************************************************************/

void add_deck_flag(struct gameState game) {
  int pre = game.deckCount[0];
  printf("==> TEST 3: Testing toFlag 1 (Add Card to Deck)\n");
  printf("==> Player Deck Should Increase by One\n");
  gainCard(0, &game, 1, 0);
  if((pre + 1) == game.deckCount[0]){
    printf("[%sPASSED%s] Player Deck Increased\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Player Deck DID NOT Increase\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: add_hand_flag function
*******************************************************************************/

void add_hand_flag(struct gameState game) {
  int pre = game.handCount[0];
  printf("==> TEST 4: Testing toFlag 2 (Add Card to Hand)\n");
  printf("==> Player Hand Should Increase by One\n");
  gainCard(0, &game, 2, 0);
  if((pre + 1) == game.handCount[0]){
    printf("[%sPASSED%s] Player Hand Increased\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Player Hand DID NOT Increase\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: check_supply_count_decrease function
*******************************************************************************/

void check_supply_count_decrease(struct gameState game) {
  int pre = game.supplyCount[0];
  printf("==> TEST 5: Testing that Supply Count is Decreased\n");
  printf("==> Supply Count for Gained Card should be reduced by ONE\n");
  gainCard(0, &game, 1, 0);
  if((pre - 1) == game.supplyCount[0]) {
    printf("[%sPASSED%s] Supply Count Increased\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Supply Count DID NOT Decrease\n", KRED, KNRM);
  }
}
