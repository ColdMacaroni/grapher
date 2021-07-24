#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

void shiftCoords(node_t *head, int min_x, int min_y)
{
    /* Will shift coordinates from negative to positive */
    // Store this early so that the comparison is run only once
    const bool shift_x = min_x < 0;
    const bool shift_y = min_y < 0;

    node_t *tmp = head;

    while (tmp != NULL)
    {
        if (shift_x)
        {
            tmp->coord.x -= min_x;
        }

        if (shift_y)
        {
            tmp->coord.y -= min_y;
        }

        /* printf("(%d, %d), ", tmp->coord.x, tmp->coord.y); */

        tmp = tmp->next;
    }
    /* putchar('\n'); */
}


void invertY(node_t *head, unsigned int height)
{
    /* Invert the Y axis for compliance with pbm format */
    node_t *tmp = head;

    while (tmp != NULL)
    {
        // Not sure why -1 but it works
        tmp->coord.y = height - tmp->coord.y - 1;
        /* printf("(%d, %d), ", tmp->coord.x, tmp->coord.y); */

        tmp = tmp->next;
    }
    /* putchar('\n'); */
}

char
*generateContent(node_t *head, unsigned int width_a, unsigned int height_a)
{
    // Turn em into constants
    const unsigned int width = width_a;
    const unsigned int height = height_a;

    // All the text
    char *img_content;
    const char bg = '0';
    const char fg = '1';

    // magic
    const unsigned int file_len = 3 + 22 + (width * height) + height + 1;
    char size_str[23];

    // actual pixels
    const unsigned int pixels_len = (width * height) + height + 1;
    char pixels[pixels_len];

    // To be used during loop
    node_t *node_ptr = head;
    unsigned int pos;

    /* Alloc for the img file
     * Magic:   3   P1\n
     * Size:    22  len(max_int) is 10 so "10 10 \n"
     * (width * height) + height for final \n
     */

    // Initialize
    img_content = calloc(sizeof(char), file_len);
    memset(img_content, '\0', sizeof(char) * file_len);

    // Add magic bytes and size to start of file
    strcat(img_content, "P1\n");

    sprintf(size_str, "%d %d\n", width, height);
    strcat(img_content, size_str);

    /* printf("%s", img_content); */
    // Calc size plus newlines plus null
    memset(pixels, bg, sizeof(char) * pixels_len);

    // Set the terminating null char
    pixels[pixels_len - 1] = '\0';

    // Set the newlines
    // width + 1 to allow for the previous newline
    for (unsigned int row = width; row < pixels_len; row += width + 1)
        pixels[row] = '\n';

    // Mark the coordinates
    while (node_ptr != NULL)
    {
        // XXX: When the first coord isnt (0, 0), pos ends up being negative. Causing integer overflow and consequently segfault. UPDATE: Y comes here as negative if first coord isnt 0,0
        pos = (node_ptr->coord.y * (width + 1)) + node_ptr->coord.x;
        pixels[pos] = fg;

        node_ptr = node_ptr->next;
    }

    strcat(img_content, pixels);
    return(img_content);
}

void writePbm(node_t *head, char *filename)
{
    // TODO: Add a padding of 1px
    if (head == NULL)
    {
        fprintf(stderr, "Can't write an image of 0 pixels\n");
        exit(EXIT_FAILURE);
    }

    // Sep pointer for looping to not lose the head.
    node_t *node_ptr;

    unsigned int width, height;

    int min_x, max_x;
    int min_y, max_y;

    int ptr_x;
    int ptr_y;

    char *img_content;

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
    // Must add one because we are counting 0 as a position.
    width = max_x - min_x  + 1;
    height = max_y - min_y + 1;

    // This prints the img size
    /* printf("%s: %dx%dpx\n", filename, width, height); */

    // Get rid of negative numbers
    shiftCoords(head, min_x, min_y);

    // Y axis
    invertY(head, height);

    img_content = generateContent(head, width, height);

    // Write file
    FILE *file = fopen(filename, "w");
    fputs(img_content, file);
    fclose(file);

    free(img_content);
}
