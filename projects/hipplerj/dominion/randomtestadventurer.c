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
** OBJECTIVES:
** Write an automated random test generator for three Dominion cards “use the
** refactored code you created for assignment-2”, one of them being the
** adventurer card, and at least one being a card you wrote unit tests for in
** assignment-3. Check these testers in as randomtestcard1.c, randomtestcard2.c,
** and randomtestadventurer.c (45 Points)
**
** TEST CARD: Adventurer
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
#include <time.h>                                                               // Include the time.h C Library (necessary for seeding random time)

/*******************************************************************************
** DEFINE GLOBAL VARIABLES
*******************************************************************************/

#define TEST_CARD_NAME "Adventurer"                                             // Define global variable for card name "Adventurer"
#define TEST_FILE_NAME "randomtestadventurer.c"                                 // Define global variable for the file name used for testing
#define MIN_PLAYERS 2
#define KNRM "\x1B[0m"                                                          // Define global variable to change console color to Normal
#define KRED "\x1B[31m"                                                         // Define global variable to change the console color to Red (Failed Tests)
#define KGREEN "\x1B[32m"                                                       // Define global variable to change the console color to Green (Passed Tests)

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

void print_test_details();
int test_initialize_game(int, int*, int, struct gameState*);
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
  int num_tests = 5000;                                                         // Initialize a variable for the number of times testing will be performed (currently 5,000)
  int status = -5;                                                              // Initialize a variable for the status of initializing the game (set to bogus value)
  srand(time(NULL));                                                            // Use the system clock to initialize random values
  struct gameState def_state,                                                   // Initialize a game state structure for default game values
                   test_state;                                                  // Initialize a game state structure for testing values
  int numPlayers = 0,                                                           // Initialize an integer variable for the number of players (random value between 0 and 5)
      randomSeed = (rand() % 1000),                                             // Initialize an integer variable for random seed numbers (Random Seed is randomly generated)
      choice1 = 0,
      choice2 = 0,
      choice3 = 0,
      bonus = 0,
      handPos = 0,
      i = 0;
  int kingdomCards[10] = {
                           adventurer, embargo, village, minion, mine,
                           cutpurse, sea_hag, tribute, smithy, council_room
                         };
  int victoryCards[3] = {
                          estate, duchy, province
                        };
  while(i < num_tests) {
    numPlayers = (rand() % 6);
    print_test_details(i, num_tests);
    status = test_initialize_game(numPlayers, kingdomCards, randomSeed, &def_state);
    if(status == -1) {
      printf("Could not initialize Game.\n");
      printf("Random Value %d for Players is Invalid\n", numPlayers);
      printf("\n\n");
      continue;
    }
    memcpy(&test_state, &def_state, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &test_state, handPos, &bonus);
    player_hand_size_test(test_state, def_state);
    player_deck_size_test(test_state, def_state);
    opponent_hand_size_test(test_state, def_state);
    opponent_deck_size_test(test_state, def_state);
    played_card_test(test_state, def_state);
    discard_test(test_state, def_state);
    kingdom_card_test(test_state, def_state, kingdomCards);
    victory_card_test(test_state, def_state, victoryCards);
    i ++;
    printf("\n\n");
  }
  return 0;
}

/*******************************************************************************
* Description: print_test_details function
* Print the test information to the console.  This includes printing the
* name of the card being test and the name of the file performing the tests.
*******************************************************************************/

void print_test_details(int test_number, int num_tests) {
  printf("---------- RANDOM CARD TEST: %s ----------\n", TEST_CARD_NAME);       // Output the name of the card being tested (smithy)
  printf("TEST FILE: %s\n", TEST_FILE_NAME);                                    // Output the name of the file used for testing
  printf("TEST NUMBER: %d of %d\n", test_number + 1, num_tests);
}

/*******************************************************************************
* Description: test_initialize_game function
*******************************************************************************/

int test_initialize_game(int numPlayers, int* kingdomCards, int randomSeed, struct gameState *def_state) {
  int status = 0;
  int fault = -1;
  printf("TEST #1\n");
  printf("Testing Game Initialization with Random Players\n");
  printf("Randomized Number of Players: %d\n", numPlayers);
  status = initializeGame(numPlayers, kingdomCards, randomSeed, def_state);
  if ((numPlayers > MAX_PLAYERS) || (numPlayers < MIN_PLAYERS)) {
    if(status != fault){
      printf("[%sFAILED%s] Number of Players in incorrect.\nInitializing Game Should Fail and it didn't\n", KRED, KNRM);
    } else {
      printf("[%sPASSED%s] Number of Players in incorrect.\nInitializing Game Failed correctly\n", KGREEN, KNRM);
    }
  } else {
    if(status == fault){
      printf("[%sFAILED%s] Number of Players is correct.\nInitializing Game Should not fail\n", KRED, KNRM);
    } else {
      printf("[%sPASSED%s] Number of Players in correct.\nSuccessfully Initialized Game\n", KGREEN, KNRM);
    }
  }
  return status;
}

/*******************************************************************************
* Description: player_hand_size_test function
*******************************************************************************/

