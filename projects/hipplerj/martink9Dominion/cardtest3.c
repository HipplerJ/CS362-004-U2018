/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 3
** Due: Sunday, June 22, 2018
**
** Filename: cardtest3.c
**
** OBJECTIVES:
** Write unit tests for four Dominion cards implemented in dominion.c. Write these tests so that they
** work whether a card is implemented inside cardEffect or in its own function. These tests should be
** checked in as cardtest1.c, cardtest2.c, cardtest3.c, and cardtest4.c. It is mandatory to test smithy and
** adventurer card. (20 points)
**
** TEST CARD: baron
** +1 Buy
** You may discard an Estate for +4 Gold. If you don't, gain an estate
** Choice 0: Gain Estate
** Choice 1: Discard Estate for +4 Gold
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
** INITIALIZE GAME FUNCTION
** int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
** 		   struct gameState *state);
**
** Responsible for initializing all supplies, and shuffling deck and
** drawing starting hands for all players.  Check that 10 cards selected
** are in fact (different) kingdom cards, and that numPlayers is valid.
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

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_CARD_NAME "baron"                                                  // Define global variable for card name "baron"
#define TEST_FILE_NAME "cardtest3.c"                                            // Define global variable for the file name used for testing
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
void player_hand_size_test(struct gameState, struct gameState, int);
void player_deck_size_test(struct gameState, struct gameState, int);
void opponent_hand_size_test(struct gameState, struct gameState, int);
void opponent_deck_size_test(struct gameState, struct gameState, int);
void played_card_test(struct gameState, struct gameState, int);
void discard_test(struct gameState, struct gameState, int);
void kingdom_card_test(struct gameState, struct gameState, int*, int);
void victory_card_test(struct gameState, struct gameState, int*, int);
void teasure_card_test(struct gameState, struct gameState, int);
void num_buy_test(struct gameState, struct gameState, int);

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  struct gameState def_state,                                                   // Initialize a game state structure for default game values
                   test_state_c0,                                               // Initialize a game state structure for testing values
                   test_state_c1;                                               // Initialize a game state structure for testing values
  int numPlayers = 2,                                                           // Initialize an integer variable for the number of players as 2
      randomSeed = 1000,                                                        // Initialize an integer variable for random seed numbers
      // choice1 = 0,
      choice2 = 0,
      choice3 = 0,
      bonus = 0,
      handPos = 0;
  int kingdomCards[10] = {
                           adventurer, embargo, village, minion, mine,
                           cutpurse, sea_hag, tribute, smithy, council_room
                         };
  int victoryCards[3] = {
                          estate, duchy, province
                        };
  print_test_details();
  initializeGame(numPlayers, kingdomCards, randomSeed, &def_state);
  // Setup Test suite for Baron with Choice 0 option
  printf("==> Baron - Choice 0\n");
  memcpy(&test_state_c0, &def_state, sizeof(struct gameState));
  cardEffect(baron, 0, choice2, choice3, &test_state_c0, handPos, &bonus);      // Setup test instance for choice 0 on baron
  player_hand_size_test(test_state_c0, def_state, 0);
  player_deck_size_test(test_state_c0, def_state, 0);
  opponent_hand_size_test(test_state_c0, def_state, 0);
  played_card_test(test_state_c0, def_state, 0);
  discard_test(test_state_c0, def_state, 0);
  kingdom_card_test(test_state_c0, def_state, kingdomCards, 0);
  victory_card_test(test_state_c0, def_state, victoryCards, 0);
  teasure_card_test(test_state_c0, def_state, 0);
  num_buy_test(test_state_c0, def_state, 0);
  printf("******************************\n");
  // Setup Test suite for Baron with Choice 1 option
  printf("==> Baron - Choice 1\n");
  memcpy(&test_state_c1, &def_state, sizeof(struct gameState));
  cardEffect(baron, 1, choice2, choice3, &test_state_c1, handPos, &bonus);      // Setup test instance for choice 1 on baron
  player_hand_size_test(test_state_c1, def_state, 1);
  player_deck_size_test(test_state_c1, def_state, 1);
  opponent_deck_size_test(test_state_c1, def_state, 1);
  played_card_test(test_state_c1, def_state, 1);
  discard_test(test_state_c1, def_state, 1);
  kingdom_card_test(test_state_c1, def_state, kingdomCards, 1);
  victory_card_test(test_state_c1, def_state, victoryCards, 1);
  teasure_card_test(test_state_c1, def_state, 1);
  num_buy_test(test_state_c1, def_state, 1);

  printf("\n\n");
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
*******************************************************************************/

void print_test_details() {
  printf("---------- CARD TEST: %s ----------\n", TEST_CARD_NAME);              // Output the name of the card being tested (baron)
  printf("==> TEST FILE: %s\n", TEST_FILE_NAME);                                // Output the name of the file used for testing
  printf("==> This Test Suite Involves Two Test for Both Available Choices\n");
}

