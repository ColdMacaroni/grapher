#include <stdio.h>
#include <ctype.h>

typedef struct _point
{
    int x;
    int y;
} point;

point inputPoint(void);

int main()
{
    point sample = inputPoint();
    printf("x: %d\ny: %d\n", sample.x, sample.y);
    return(0);
}

point inputPoint(void)
{
    char input[BUFSIZ];

    fgets(input, BUFSIZ, stdin);

    // Go through every character
    // +1 so null character is never considered
    for (int i = 0; input[i + 1] != '\0'; i++)
    {
        // Skip brackets and space in points (x, y) comma to be handled separately
        if (input[i] == '(' ||
            input[i] == ')' ||
            input[i] == ' ')
            continue;

        putchar('a');
    }

    point hi;
    hi.x = 2; hi.y=3;
    return hi;
}
