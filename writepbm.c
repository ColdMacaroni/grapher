#include <stdio.h>
#include "points.h"

/* Example pbm file format from
 * https://en.wikipedia.org/wiki/Netpbm#PBM_example
 *
 * 0 = white
 * 1 = black
 */

/*
 * P1
 * # This is an example bitmap of the letter "J"
 * 6 10
 * 0 0 0 0 1 0
 * 0 0 0 0 1 0
 * 0 0 0 0 1 0
 * 0 0 0 0 1 0
 * 0 0 0 0 1 0
 * 0 0 0 0 1 0
 * 1 0 0 0 1 0
 * 0 1 1 1 0 0
 * 0 0 0 0 0 0
 * 0 0 0 0 0 0
 */

/* Will write a pbm file out of arguments.
 * Args:
 *  > Array of struct points
 *  > Len of array
 *
 * Then it will calculate the width and height of the file.
 * It will create an empty array of that size, will loop through
 * the given array setting the specific bits to 1.
 * It iwll then write it to a pbm file.
 */

void writePbm(point_t *points, int point_num)
{
    int width;
    int height;
    // Calculate width and height
}
