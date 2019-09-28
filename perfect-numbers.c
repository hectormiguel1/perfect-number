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
#define END 100000
#define FACTOR_ARRAY_SIZE 320
#define START_GUESS_STRING "\nInitial \"guess\" = %f"
#define EXPECTED_SQRT_STRING "\nExpected square root of %d = "
#define COMPUTED_SQRT_STRING "\nComputed square root of %d = "
#define REACHED_STRING "\n\treached in %d iterations"
#define THRESHOLD_STRING "\n\tusing threshold "
#define ACCURACY_STRING "\n\tfor %d decimal-place accuracy \n"
#define DECIMAL_FORMAT_SUBSECTION_ONE "%."
#define DECIMAL_FORMAT_SUBSECTION_TWO "lf"



int iterations = EMPTY_INITIALIZER;
int factors[FACTOR_ARRAY_SIZE] = { EMPTY_INITIALIZER };
double allowedThreshold = EMPTY_INITIALIZER;
int precision = EMPTY_INITIALIZER;
double computedSQRT = EMPTY_INITIALIZER;
char decimalFormat[7];

int isPerfect(int number);
void doSQRTComputation(int number);
void printToScreen(int number);
void reset();

int mainLoop(int desiredAccuracy, double threshold)
{

    precision = desiredAccuracy;
    allowedThreshold = threshold;
    sprintf(decimalFormat,"%s%d%s",DECIMAL_FORMAT_SUBSECTION_ONE,precision,DECIMAL_FORMAT_SUBSECTION_TWO);

    for(int number = START; number <= END; number++)
    {
        if(isPerfect(number))
        {
           doSQRTComputation(number);
           printToScreen(number);
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
#define DIVISOR_START 1
#define ALWAYS_DIVISOR 1
#define SPRINTF_FORMAT_STRING " + %d"
int isPerfect(int number) {
    int factorSum = EMPTY_INITIALIZER;
    int lastFactorIndex = EMPTY_INITIALIZER;

    for (int divisor = DIVISOR_START; divisor < number; divisor++) {
        if (number % divisor == 0) {
            factors[lastFactorIndex] = divisor;
            lastFactorIndex++;
            factorSum += divisor;
        }
    }
    if (factorSum == number) {
        return PERFECT;
    } else {
        return NOT_PERFECT;
    }
}

/**
 * FUNCTION NAME: doSQRTComputation
 * This function uses the babylonian method to compute the square root of the passed number
 * to a previously specified threshold.
 * Babylonian Method is as fallows:
 * better estimation = (initial guess + number/initial guess) /2
 * As a result of the formula, the magic number 2 will be used in this function.
 * @param number: number to compute the square root of.
 * @return NONE: void function.
 */
#define GUESS_MULTIPLIER 0.15
void doSQRTComputation(int number)
{
    double previousSQRT = number * GUESS_MULTIPLIER;
    double currentSQRT = previousSQRT;
    double difference = EMPTY_INITIALIZER;

    do{
        iterations++;
        previousSQRT = currentSQRT;
        currentSQRT = (previousSQRT + (number/ previousSQRT)) / 2;
        difference = currentSQRT - previousSQRT;

        if (difference < EMPTY_INITIALIZER)
        {
            difference *= -1; //Flips the sign
        }


    }while(difference > precision);

    computedSQRT = currentSQRT;
}

/**
 * FUNCTION NAME: printToScreen
 * This functions does the final printing to the screen.
 * Due to the fact that 1 as always a divisor to every number, it is always printed outside the loop,
 * therefor the loop can iterate from the next factor, for this reason the for loop starts at 1 instead of
 * 0.
 * @param number: perfect number to be printed
 * @return : Nothing is return, void function.
 */
void printToScreen(int number)
{
    printf("Perfect Number %d = 1", number);
    for (int index = 1; index < FACTOR_ARRAY_SIZE; index++) //1 is explained in header file, please read.
    {
        if(factors[index])
        {
            printf(" + %d",factors[index]);
        }
    }
    printf(";");

    printf(START_GUESS_STRING,(number * GUESS_MULTIPLIER));
    printf(EXPECTED_SQRT_STRING,number);
    printf(decimalFormat,sqrt(number));
    printf(COMPUTED_SQRT_STRING,number);
    printf(decimalFormat,computedSQRT);
    printf(REACHED_STRING,iterations);
    printf(THRESHOLD_STRING);
    printf(decimalFormat,precision);
    printf(ACCURACY_STRING,precision);
}
/**
 * FUNCTION NAME: reset
 * This function resets all the values used when testing if the number is perfect.
 * in order to rest the array we are using memset which is part of the string.h file
 * while not discussed in the book it is referenced in the appendix.
 * @param: NONE
 * @return: function return type is void
 */
void reset()
{
    iterations = EMPTY_INITIALIZER;
    computedSQRT = EMPTY_INITIALIZER;
    for(int index = EMPTY_INITIALIZER; index < FACTOR_ARRAY_SIZE; index++)
    {
        factors[index] = EMPTY_INITIALIZER;
    }

}

