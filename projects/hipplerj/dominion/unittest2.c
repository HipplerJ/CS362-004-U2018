/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: unittest2.c
**
** Function Test: shuffle
** int shuffle(int player, struct gameState *state)
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

#define TEST_FUNC_NAME "shuffle"
#define TEST_FILE_NAME "unittest2.c"
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
void deck_count_zero(struct gameState);
void deck_count_full(struct gameState);
void test_deck_size(struct gameState);
void test_shuffle(struct gameState);
void print_test_results(int, int);
void print_size_shuffle(int, int);
void print_shuffle_results(int*, int*);

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
  deck_count_zero(game);
  deck_count_full(game);
  test_deck_size(game);
  test_shuffle(game);
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
* Description: deck_count_zero function
*******************************************************************************/

void deck_count_zero(struct gameState game) {
  int i = 0;
  printf("==> TEST 1: Testing if Shuffle FAILS When Player Decks are Empty\n");
  printf("==> Player Decks set to ZERO. Shuffle Should FAIL\n");
  for(i = 0; i < game.numPlayers; i ++) {
    printf("Testing Player %d Deck Shuffle\n", i + 1);
    game.deckCount[i] = 0;
    print_test_results(shuffle(i, &game), -1);
  }
}

/*******************************************************************************
* Description: deck_count_full function
*******************************************************************************/

void deck_count_full(struct gameState game) {
  int i = 0;
  printf("==> TEST 2: Testing if Shuffle PASSES When Player Decks are FULL\n");
  printf("==> Player Decks set to TEN. Shuffle Should PASS\n");
  for(i = 0; i < game.numPlayers; i ++) {
    printf("Testing Player %d Deck Shuffle\n", i + 1);
    game.deckCount[i] = 10;
    print_test_results(shuffle(i, &game), 0);
  }
}

/*******************************************************************************
* Description: deck_count_full function
*******************************************************************************/

void test_deck_size(struct gameState game) {
  int i = 0;
  int before = 10;
  printf("==> TEST 3: Testing Player Deck Size Before and After Shuffle\n");
  for(i = 0; i < game.numPlayers; i ++) {
    game.deckCount[i] = before;
    printf("Testing Player %d Deck Size\n", i + 1);
    printf("Size Before Shuffle: %d\n", game.deckCount[i]);
    shuffle(i, &game);
    printf("Size After Shuffle: %d\n", game.deckCount[i]);
    print_size_shuffle(before, game.deckCount[i]);
  }
}

/*******************************************************************************
* Description: print_size_shuffle function
*******************************************************************************/

void test_shuffle(struct gameState game) {
  int i = 0;
  int j = 0;
  int deck_order[10];
  printf("==> TEST 4: Testing that Deck is different after shuffle\n");
  for (i = 0; i < game.numPlayers; i ++){
    printf("Testing Player %d Deck Order\n", i + 1);
    for(j = 0; j < 10; j ++){
      deck_order[j] = game.deck[i][j];
    }
    shuffle(i, &game);
    print_shuffle_results(deck_order, game.deck[i]);
  }
}

/*******************************************************************************
* Description: print_test_results function
*******************************************************************************/

void print_test_results(int func_return, int status) {
  if(status == -1) {
    if(func_return == status){
      printf("[%sPASSED%s] Shuffle Should Fail. Player Decks are Empty\n", KGREEN, KNRM);
    } else {
      printf("[%sFAILED%s] Shuffle Should Fail. Player Decks are Empty\n", KRED, KNRM);
    }
  } else {
    if(func_return == status){
      printf("[%sPASSED%s] Shuffle Should Pass. Player Decks are Full\n", KGREEN, KNRM);
    } else {
      printf("[%sFAILED%s] Shuffle Should Pass. Player Decks are Full\n", KRED, KNRM);
    }
  }
}

/*******************************************************************************
* Description: print_size_shuffle function
*******************************************************************************/

void print_size_shuffle(int before, int after) {
  if(before == after) {
    printf("[%sPASSED%s] Deck Size remained unchanged during shuffle\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Deck Size Changed during Shuffle\n", KRED, KNRM);
  }
}

/*******************************************************************************
* Description: print_shuffle_results function
*******************************************************************************/

void print_shuffle_results(int* pre, int* post) {
  int i = 0;
  bool same = true;
  for (i = 0; i < 10; i ++) {
    if (pre[i] == post[i]) {
      same = true;
    } else {
      same = false;
      break;
    }
  }
  if(same == false) {
    printf("[%sPASSED%s] Deck was shuffled\n", KGREEN, KNRM);
  } else {
    printf("[%sFAILED%s] Deck was NOT shuffled\n", KRED, KNRM);
  }
}
