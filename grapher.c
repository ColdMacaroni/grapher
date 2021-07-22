#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef
struct
_point
{
    int x;
    int y;
} point;

point
inputPoint(void);

int
strToInt(char *str, int len);

int
main()
{
    point sample = inputPoint();
    printf("x: %d\ny: %d\n", sample.x, sample.y);
    return(0);
}

point
inputPoint(void)
{
    char input[BUFSIZ];
    int num_len = 0;
    char *num = malloc(sizeof(char));

    int x = 0;
    int y = 0;

    int *coord = &x;

    fgets(input, BUFSIZ, stdin);

    // Go through every character
    // +1 so null character is never considered
    // Store digits in a char array
    for (int i = 0; input[i + 1] != '\0'; i++)
    {
        // Skip brackets and space in points (x, y) comma to be handled separately
        if (!isdigit(input[i]) && input[i] != ',')
            continue;

        if (input[i] == ',')
        {
            // Convert to int
            *coord = strToInt(num, num_len);

            // Reset stuff
            num_len = 0;
            num = malloc(sizeof(char));

            // Now store y
            coord = &y;

            continue;
        }

        // Store the current digit in the array
        num[num_len] = input[i];

        // Increase how many numbers there are
        num_len++;

        // Make space for next number
        num = realloc(num, (num_len + 1) * sizeof(char));
    }

    free(num);

    // Placeholder
    point pt = {
        .x = x,
        .y = y
    };

    return pt;
}

int
strToInt(char *str, int len)
{
    /* Convert an array of chars to int */
    int digits = len - 1;
    int num = 0;

    for (int i = 0; i < len; i++)
    {
        num += (str[i] - '0') * pow(10, digits - i);
    }

    return(num);
}
