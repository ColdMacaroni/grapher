#include <stdio.h>
#include <stdlib.h>
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

void writePbm(node_t *head, char *filename)
{
    if (head == NULL)
    {
        fprintf(stderr, "Can't write an image of 0 pixels\n");
        exit(EXIT_FAILURE);
    }

    // Sep pointer for looping to not lose the head.
    node_t *node_ptr;

    int width, height;

    // Initialize min and max variables to first element
    int min_x, max_x;
    int min_y, max_y;

    int ptr_x;
    int ptr_y;

    min_x = max_x = head->coord.x;
    min_y = max_y = head->coord.y;


    // Get minimum and maximum x and y.
    // Will be used for calculating the size of the image
    node_ptr = head;
    while (node_ptr != NULL)
    {
        // Store them for quicker accessing
        ptr_x = node_ptr->coord.x;
        ptr_y = node_ptr->coord.y;

        /* X */
        if (min_x > ptr_x)
            min_x = ptr_x;
        else if (max_x < ptr_x)
            max_x = ptr_x;

        /* Y */
        if (min_y > ptr_y)
            min_y = ptr_y;
        else if (max_y < ptr_y)
            max_y = ptr_y;

        // Go to next node
        node_ptr = node_ptr->next;
    }

    // This line prints min and max for x and y in a table
    // printf("\tX\tY\nMin\t%d\t%d\nMax\t%d\t%d\n", min_x, min_y, max_x, max_y);

    /* int width = points[0].x; */
    /* int height = points[0].y; */

    // Calculate width and height
    width = max_x - min_x;
    height = max_y - min_y;

    printf("%s: %dx%dpx\n", filename, width, height);
}
