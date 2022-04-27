#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[1]);
        exit(2);
    }

    //get size of file
    struct stat status;
    int ret = stat(argv[1], &status);
    if (ret == -1)
    {
        fprintf(stderr, "can not stat %s: ", argv[1]);
        perror(NULL);
        exit(1);
    }
    
    int size = status.st_size;
    printf("size is: %d\n", size);

    //open file for reading
    FILE *w = fopen(argv[1], "r");
    if (!w)
    {
        fprintf(stderr, "can not open %s for reading: ", argv[1]);
        perror(NULL);
        exit(1);
    }
    
    //allocate memory for entire file
    char *contents = malloc(size);

    //read entire file in all at once
    fread(contents, size, 1, w);
    fclose(w);

    //count the number of newlines to give us the number of words
    int wordcount = 0;
    for (int i = 0; i < size; i++)
    {
        if (contents[i] == '\n')
        {
            wordcount++;
        }
    }
    printf("number of the words: %d\n", wordcount);

    //build the array of pointers to each word
    char **words = malloc(wordcount * sizeof(char *));
    words[0] = &contents[0];
    int word = 1;

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