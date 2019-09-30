/*=============================================================================
|   Source code:  [perfect-number-tester]
|        Author:  [Hector Ramirez]
|    Student ID:  [Your Student ID]
|    Assignment:  Program #[2] [Perfect Numbers]
|
|            Course:  [COP 4338]
|           Section:  [U04]
|        Instructor:  William Feild
|          Due Date:  [10/01/2019], at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|
|        Language:  [C]
|  Compile/Run:  [The fallowing instructions is to compile in the ocelot server at FIU.
|                   -std=c99: used to direct the compiler to use the newer c99 standard and libraries.
|                   -lm: used to tell the compiler to link the math library.
|                 ]
| 	gcc -std=c99 -lm *.c -o perfect-numbers perfect-number-tester.c perfect-numbers.c
|   ./perfect-numbers
|  +-----------------------------------------------------------------------------
|
|  Description:  [This is a header file shared between perfect-number-tester.c and perfect-numbers.c, it has shared
|                    libraries imports and shared defines. This header file also contains the function prototype for
|                    mainLoop.]
|
|        Input:  [No input or output is done from this header file.]
|
|       Output:  [No Output is done in this header file. ]
|
|     Process:  [Header file only contains share library imports and defines as well as shared function prototypes. ]
|
|   Required Features Not Included:
|                [None, all requested features are present.]
|
|   Known Bugs:  [No known bugs.]
|  *===========================================================================*/
#include <stdio.h>
#include <math.h> //used for pow() and sqrt()

/**
 * EMPTY_INITIALIZER : used whenever anything needs to be initialized, set to a default value of 0
 * NO_ERROR: Used to return 0 reported errors from functions.
 */
#define EMPTY_INITIALIZER 0
#define NO_ERROR 0

/**
 * Function Prototype, please go to function declaration for further information.
 */
void mainLoop(int desiredAccuracy, double threshold);

