/* 
 * head file
 * read large text file function
 */

#ifndef __READ_TEXT_H__
#define __READ_TEXT_H__

struct node
{
    char word[100]; // also can use a pointer to string and malloc space
    struct node *next;
};

void read_stat(char *filename);
void read_line(char *filename);
void read_dict(char *filename);

#endif