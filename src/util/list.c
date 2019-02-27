#include "util/list.h"

#include <stdlib.h> // malloc
#include <strings.h> // bzero
#include <string.h> // memcpy

t_list  *lstnew(const void *content, unsigned long content_size)
{
        t_list *out;

        out = malloc(sizeof(t_list));
        if (!out)
                return (NULL);
        bzero(out, sizeof(t_list));
        if (!content)
                out->content = NULL;
        else
        {
                out->content = malloc(content_size);
                out->content = memcpy(out->content, content, content_size);
        }
        out->next = NULL;
        return (out);
}

void lstfree(t_list *list)
{
        if (list->content)
                free(list->content);
        free(list);
}
