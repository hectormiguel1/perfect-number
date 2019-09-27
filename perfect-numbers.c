/*=============================================================================
|   Source code:  [//Todo]
|        Author:  [Hector Ramirez] 
|    Student ID:  [Your Student ID]  
|    Assignment:  Program #[//Todo] [//Todo]
|  
|            Course:  [COP 4338]  
|           Section:  [U04]  
|        Instructor:  William Feild  
|          Due Date:  [//Todo], at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|  
|        Language:  [C] 
|  Compile/Run:  [How to Compile and Execute this program, IN DETAIL.] 
| 	gcc -std=c99 //todo
|   //todo
|  +-----------------------------------------------------------------------------  
|  
|  Description:  [//Todo]  
|                  
|        Input:  [//Todo]  
|  
|       Output:  [//Todo]  
|  
|     Process:  [//Todo]  
|  
|   Required Features Not Included:  
|                [//Todo]  
|  
|   Known Bugs:  [//Todo]  
|  *===========================================================================*/
#include "perfect-numbers.h"
#include <string.h>
#include <stdlib.h>

#define START 1
#define END 100
#define GUESS_MULTIPLIER_ONE 0.5
#define GUESS_MULTIPLIER_TWO 0.05


int iterations = EMPTY_INITIALIZER;
char factorsString[END + 1] = { EMPTY_INITIALIZER };
double allowedThreshold = EMPTY_INITIALIZER;
int precision = EMPTY_INITIALIZER;
double computedSQRT = EMPTY_INITIALIZER;

int isPerfect(int number);
void doSQRTComputation(int number);
void printToScreen(int number);
void reset();
char* itoa(int,int);

int mainLoop(int desiredAccuracy, double threshold)
{
    precision = desiredAccuracy;
    allowedThreshold = threshold;

    for(int number = START; number <= END; number++)
    {
        if(isPerfect(number))
        {
           // doSQRTComputation(number);
           // printToScreen(number);
          reset();
        }
        else
        {
          reset();
        }
    }

    return NO_ERROR;
}

/**
 * FUNCTION NAME: isPerfect
 * Checks if the passed number is perfect.
 * In order to do so, we get the factors of the number and add them up, if the sum is the same as the number, the number
 * is perfect.
 * @param number: number to test if is perfect.
 * @return PERFECT if number is known to be perfect, NOT_PERFECT otherwise.
 */
#define PERFECT 1
#define NOT_PERFECT 0
#define DIVISOR_START 2
#define ALWAYS_DIVISOR 1
#define SPRINTF_FORMAT_STRING " + %d"

int isPerfect(int number)
{
    int factorSum = ALWAYS_DIVISOR; //TODO EXPLAIN WHY 2

    strcat(factorsString,itoa(ALWAYS_DIVISOR, 10));


    for (int divisor = DIVISOR_START; divisor < number; divisor++)
    {
        if(number % divisor == 0)
        {
            strcat(factorsString," + ");
            strcat(factorsString,itoa(divisor,10));
            factorSum += divisor;
        }
    }
    printf(factorsString);
    if(factorSum == number)
    {
        return PERFECT;
    }
    else
    {
        return NOT_PERFECT;
    }
}
char* itoa(int val, int base){

    static char buf[32] = {0};

    int i = 30;

    for(; val && i ; --i, val /= base)

        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i+1];

}

void reset()
{
    iterations = EMPTY_INITIALIZER;
    computedSQRT = EMPTY_INITIALIZER;
    memset(factorsString,0, sizeof(factorsString) - 1);
}

