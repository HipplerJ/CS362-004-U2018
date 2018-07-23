/*******************************************************************************
** Author: James Hippler (HipplerJ)
** Oregon State University
** CS 362-400 (Spring 2018)
** Software Engineering II
**
** Description: Random Testing (RT) Quiz
** Due: Sunday, June 22, 2018
**
** Filename: testme.c
**
** OBJECTIVES:
** The primary goal of this quiz is to learn how to generate a random test
** generator.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************************
* Description: inputChar function
*******************************************************************************/

char inputChar() {
  int n = (rand() % 94) + 32;                                                   // Select a random number in range of 32 - 128
  return (char)n;                                                               // Return the character associated with the ascii value
}

/*******************************************************************************
* Description: inputString function
*******************************************************************************/

char *inputString() {
  int str_len = 5,                                                              // Initialize integer variable for string length
      i = 0;                                                                    // Initialize integer variable for loop counter
  char rand_string[str_len + 1];                                                // Initialize string of length 6 and set to null
  char* rand_str = NULL;                                                        // Added this dynamic character variable to mitigate memory warning from Clang
  memset(rand_string, '\0', str_len + 1);                                       // Run memset on character array to ensure all elements are null
  for (i = 0; i < str_len; i ++) {                                              // Loop through each element of the random string (5 elements total)
    rand_string[i] = (rand() % 16) + 101;                                        // Assign a random ascii value (as character) to the current string element
  }
  rand_str = rand_string;                                                       // Assign the static character array to the dynamic character array (Corrects memory warning)
  return rand_str;                                                              // Return final randomized dynamic character array to the calling function
}

void testme() {
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1) {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9) {
      printf("error\n");
      exit(200);
    }
  }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    testme();
    return 0;
}
