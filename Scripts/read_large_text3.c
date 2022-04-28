#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct node
{
    char word[100];  //also can use a pointer to string and malloc space
    struct node * next;
};


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(2);
    }

    //open file for reading
    FILE *w = fopen(argv[1], "r");
    if (!w)
    {
        fprintf(stderr, "can not open %s for reading: ", argv[1]);
        perror(NULL);
        exit(1);
    }
    
    //initialize linked list
    struct node * head = NULL;
    struct node * tail = NULL;

    // read file in one line at a time
    char line[100];
    while (fgets(line, 100, w) != NULL)
    {
        char *nl = strchr(line, '\n');
        if (nl)
        {
            *nl = '\0';
        }
        
        if (head == NULL)
        {
            //empty list create first node and hook it
            struct node * n = malloc(sizeof(struct node));
            strcpy(n->word, line);
            head = n;
            tail = n;
        }
        else
        {
            struct node * n = malloc(sizeof(struct node));
            strcpy(n->word, line);
            tail->next = n;
            tail = n;
        }
    }

    struct node * current = head;
    while (current != NULL)
    {
        printf("%s\n", current->word);
        current = current->next;
    }
    
    

}