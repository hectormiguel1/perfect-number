/*=============================================================================
|   Source code:  [perfect-number-tester]
|        Author:  [Hector Ramirez]
|    Student ID:  [5708475]
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
|  Description:  [Ths program iterates through a predefined list of numbers and finds the perfect numbers within the list.
|                   When a perfect number is found, we find the square root of the number, and then outputs the required
|                    information about the perfect number.]
|
|        Input:  [Through mainLoop, this program takes in a precision and threshold, used when computing threshold,
|                    or printing to the screen.]
|
|       Output:  [Output will include all of the perfect numbers between [1-100000], along with an ordered list of their
|                   factors to confirm the factors sum to the perfect number. For each perfect number, the output will
|                   also include the initial square root guess, the expected value using sqrt() (or a similar function),
|                   computed value for the square root of that number, the required decimal-place accuracy,
|                   the required threshold, and the number of terms (iterations) it took to reach the required
|                   decimal-place accuracy. ]
|
|     Process:  [The program will iterate through a list of pre-defined numbers looking for perfect numbers, when one is
|                 encountered, we will compute that numbers square root using the babylonian method. After the information
|                 about the perfect number is printed. After each iteration from START to END, reset is called to clean up
|                 variables used during the last check for perfect number.   ]
|
|   Required Features Not Included:
|                [None, all requested features are present.]
|
|   Known Bugs:  [No known bugs.]
|  *===========================================================================*/
#include "perfect-numbers.h" //Used to include shared libraries and function definitions

/**
 * START: This is the starting point from which we are finding perfect numbers, it is provided by the specifications.
 * END: This is the stopping point where we want to stop finding perfect numbers.
 * FACTOR_ARRAY_SIZE: Size of the array where the computed factors will be stored. In order to prevent memory corruption
 * around the array this number has been set to a value roughly equal to the square root of END, as in testing this has
 * proven to have the best result it terms of efficiency and memory consumption.
 * DECIMAL_FORMAT_STRING_SIZE: This is used to set the size of the decimal format string, as this has to be passed into
 * sprintf(), we have to make sure that ample size is available to insert formatted string with space for string terminator.
 * TOTAL_RUN_TIME: Number found through testing, total run time in seconds on ocelot server, with no optimizations options
 * enabled.
 */
#define START 1
#define END 100000
#define FACTOR_ARRAY_SIZE 317
#define DECIMAL_FORMAT_STRING_SIZE 7
#define TOTAL_RUN_TIME 30

/**
 * iterations: (int) keeps track track of the number of iterations that where needed to reach the desired accuracy for the
 * square root. This variable is reset upon each loop.
 * factors: (int[]) this is the holding place for the factors computed in the isPerfect method. This array is reset after
 * each iteration as we must find the factors of each number to see if the number is perfect.
 * allowedThreshold : (double) this is the maximum allowed threshold when computing the square root of the perfect number.
 * This number is stored as a double as max precision is required.
 * precision: (int) This is the decimal-place at which the most precision is desired.
 * computedSQRT: (double) This is where the computed square root of the perfect number is stored after being computed.
 * This variable is reset after every iteration.
 * decimalFormat: (char[]) This is the decimal format string which will be modified and used for printing the floating
 * point values to the desired accuracy. This string is formed when the mainLoop function is called with the desiredAccuracy
 * value.
 */
int iterations = EMPTY_INITIALIZER;
int factors[FACTOR_ARRAY_SIZE] = { EMPTY_INITIALIZER };
double allowedThreshold = EMPTY_INITIALIZER;
int precision = EMPTY_INITIALIZER;
double computedSQRT = EMPTY_INITIALIZER;
char decimalFormat[DECIMAL_FORMAT_STRING_SIZE];

/**
 * This are function prototypes, for a more complete in-depth explanation of each function please head to each functions
 * definition.
  */
void printTimeDisclaimer(void);
int isPerfect(int number);
void doSQRTComputation(int number);
void printToScreen(int number);
void reset();

