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
void check_trash(struct gameState);
void check_played_card_count(struct gameState);
void check_played_card_array(struct gameState);
void check_player_hand_count(struct gameState);
void check_played_hand_slot(struct gameState);

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
  check_trash(game);
  check_player_hand_count(game);
  check_played_hand_slot(game);
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
* Description: check_trash function
*******************************************************************************/

void check_trash(struct gameState game) {
  int trashFlag = 0;
  printf("==> TEST 1: Testing Trash Flag Functionality\n");
  printf("==> Played Card Count Should Increase\n");
  printf("==> Played Cards Array should have value in first element\n");
  discardCard(0, 0, &game, trashFlag);
  check_played_card_count(game);
  check_played_card_array(game);
}

/*******************************************************************************
* Description: check_played_card_count function
*******************************************************************************/

void check_played_card_count(struct gameState game){
  if(game.playedCardCount == 1) {
    printf("[%sPASSED%s] Played Card Count was Increased\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Played Card Count was NOT Increased\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: check_played_card_array function
*******************************************************************************/

void check_played_card_array(struct gameState game) {
  if(game.playedCards[0] == game.hand[0][0]){
    printf("[%sPASSED%s] Played Card and Card in Player Hand Match\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Played Card and Card in Player Hand DO NOT Match\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: check_player_hand_count function
*******************************************************************************/

void check_player_hand_count(struct gameState game) {
  int pre_discard = game.handCount[0];
  printf("==> TEST 2: Testing Player Hand Size\n");
  printf("==> Player Hand should decrease by one\n");
  discardCard(0, 0, &game, 1);
  if((pre_discard - 1) == game.handCount[0]){
    printf("[%sPASSED%s] Player Hand was reduced\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Player Hand was NOT reduced\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: check_played_hand_slot function
*******************************************************************************/

void check_played_hand_slot(struct gameState game) {
  printf("==> TEST 3: Testing Card is removed from Hand\n");
  printf("==> Discard Slot in Hand should be -1\n");
  discardCard(0, 0, &game, 1);
  if(game.hand[0][0] != -1) {
    printf("[%sPASSED%s] Card Successfully Discarded\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Card NOT Discarded Correctly\n", KRED, KNRM);
  }
}