/*******************************************************************************
* Description: player_hand_size_test function
*******************************************************************************/

void player_hand_size_test(struct gameState test, struct gameState def, int choice) {
  int draw_cards = 0,
      discard = 0,
      def_value = 0;
  if (choice == 0){
    draw_cards = 1;
    discard = 1;
  } else {
    draw_cards = 0;
    discard = 1;
  }
  def_value = (def.handCount[0] + draw_cards - discard);
  printf("==> TEST 1: Testing Player Hand Size (Choice %d)\n", choice);
  if (choice == 0) {
    printf("==> Estate Card Gained.  Discard Baron Card\n");
  } else {
    printf("==> Estate discarded for Gold.  Dicard %d Estate Card and Baron.\n", discard);
  }
  printf("Received Hand Size: %d\n", test.handCount[0]);
  printf("Expected Hand Size: %d\n", def_value);
  if(def_value != test.handCount[0]){
    printf("[%sFAILED%s] Received Hand Size Value (%d Cards) Incorrect\n", KRED, KNRM, test.handCount[0]);
  } else {
    printf("[%sPASSED%s] Received and Expected Hand Size Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: player_deck_size_test function
*******************************************************************************/

void player_deck_size_test(struct gameState test, struct gameState def, int choice) {
  printf("==> TEST 2: Testing Player Deck Size\n");
  printf("==> Deck Size should be remain unchanged\n");
  printf("Received Deck Size: %d\n", test.deckCount[0]);
  printf("Expected Deck Size: %d\n", def.deckCount[0]);
  if(def.deckCount[0] != test.deckCount[0]){
    printf("[%sFAILED%s] Received Deck Value (%d Cards) Incorrect\n", KRED, KNRM, test.deckCount[0]);
  } else {
    printf("[%sPASSED%s] Received and Expected Deck Size Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: opponent_hand_size_test function
*******************************************************************************/

void opponent_hand_size_test(struct gameState test, struct gameState def, int choice) {
  printf("==> TEST 3: Testing Opponent Hand Size\n");
  printf("==> Opponent Hand Size should remain unchanged (5 Cards)\n");
  printf("Received Opponent Hand Size: %d\n", test.handCount[1]);
  printf("Expected Opponent Hand Size: %d\n", def.handCount[1]);
  if(def.handCount[1] != test.handCount[1]){
    printf("[%sFAILED%s] Received Opponent Hand Size Value (%d Cards) Incorrect\n", KRED, KNRM, test.handCount[1]);
  } else {
    printf("[%sPASSED%s] Received and Expected Opponent Hand Size Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: opponent_deck_size_test function
*******************************************************************************/

void opponent_deck_size_test(struct gameState test, struct gameState def, int choice) {
  printf("==> TEST 4: Testing Opponent Deck Size\n");
  printf("==> Opponent Deck Size should remain unchanged (10 Cards)\n");
  printf("Received Opponent Deck Size: %d\n", test.deckCount[1]);
  printf("Expected Opponent Deck Size: %d\n", def.deckCount[1]);
  if(def.deckCount[1] != test.deckCount[1]){
    printf("[%sFAILED%s] Received Opponent Deck Size Value (%d Cards) Incorrect\n", KRED, KNRM, test.deckCount[1]);
  } else {
    printf("[%sPASSED%s] Received and Expected Opponent Deck Size Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: played_card_test function
*******************************************************************************/

void played_card_test(struct gameState test, struct gameState def, int choice) {
  int played = 1,
      def_value = (def.playedCardCount + played);
  printf("==> TEST 5: Testing Played Card Count\n");
  printf("==> Played Card Count should be increased by 1 Card\n");
  printf("Received Played Card Count Value: %d\n", test.playedCardCount);
  printf("Expected Played Card Count Value: %d\n", def_value);
  if(def_value != test.playedCardCount){
    printf("[%sFAILED%s] Received Played Card Count Value (%d Cards) Incorrect\n", KRED, KNRM, test.playedCardCount);
  } else {
    printf("[%sPASSED%s] Received and Expected Played Card Count Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: discard_test function
*******************************************************************************/

void discard_test(struct gameState test, struct gameState def, int choice) {
  printf("==> TEST 6: Testing Played Discard Count\n");
  printf("==> Discard Count should be increased by at least 1 Card\n");
  printf("Received Discard Count Value: %d\n", test.discardCount[0]);
  printf("Expected Discard Count Value: %d\n", def.discardCount[0] + 1);
  if((def.discardCount[0] + 1) > test.discardCount[0]){
    printf("[%sFAILED%s] Received Discard Count Value (%d Cards) Incorrect\n", KRED, KNRM, test.discardCount[0]);
  } else {
    printf("[%sPASSED%s] Received and Expected values match\\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: kingdom_card_test function
*******************************************************************************/

void kingdom_card_test(struct gameState test, struct gameState def, int* kingdomCards, int choice) {
  char* king_names[10] = {
                            "Adventurer", "Embargo", "Village", "Minion", "Mine",
                            "Cutpurse", "Sea Hag", "Tribute", "Smithy", "Council Room"
                          };
  int i = 0;
  printf("==> TEST 7: Testing Supply Card Piles (Kingdom Cards)\n");
  printf("==> Kingdom Supply Card Pile should remain unchanged\n");
  for(i = 0; i < 10; i ++) {
    printf("Received %s Cards: %d\n", king_names[i], test.supplyCount[kingdomCards[i]]);
    printf("Expected %s Cards: %d\n", king_names[i], def.supplyCount[kingdomCards[i]]);
    if(test.supplyCount[kingdomCards[i]] != def.supplyCount[kingdomCards[i]]) {
      printf("[%sFAILED%s] Received Number of %s Cards (%d Cards) Incorrect\n", KRED, KNRM, king_names[i], test.supplyCount[kingdomCards[i]]);
    } else {
      printf("[%sPASSED%s] Received and Expected Number of %s Cards Match\n", KGREEN, KNRM, king_names[i]);
    }
  }
}

/*******************************************************************************
* Description: victory_card_test function
*******************************************************************************/

void victory_card_test(struct gameState test, struct gameState def, int* victoryCards, int choice) {
  char* vict_names[10] = {
                            "Estate", "Duchy", "Province"
                          };
  int i = 0,
      draw = 0;
  if (choice == 0) {
    draw = 1;
  }
  printf("==> TEST 8: Testing Supply Card Piles (Victory Cards)\n");
  printf("==> Estate Value should reduce by one.\n");
  printf("==> All other Victory Supply Card Piles should remain unchanged\n");
  for(i = 0; i < 3; i ++) {
    if(i == (estate - 1)){
      printf("Received %s Cards: %d\n", vict_names[i], test.supplyCount[victoryCards[i]]);
      printf("Expected %s Cards: %d\n", vict_names[i], def.supplyCount[victoryCards[i]] - draw);
      if(test.supplyCount[victoryCards[i]] != def.supplyCount[victoryCards[i]] - draw) {
        printf("[%sFAILED%s] Received Number of %s Cards (%d Cards) Incorrect\n", KRED, KNRM, vict_names[i], test.supplyCount[victoryCards[i]]);
      } else {
        printf("[%sPASSED%s] Received and Expected Number of %s Cards Match\n", KGREEN, KNRM, vict_names[i]);
      }
    } else {
      printf("Received %s Cards: %d\n", vict_names[i], test.supplyCount[victoryCards[i]]);
      printf("Expected %s Cards: %d\n", vict_names[i], def.supplyCount[victoryCards[i]]);
      if(test.supplyCount[victoryCards[i]] != def.supplyCount[victoryCards[i]]) {
        printf("[%sFAILED%s] Received Number of %s Cards (%d Cards) Incorrect\n", KRED, KNRM, vict_names[i], test.supplyCount[victoryCards[i]]);
      } else {
        printf("[%sPASSED%s] Received and Expected Number of %s Cards Match\n", KGREEN, KNRM, vict_names[i]);
      }
    }
  }
}

/*******************************************************************************
* Description: teasure_card_test function
*******************************************************************************/

void teasure_card_test(struct gameState test, struct gameState def, int choice) {
  int coins = 0,
      def_value =0;
  if(choice == 1){
    coins = 4;
  }
  def_value = def.coins + coins;
  printf("==> TEST 9: Testing Number of Coins\n");
  printf("==> Number of coins should increase to 6 (4 + 2 = 6)\n");
  printf("Received Coin Count Value: %d\n", test.coins);
  printf("Starting Coin Count Value: %d\n", def_value);
  if(def_value != test.coins){
    printf("[%sFAILED%s] Received Coin Count Value (%d Cards) Incorrect\n", KRED, KNRM, test.coins);
  } else {
    printf("[%sPASSED%s] Received and Expected Coin Count Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: num_buy_test function
*******************************************************************************/

void num_buy_test(struct gameState test, struct gameState def, int choice) {
  int buys = 1,
      def_value = def.numBuys + buys;
  printf("==> TEST 10: Testing Number of Buys (Choice %d)\n", choice);
  printf("==> Number of Buys should increase to 2 (1 + 1 = 2)\n");
  printf("Received Buy Count Value: %d\n", test.numBuys);
  printf("Starting Buy Count Value: %d\n", def_value);
  if(def_value != test.numBuys){
    printf("[%sFAILED%s] Received number of Buys (%d Buys) Incorrect\n", KRED, KNRM, test.numBuys);
  } else {
    printf("[%sPASSED%s] Received and Expected Buy Values Match\n", KGREEN, KNRM);
  }
}
