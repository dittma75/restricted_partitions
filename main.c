/* 
 * File:   main.c
 * Author: Kevin
 *
 * Created on July 8, 2014, 8:46 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "distinct.h"
#include "least_part_m.h"
#include "h_function_generator.h"
#include "h_sign_generator.h"
#include "unrestricted_partition.h"
mpz_t cache[1000000];
int main(int argc, char** argv) 
{
    if (argc != 3)
    {
        printf("Usage: partitions_generating_working_copy.exe m n");
        exit(EXIT_FAILURE);
    }
    printf("m= %s; n = %s\n", argv[1], argv[2]);
    mpz_t result;
    mpz_init(result);
    //generate();
    //Set args under Run/Set Project Configuration/Customize.../Run/Run Command 
    h_sign_generator(atoi(argv[1]));
    h_function_generator(atoi(argv[1]), atoi(argv[2]));
    h(result, atoi(argv[1]) , atoi(argv[2]));
    gmp_printf("%Zd\n", result);
    return (EXIT_SUCCESS);
}

