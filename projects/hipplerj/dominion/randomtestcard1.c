/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Assignment 4
** Due: Sunday, August 05, 2018
**
** Filename: randomtestcard1.c
**
** OBJECTIVES:
** Write an automated random test generator for three Dominion cards “use the
** refactored code you created for assignment-2”, one of them being the
** adventurer card, and at least one being a card you wrote unit tests for in
** assignment-3. Check these testers in as randomtestcard1.c, randomtestcard2.c,
** and randomtestadventurer.c (45 Points)
**
** TEST CARD: smithy
** Smithy card allows user to draw 3 cards
** +3 Cards
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
#include <time.h>                                                               // Include the string.h C Library (necessary for memcpy)

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_CARD_NAME "Smithy"                                                 // Define global variable for card name "Smithy"
#define TEST_FILE_NAME "randomtestcard1.c"                                      // Define global variable for the file name used for testing
#define MIN_PLAYERS 2
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
void player_hand_size_test(struct gameState, struct gameState);
void player_deck_size_test(struct gameState, struct gameState);
void opponent_hand_size_test(struct gameState, struct gameState);
void opponent_deck_size_test(struct gameState, struct gameState);
void played_card_test(struct gameState, struct gameState);
void discard_test(struct gameState, struct gameState);
void kingdom_card_test(struct gameState, struct gameState, int*);
void victory_card_test(struct gameState, struct gameState, int*);

/*******************************************************************************
* Description: main function
*******************************************************************************/

int main(int argc, char const *argv[]) {
  struct gameState def_state,                                                   // Initialize a game state structure for default game values
                   test_state;                                                  // Initialize a game state structure for testing values
  int numPlayers = 2,                                                           // Initialize an integer variable for the number of players as 2
      randomSeed = 1000,                                                        // Initialize an integer variable for random seed numbers
      choice1 = 0,
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
  memcpy(&test_state, &def_state, sizeof(struct gameState));
  cardEffect(smithy, choice1, choice2, choice3, &test_state, handPos, &bonus);
  player_hand_size_test(test_state, def_state);
  player_deck_size_test(test_state, def_state);
  opponent_hand_size_test(test_state, def_state);
  opponent_deck_size_test(test_state, def_state);
  played_card_test(test_state, def_state);
  discard_test(test_state, def_state);
  kingdom_card_test(test_state, def_state, kingdomCards);
  victory_card_test(test_state, def_state, victoryCards);
  printf("\n\n");
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
* Print the test information to the console.  This includes printing the
* name of the card being test and the name of the file performing the tests.
*******************************************************************************/

void print_test_details() {
  printf("---------- CARD TEST: %s ----------\n", TEST_CARD_NAME);              // Output the name of the card being tested (smithy)
  printf("==> TEST FILE: %s\n", TEST_FILE_NAME);                                // Output the name of the file used for testing
}

/*******************************************************************************
* Description: player_hand_size_test function
* Test to ensure that the player's hand size increases by the appropriate
* number of cards.  Player should draw three cards and then discard 1 (smithy)
* increasing their handsize by a value of two.
*******************************************************************************/

void player_hand_size_test(struct gameState test, struct gameState def) {
  int draw_cards = 3,
      discard = 1,
      def_value = (def.handCount[0] + draw_cards - discard);
  printf("==> TEST 1: Testing Player Hand Size\n");
  printf("==> Draw Three Cards.  Hand Size should be 7 (5 + 3 - 1 = 7 Cards)\n");
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
* Test to ensure that the correct number of cards were removed from the
* player's deck.  Player Deck size should be reduced by three.
*******************************************************************************/

void player_deck_size_test(struct gameState test, struct gameState def) {
  int drawn_cards = 3,
      def_value = (def.deckCount[0] - drawn_cards);
  printf("==> TEST 2: Testing Player Deck Size\n");
  printf("==> Draw Three Cards.  Deck Size should be 2 (5 - 3 = 2 Cards)\n");
  printf("Received Deck Size: %d\n", test.deckCount[0]);
  printf("Expected Deck Size: %d\n", def_value);
  if(def_value != test.deckCount[0]){
    printf("[%sFAILED%s] Received Deck Value (%d Cards) Incorrect\n", KRED, KNRM, test.deckCount[0]);
  } else {
    printf("[%sPASSED%s] Received and Expected Deck Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: opponent_hand_size_test function
* Confirm that the opponent's Hand Size remains unchanged after smithy is
* played.  Hand size should remain at 5 cards.
*******************************************************************************/

void opponent_hand_size_test(struct gameState test, struct gameState def) {
  printf("==> TEST 3: Testing Opponent Hand Size\n");
  printf("==> Opponent Hand Size should remain unchanged (0 Cards)\n");
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
* Confirm that the opponent's Deck Size remains unchanged after smithy is
* played.  Deck Size should remain at 10 cards.
*******************************************************************************/

void opponent_deck_size_test(struct gameState test, struct gameState def) {
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
* Tests the value of the number of cards played to ensure that the game is
* accurately reflecting the smithy card after it's been played.
*******************************************************************************/

void played_card_test(struct gameState test, struct gameState def) {
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
* Tests the value of the player's discard value to ensure that the game is
* taking into consideration that the smithy has been played and then
* discarded.
*******************************************************************************/

void discard_test(struct gameState test, struct gameState def) {
  int discard = 1,
      def_value = (def.discardCount[0] + discard);
  printf("==> TEST 6: Testing Played Discard Count\n");
  printf("==> Discard Count should be increased by 1 Card\n");
  printf("Received Discard Count Value: %d\n", test.discardCount[0]);
  printf("Expected Discard Count Value: %d\n", def_value);
  if(def_value != test.discardCount[0]){
    printf("[%sFAILED%s] Received Discard Count Value (%d Cards) Incorrect\n", KRED, KNRM, test.discardCount[0]);
  } else {
    printf("[%sPASSED%s] Received and Expected Discard Count Values Match\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: kingdom_card_test function
* Test to confirm that the kingdom cards in the supply card piles are not
* affected when playing the smithy card.
*******************************************************************************/

void kingdom_card_test(struct gameState test, struct gameState def, int* kingdomCards) {
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
* Test to confirm that the victory cards in the supply card piles are not
* affected when playing the smithy card.
*******************************************************************************/

void victory_card_test(struct gameState test, struct gameState def, int* victoryCards) {
  char* vict_names[10] = {
                            "Estate", "Duchy", "Province"
                          };
  int i = 0;
  printf("==> TEST 8: Testing Supply Card Piles (Victory Cards)\n");
  printf("==> Victory Supply Card Pile should remain unchanged\n");
  for(i = 0; i < 3; i ++) {
    printf("Received %s Cards: %d\n", vict_names[i], test.supplyCount[victoryCards[i]]);
    printf("Expected %s Cards: %d\n", vict_names[i], def.supplyCount[victoryCards[i]]);
    if(test.supplyCount[victoryCards[i]] != def.supplyCount[victoryCards[i]]) {
      printf("[%sFAILED%s] Received Number of %s Cards (%d Cards) Incorrect\n", KRED, KNRM, vict_names[i], test.supplyCount[victoryCards[i]]);
    } else {
      printf("[%sPASSED%s] Received and Expected Number of %s Cards Match\n", KGREEN, KNRM, vict_names[i]);
    }
  }
}
