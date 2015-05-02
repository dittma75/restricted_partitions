#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "h_function_generator.h"

/*Pre:  1 <= m <= n
 *Generate a function_tree.txt file that the rest of the
 *program can use to count the number of partitions.
 */
//O(3nlog_4(n))
int h_function_generator(int m, int n)
{
    FILE *file;
    double epsilon = .000001;
    double numbers = pow(2, m - 1);
    double counter = 0;
    int original = n - (m - 1);
    file = fopen("function_tree.txt", "w");
    if (file == NULL)
    {
        printf("Error:  Can't write file.  Make sure function_tree.txt is closed.");
        return (EXIT_FAILURE);
    }
    if (numbers > 4)
    {
        for (int offset = 0; offset < 3; offset++)
        {
            fprintf(file, "%d;", original - offset);
            counter++;
        }
        fprintf(file, "0;");
        counter++;
    }
    //Special case for no decomposition.
    else if (numbers == 1)
    {
        fprintf(file, "%d;", original);
    }
    //Special case for 2 decomposition functions.
    else if (numbers == 2)
    {
        fprintf(file, "%d;", original);
        fprintf(file, "%d;", original - 1);
    }
    //Special case for 4 decomposition functions.
    else if (numbers == 4)
    {
        for (int offset = 0; offset < 4; offset++)
        {
            fprintf(file, "%d;", original - offset);
            counter++;
        }
    }
    //O(n)
    for (int k = 4; k < numbers; k+=4)
    {
        double k_left = k;
        int decrement = 0;
        //O(3log(n))
        while ((k_left - epsilon) > 0 )
        {
            int exponent = 0;
            int power = 1;
            //O(log(n))
            //Get the largest exponent that can fit in k.
            while ((power * 4) <= k_left)
            {
                power *= 4;
                exponent++;
            }
            int amount_of_power = k_left / power;
            k_left -= amount_of_power * power;
            //Examples:
            /*exponent is 16, amount_of_power is 1
             *We decrement by 16's special number, which is 5, or 2(2) + 1;
             */
            if (amount_of_power == 1)
            {
                decrement += 2 * exponent + 1;
            }
            /*exponent is 16, amount_of_power is 2
             *We want to decrement by a 16 jump's special number, which is 
             *5, or 2(2)+1.
             *Then, we want to decrement by an additional 1, so 6, or (2(2)+1)+1  
             */
            if (amount_of_power == 2)
            {
                decrement += (2 * exponent + 1) + 1;
            }
            /*exponent is 16, amount_of_power is 3
             *We want to decrement by 16's special number, which is 5, or 2(2)+1.
             *Then, we want to decrement by an additional 1, so 6, or (2(2)+1)+1.
             *Last, we want to decrement by 16's special number again, which is
             *another 5, so 11, or 2(2(2)+1)+1
             */
            if (amount_of_power == 3)
            {
                decrement += 2 * ((2 * exponent) + 1) + 1;
            }
        }
        
        if (numbers > 8)
        {
            for (int offset = 0; offset < 4; offset++)
            {
                /*Given the following grid for blocks of 16 numbers:
                 *00;01;02;03;
                 *04;05;06;07;
                 *08;09;10;11;
                 *12;13;14;15;
                 *Numbers 3, 4, 5, 7, 8, 10, 11, and 12 cancel with each other.
                 */
                if (double_mod(counter, 16.0, 3.0) ||
                    double_mod(counter, 16.0, 4.0) ||
                    double_mod(counter, 16.0, 5.0) ||
                    double_mod(counter, 16.0, 7.0) ||
                    double_mod(counter, 16.0, 8.0) ||
                    double_mod(counter, 16.0, 10.0) ||
                    double_mod(counter, 16.0, 11.0) ||
                    double_mod(counter, 16.0, 12.0))
                {
                    fprintf(file, "0;");
                }
                else
                {
                    fprintf(file, "%d;", original - (decrement + offset));
                }
                counter++;
            }
        }
        /*When there are exactly 8 numbers (this loop only fires if numbers > 4),
         *the fifth number will cancel with the fourth.
         */
        else
        {
            fprintf(file, "0;");
            counter++;
            for (int offset = 1; offset < 4; offset++)
            {
                fprintf(file, "%d;", original - (decrement + offset));
                counter++;
            }
        }
    }
    fclose(file);
    return (EXIT_SUCCESS);
}

double log_4(int x)
{
    return (log(x) / log(4));
}

/* Function from:
 * http://stackoverflow.com/questions/1944119/what-is-the-fastest-way-to\
 * -test-if-a-double-number-is-integer-in-modern-intel-x
 */
int isInteger(double n)
{
  return n - (double)(int)n == 0.0;
}

//returns true if dividend mod divisor has the given remainder.
int double_mod(double dividend, double divisor, double remainder)
{
    return isInteger((dividend - remainder) / divisor);
}