void player_hand_size_test(struct gameState test, struct gameState def) {
  int draw_cards = 2,
      discard = 1,
      def_value = (def.handCount[0] + draw_cards - discard);
  printf("TEST #2\n");
  printf("Testing Player Hand Size with %d Players\n", test.numPlayers);
  printf("==> Draw Two Treasure Cards.  Hand Size should be 6 (5 + 2 - 1 = 6 Cards)\n");
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

void player_deck_size_test(struct gameState test, struct gameState def) {
  printf("TEST #3\n");
  printf("Testing Player Deck Size with %d Players\n", test.numPlayers);
  printf("==> Draw Two Treasure Cards.  Deck Size should be reduced by at least 2\n");
  printf("Received Deck Size: %d\n", test.deckCount[0]);
  printf("Expected Deck Size: %d\n", def.deckCount[0]);
  if((def.deckCount[0] - 2) < test.deckCount[0]){
    printf("[%sFAILED%s] Received Deck Value (%d Cards) Incorrect\n", KRED, KNRM, test.deckCount[0]);
  } else {
    printf("[%sPASSED%s] Received is Equal to Expected or Less\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: opponent_hand_size_test function
*******************************************************************************/

void opponent_hand_size_test(struct gameState test, struct gameState def) {
  int i = 0;
  printf("TEST #4\n");
  printf("Testing Opponent Hand Size with %d Players\n", test.numPlayers);
  printf("==> Opponent Hand Size should remain unchanged (0 Cards)\n");
  for (i = 1; i < test.numPlayers; i ++) {
    printf("Received Hand Size for Opponent %d: %d\n", i + 1, test.handCount[1]);
    printf("Expected Hand Size for Opponent %d: %d\n", i + 1, def.handCount[1]);
    if(def.handCount[1] != test.handCount[1]){
      printf("[%sFAILED%s] Received Opponent Hand Size Value (%d Cards) Incorrect\n", KRED, KNRM, test.handCount[1]);
    } else {
      printf("[%sPASSED%s] Received and Expected Opponent Hand Size Values Match\n", KGREEN, KNRM);
    }
  }
}

/*******************************************************************************
* Description: opponent_deck_size_test function
*******************************************************************************/

void opponent_deck_size_test(struct gameState test, struct gameState def) {
  int i = 0;
  printf("TEST #5\n");
  printf("Testing Opponent Deck Size with %d\n", test.numPlayers);
  printf("==> Opponent Deck Size should remain unchanged (10 Cards)\n");
  for (i = 1; i < test.numPlayers; i ++){
    printf("Received Deck Size for Opponent %d: %d\n", i + 1, test.deckCount[i]);
    printf("Expected Deck Size for Opponent %d: %d\n", i + 1, def.deckCount[i]);
    if(def.deckCount[1] != test.deckCount[1]){
      printf("[%sFAILED%s] Received Opponent Deck Size Value (%d Cards) Incorrect\n", KRED, KNRM, test.deckCount[1]);
    } else {
      printf("[%sPASSED%s] Received and Expected Opponent Deck Size Values Match\n", KGREEN, KNRM);
    }
  }
}

/*******************************************************************************
* Description: played_card_test function
*******************************************************************************/

void played_card_test(struct gameState test, struct gameState def) {
  int played = 1,
      def_value = (def.playedCardCount + played);
  printf("TEST #6\n");
  printf("Testing Played Card Count with %d Players\n", test.numPlayers);
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

void discard_test(struct gameState test, struct gameState def) {
  printf("TEST #7\n");
  printf("Testing Played Discard Count with %d Players\n", test.numPlayers);
  printf("==> Discard Count should be increased by at least 1 Card\n");
  printf("Received Discard Count Value: %d\n", test.discardCount[0]);
  printf("Starting Discard Count Value: %d\n", def.discardCount[0]);
  if((def.discardCount[0] + 1) <= test.discardCount[0]){
    printf("[%sFAILED%s] Received Discard Count Value (%d Cards) Incorrect\n", KRED, KNRM, test.discardCount[0]);
  } else {
    printf("[%sPASSED%s] Received is Equal to Expected of Greater\\n", KGREEN, KNRM);
  }
}

/*******************************************************************************
* Description: kingdom_card_test function
*******************************************************************************/

void kingdom_card_test(struct gameState test, struct gameState def, int* kingdomCards) {
  char* king_names[10] = {
                            "Adventurer", "Embargo", "Village", "Minion", "Mine",
                            "Cutpurse", "Sea Hag", "Tribute", "Smithy", "Council Room"
                          };
  int i = 0;
  printf("TEST #8\n");
  printf("Testing Supply Card Piles (Kingdom Cards) with %d Players\n", test.numPlayers);
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

void victory_card_test(struct gameState test, struct gameState def, int* victoryCards) {
  char* vict_names[10] = {
                            "Estate", "Duchy", "Province"
                          };
  int i = 0;
  printf("TEST #9\n");
  printf("Testing Supply Card Piles (Victory Cards) with %d Players\n", test.numPlayers);
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
