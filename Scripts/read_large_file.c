#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STEPSIZE = 100;
char **loadfile(char *filename, int *len);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "You must supply a filename to read\n");
        exit(1);
    }
    
    int length = 0;
    char **words = loadfile(argv[1], &length);
    if (!words)
    {
        fprintf(stderr, "can not build data structure\n");
        exit(1);
    }
    
    printf("%d\n", length);

    for (int i = 0; i < length; i++)
    {
        printf("%s", words[i]);
    }
    printf("\nDone\n");
}

char **loadfile(char *filename, int *len)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "can not open %s for reading\n", filename);
        return NULL;
    }
    
    int arrlen = 0;

    //allocate space
    //char **lines = (char **)malloc(arrlen * sizeof(char *));
    char **lines = NULL;


    char buf[1000];
    int i = 0;

    while (fgets(buf, 1000, f))
    {   
        // check if array is full, if so, extend it
        if (i == arrlen)
        {   
            arrlen += STEPSIZE;
            char **newlines = realloc(lines, arrlen * sizeof(char *));
            if (!newlines)
            {
                fprintf(stderr, "can not realloc\n");
                exit(1);
            }
            lines = newlines;
        }
        

        //trim off newline char
        //buf[strlen(buf) - 1] = '\0';

        //get length of buf
        int slen = strlen(buf);

        //allocate space for the string
        char *str = malloc((slen + 1) * sizeof(char));

        //copy string
        strcpy(str, buf);

        //attach str to data structure
        lines[i] = str;

        i++;
    }
    *len = i;  //set the length of the array of char *s
    return lines;
}
