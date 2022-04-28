/* 
 * definition file
 * read large text file function
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "read_text.h"


void read_stat(char *filename)
{

    // get size of file
    struct stat status;
    int ret = stat(filename, &status);
    if (ret == -1)
    {
        fprintf(stderr, "can not stat %s: ", filename);
        perror(NULL);
        exit(1);
    }

    int size = status.st_size;
    printf("size is: %d\n", size);

    // open file for reading
    FILE *w = fopen(filename, "r");
    if (!w)
    {
        fprintf(stderr, "can not open %s for reading: ", filename);
        perror(NULL);
        exit(1);
    }

    // allocate memory for entire file
    char *contents = malloc(size);

    // read entire file in all at once
    fread(contents, size, 1, w);
    fclose(w);

    // count the number of newlines to give us the number of words
    int wordcount = 0;
    for (int i = 0; i < size; i++)
    {
        if (contents[i] == '\n')
        {
            wordcount++;
        }
    }
    printf("number of the words: %d\n", wordcount);

    // build the array of pointers to each word
    char **words = malloc(wordcount * sizeof(char *));
    words[0] = &contents[0];
    int word = 1;

    // because each line with one word
    for (int i = 0; i < size; i++)
    {
        if (contents[i] == '\n')
        {
            contents[i] = '\0';
            if (word < wordcount)
            {
                words[word] = &contents[i + 1];
                word++;
            }
        }
    }

    for (int i = 0; i < wordcount; i++)
    {
        printf("%d %s\n", i, words[i]);
    }
}

void read_line(char *filename)
{
    //Allocate space for each line of strings

    //open file for reading
    FILE *w = fopen(filename, "r");
    if (!w)
    {
        fprintf(stderr, "can not open %s for reading: ", filename);
        perror(NULL);
        exit(1);
    }
    
    int capacity = 10;
    char **words = malloc(capacity * sizeof(char *));


    char line[100];
    int size = 0;
    while (fgets(line, 100, w) != NULL)
    {
        //trim newline
        char *nl = strchr(line, '\n');
        if (nl)
        {
            *nl = '\0';
        }
        
        //allocate space how long actually
        char *word = malloc(strlen(line) + 1);
        strcpy(word, line);
        words[size] = word;
        size++;

        //expand
        if (size == capacity)
        {
            //make array bigger
            capacity += 10;
            words = realloc(words, capacity * sizeof(char *));
        }
        
    }

    //how many valid elements
    for (int i = 0; i < size; i++)
    {
        printf("%d %s\n", i, words[i]);
    }

}

void read_dict(char *filename)
{
    // open file for reading
    FILE *w = fopen(filename, "r");
    if (!w)
    {
        fprintf(stderr, "can not open %s for reading: ", filename);
        perror(NULL);
        exit(1);
    }

    // initialize linked list
    struct node *head = NULL;
    struct node *tail = NULL;

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
            // empty list create first node and hook it
            struct node *n = malloc(sizeof(struct node));
            strcpy(n->word, line);
            head = n;
            tail = n;
        }
        else
        {
            struct node *n = malloc(sizeof(struct node));
            strcpy(n->word, line);
            tail->next = n;
            tail = n;
        }
    }

    struct node *current = head;
    while (current != NULL)
    {
        printf("%s\n", current->word);
        current = current->next;
    }
}

