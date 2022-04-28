#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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