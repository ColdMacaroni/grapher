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

int
peek(FILE *stream);

point
inputPoint(void);

int
strToInt(char *str, int len);

int
main()
{
    // This array will store all points
    point *points = malloc(sizeof(point));
    int points_n = 0;

    puts("Enter coordinates in format (x, y)");
    puts("Blank lines will be considered (0, 0)");
    puts("Enter EOF to stop input.");
    while (peek(stdin) != EOF)
    {
        // Store the points in array
        points[points_n] = inputPoint();
        points_n++;
        points = realloc(points, (points_n + 1) * sizeof(point));
    }

    printf("%d points\n", points_n);

    free(points);
    return(0);
}

int
peek(FILE *stream)
{
    /* Looks at the next char in the stream */
    // From https://stackoverflow.com/a/2082772
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

point
inputPoint(void)
{
    char input[BUFSIZ];
    int num_len = 0;
    char *num = malloc(sizeof(char));

    int x = 0;
    int y = 0;

    // First start with x
    int *coord = &x;

    fgets(input, BUFSIZ, stdin);

    // Go through every character
    // +1 so null character is never considered
    // Store digits in a char array
    for (int i = 0; input[i + 1] != '\0'; i++)
    {
        // Skip brackets and space in points (x, y)
        if (!isdigit(input[i]) && input[i] != ',')
            continue;

        // Comma signifies different num
        if (input[i] == ',')
        {
            // Convert to int
            *coord = strToInt(num, num_len);

            // Reset stuff
            num_len = 0;
            free(num);
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

    // For loop will end with num storing the second number.
    *coord = strToInt(num, num_len);
    free(num);

    point pt = {
        .x = x,
        .y = y
    };
    return(pt);
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