/**
 * FUNCTION NAME: mainLoop.
 * This is the main control function for computing the perfect numbers. From this function, the decimalFormat string is
 * concatenated into a string contained the desired precision value and the loop begins from START to END. This function
 * also sets the *global* variables precision and allowedThreshold which are passed as arguments from the outside.
 * @param desiredAccuracy: The desired decimal place accuracy when computing the square root.
 * @param threshold: double value containing the maximum allowed delta for the square root.
 * @return : N/A, void return type function.
 */
void mainLoop(int desiredAccuracy, double threshold) {

    precision = desiredAccuracy;
    allowedThreshold = threshold;

    sprintf(decimalFormat, "%s%d%s", "%.",desiredAccuracy, "f");

    printTimeDisclaimer();
    for (int number = START; number <= END; number++) {
        if (isPerfect(number)) {
            doSQRTComputation(number);
            printToScreen(number);
            reset();
        } else {
            reset();
        }
    }
}

/**
 * FUNCTION NAME: printTimeDisclaimer
 * This function prints the run time disclaimer to the user, expressing how long the program might take to complete.
 * @param: NONE, VOID
 * @return: NONE, VOID
 */
void printTimeDisclaimer(void)
{
    printf("This program can take up to %d seconds to run... \n",TOTAL_RUN_TIME);
}

/**
 * FUNCTION NAME: isPerfect
 * Checks if the passed number is perfect.
 * In order to do so, we get the factors of the number and add them up, if the sum is the same as the number, the number
 * is perfect. the factors are then stored in the *global* array factors.
 * PERFECT: In C any number != 0 is considered true, 1 was the next best choice.
 * NOT_PERFECT: C representation for false.
 * DIVISOR_START: starts at number 1 to avoid div by 0.
 * @param number: number to test if is perfect.
 * @return PERFECT if number is known to be perfect, NOT_PERFECT otherwise.
 */
#define PERFECT 1 //explained in function header.
#define NOT_PERFECT 0 //explained in function header.
#define DIVISOR_START 1 //explained in function header.
int isPerfect(int number) {
    int factorSum = EMPTY_INITIALIZER;
    int lastFactorIndex = EMPTY_INITIALIZER;

    for (int divisor = DIVISOR_START; divisor < number; divisor++) {
        if (!(number % divisor)) //if remainder > 0, divisor is not a factor, inside statements wont execute.
        {
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
 * GUESS_MULTIPLIER: This is my own value, chosen for bringing down iterations with larger numbers.
 * @param number: number to compute the square root of.
 * @return NONE: void function.
 */
#define GUESS_MULTIPLIER 0.075 //explained in function header.
void doSQRTComputation(int number)
{
    double previousSQRT = number * GUESS_MULTIPLIER;
    double currentSQRT = previousSQRT;
    double difference = EMPTY_INITIALIZER;

    do{
        iterations++;
        previousSQRT = currentSQRT;
        currentSQRT = (previousSQRT + (number/ previousSQRT)) / 2; // 2 is explained in function header, not magic
        difference = currentSQRT - previousSQRT;

        if (difference < 0) //0 is used to check if the difference is negative, holds no other meaning.
        {
            difference *= -1; //Flips the sign
        }


    }while(difference > allowedThreshold);

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
    double expectedSQRT = sqrt(number);
    printf("Perfect Number %d = 1", number);
    for (int index = 1; index < FACTOR_ARRAY_SIZE; index++) //1 is explained in header file, please read.
    {
        if(factors[index])
        {
            printf(" + %d",factors[index]);
        }
    }
    printf("; \n");
    printf("Initial \"guess\" = %.2f \n",(number * GUESS_MULTIPLIER));
    printf("Expected square root of %d = ", number);
    printf(decimalFormat,expectedSQRT);
    printf("\nComputed square root of %d = ",number);
    printf(decimalFormat,computedSQRT);
    printf("\n\treached in %d iterations", iterations);
    printf("\n\tusing threshold of ");
    printf(decimalFormat,allowedThreshold);
    printf("\n\tfor %d decimal-place accuracy",precision);
    printf("\n");
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

