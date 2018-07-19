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

void print_test_details();
void player_hand_size_test(struct gameState, struct gameState);
void player_desk_test();
void player_state_test();
void game_state_test();
void print_test_results();

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  struct gameState def_state,
                   test_state;
  int numPlayers = 2,                                                           // Set the number of players to 2 for game state
      randomSeed = 1000,                                                        // Set the random seed number to 1000
      choice1 = 0,
      choice2 = 0,
      choice3 = 0,
      bonus = 0,
      handPos = 0;
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
  print_test_details();                                                         // Call Function that just prints the name of the car being tested and the file
  initializeGame(numPlayers, kingdomCards, randomSeed, &def_state);             // Initialize the Dominion Game for testing
  memcpy(&test_state, &def_state, sizeof(struct gameState));                    // Copy the default game state to the test game state variable
  cardEffect(smithy, choice1, choice2, choice3, &test_state, handPos, &bonus);
  player_hand_size_test(test_state, def_state);
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
*******************************************************************************/

void print_test_details() {
  printf("Card Test: %s\n", TEST_CARD_NAME);
  printf("Test File: cardtest1.c\n");
}

/*******************************************************************************
* Description: player_hand_size_test function
*******************************************************************************/

void player_hand_size_test(struct gameState test, struct gameState def) {
  int draw_cards = 3,
      discard = 1,
      def_value = (def.handCount[0] + draw_cards - discard);
  printf("==> Testing Player Handsize after Smithy\n");
  printf("Test Handcount: %d\n", test.handCount[0]);
  printf("Default Handcount: %d\n", def_value);
  if(def_value != test.handCount[0]){
    printf("[FAILED]  Test and Default Handvalues do not match\n");
  } else {
    printf("[PASSED]  Test and Default Handvalues are equivalent\n");
  }
}
