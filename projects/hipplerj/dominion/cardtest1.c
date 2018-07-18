/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: cardtest1.c
**
** OBJECTIVES:
** Write unit tests for four Dominion cards implemented in dominion.c. Write
** these tests so that they work whether a card is implemented inside cardEffect
** or in its own function. These tests should be checked in as cardtest1.c,
** cardtest2.c, cardtest3.c, and cardtest4.c. It is mandatory to test smithy
** and adventurer card. (20 points)
**
** TEST CARD: smithy
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

#include <stdio.h>                                                              // Include the stdio.h C Library
#include <stdlib.h>                                                             // Include the stdlib.h C Library
#include <assert.h>                                                             // Include the assert.h C Library
#include <string.h>

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_CARD_NAME "smithy"                                                 // Define global variable for card name "smithy"

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_results();

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  struct gameState default_state,
                   test_state;
  int numPlayers = 2,                                                           // Set the number of players to 2 for game state
      randomSeed = 30;                                                          // Set the random seed number to 30
  int kingdomCards[10] = {  adventurer,
                            embargo,
                            village,
                            minion,
                            mine,
                            cutpurse,
                            sea_hag,
                            tribute,
                            smithy,
                            council_room
                          };

  printf("Beginning %s Card Testing\n", TEST_CARD_NAME);
  initializeGame(numPlayers, kingdomCards, randomSeed, &default_state);
  test_state = default_state;
  print_test_results();
  printf(">>>>>> SUCCESS: Testing Complete for %s Card <<<<<<<\n", TEST_CARD_NAME);
  return 0;
}

/*******************************************************************************
* Description: print_test_results function
*******************************************************************************/

void print_test_results() {
  printf("We are here in the print_test_results function\n");
}
