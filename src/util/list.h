//
// Created by kohlten on 2/27/19.
//

#ifndef LIST_H
#define LIST_H

typedef struct s_list t_list;

struct s_list
{
    void *content;
    t_list *prev;
    t_list *next;
};

t_list  *lstnew(const void *content, unsigned long content_size);
void lstfree(t_list *list);

#endif
