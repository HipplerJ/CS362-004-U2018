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
** and randomtestadventurer.c. (45 Points)
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
#include <time.h>
#include <math.h>
#include <assert.h>

/*******************************************************************************
** FUNCTION DECLARATIONS
*******************************************************************************/

int main(int argc, char const *argv[]) {
  printf("Hello World!\n");
  return 0;
}

void smithy_rand_test(){
  printf("In the smithy random test\n");
}
