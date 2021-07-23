#include <stdlib.h>
#include "points.h"

// Most linked list stuff from jacob sorber on yt
node_t
*createNode(point_t value)
{
    /* Creates a new node with a NULL pointer by default */

    // Allocate mem
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        return(NULL);

    // Set values
    new_node->coord = value;
    new_node->next = NULL;

    return(new_node);
}

void
insertNode(node_t **head, node_t *to_insert)
{
    /* Insert node to the start of the linked list */
    /* Head is a pointer pointer so that it doesnt have to be returned
     * and reassigned */

    // Chain up the rest of the list
    to_insert->next = *head;

    // Reassign head
    *head = to_insert;
}

void
freeLinked(node_t *head)
{
    node_t *tmp;
    /* Frees a linked list from memory */
    while (head != NULL)
    {
        // Store the current head
        tmp = head;

        // Change the current head to the next node
        head = head->next;

        // Free the current node
        free(tmp);
    }
}
