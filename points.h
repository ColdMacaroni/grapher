#ifndef POINTS
#define POINTS 1

typedef
struct
_point
{
    int x;
    int y;
} point_t;

// Linked list
typedef
struct
_node
{
    point_t coord;
    struct _node *next;
} node_t;

node_t
*createNode(point_t value);

void
insertNode(node_t **head, node_t *to_insert);

void
freeLinked(node_t *head)

#endif
