/*
 * count the number of each word
 * successfully get the char and its frequency
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_MAX_SIZE 100

/* 词频字典结构体 */
typedef struct word_dict
{
    char word[WORD_MAX_SIZE]; /* 假设单词长度最长为100 */
    int times;                /* 在一篇文章出现次数不超过 2^31 - 1次 */
} WORD_DICT;

typedef struct char_dict
{
    char letter;
    long int times;
} CHAR_DICT;


int cmp_dict(const void *a, const void *b);
int cmp_fre_up(const void *a, const void *b);
int cmp_fre_down(const void *a, const void *b);
void create_word_fre_dict(char *paragraph);

//void cal_charnums(char *filename);
void cal_charnums(char *filename, CHAR_DICT *char_list);

int main(int argc, char *argv[])
{
    /* in the vcd.txt, the signal and the identifier of the signal are unique
     * consider how to encode
     */
    /* char para[] = {"Youth means a temperamental predominance of courage over timidity \
                        of the appetite for adventure over the love of ease This often \
                        aaa bbbb cccc bbbb aaa cccc  fff"}; */
    // printf("%s\n", para);
    //create_word_fre_dict(para);
    if (argc == 1)
    {
        fprintf(stderr, "You must supply a filename to read\n");
        exit(1);
    }
    CHAR_DICT char_list[94] = {0};
    // all inittial 0
    memset(char_list, 0, 94 * sizeof(CHAR_DICT));

    //get each char anf its frequency
    cal_charnums(argv[1], char_list);

    return 0;
}

/* 按字典序排序 */
int cmp_dict(const void *a, const void *b)
{
    WORD_DICT *pa = (WORD_DICT *)a;
    WORD_DICT *pb = (WORD_DICT *)b;

    return strcmp(pa->word, pb->word);
}

/* 按词频从小到大排序 */
int cmp_fre_up(const void *a, const void *b)
{
    WORD_DICT *pa = (WORD_DICT *)a;
    WORD_DICT *pb = (WORD_DICT *)b;

    return (pa->times - pb->times);
}

/* 按词频从大到小排序 */
int cmp_fre_down(const void *a, const void *b)
{
    WORD_DICT *pa = (WORD_DICT *)a;
    WORD_DICT *pb = (WORD_DICT *)b;

    return (pb->times - pa->times);
}

void create_word_fre_dict(char *paragraph)
{
    /* consider to add dynamic attend */

    // declare struct array
    WORD_DICT char_list[1000] = {0};
    // all inittial 0
    memset(char_list, 0, 1000 * sizeof(WORD_DICT));

    /* 预处理： 单词全改为小写, 非单词全转为空格符 */
    //int i = 0;
    //while (paragraph[i] != 0)
    //{
        /* if (paragraph[i] >= 'A' && paragraph[i] <= 'Z')
        {
            tolower(paragraph[i]);
        }
        else if ((paragraph[i] < 'A' || paragraph[i] > 'Z') &&
                 ((paragraph[i] < 'a' || paragraph[i] > 'z')))
        {
            paragraph[i] = ' ';
        }
        i++; */

        /* if ((paragraph[i] < 'A' || paragraph[i] > 'Z') &&
            ((paragraph[i] < 'a' || paragraph[i] > 'z')))
        {
            paragraph[i] = ' ';
        }
        i++; */
    //}

    // get the first word
    char *temp = strtok(paragraph, " ");
    strcpy(char_list[0].word, temp);
    char_list[0].times++;

    int *p;  //get the dict_index
    // get the another word
    while (temp != NULL)
    {
        temp = strtok(NULL, " "); /* 最后一个字节拿出来后还会执行一次，这次结果为NULL */
        if (temp == NULL)
        {
            break;
        }
        // printf("%s\n", temp);

        int dict_index = 0;
        int find = 0;

        while (char_list[dict_index].times != 0 && dict_index < 1000)
        {
            // the same word
            if (strcmp(char_list[dict_index].word, temp) == 0)
            {
                char_list[dict_index].times++;
                find = 1;
                break;
            }
            dict_index++;
        }

        // the new word
        if (!find && dict_index < 1000)
        {
            strcpy(char_list[dict_index].word, temp);
            char_list[dict_index].times = 1;
        }
        //printf("%d\n", dict_index);
        p = &dict_index;
    }

    // ascending sort
    //int size = sizeof(char_list) / sizeof(char_list[0]);
    //const size_t Num = sizeof(char_list) / sizeof(*char_list);
    //qsort(char_list, Num, sizeof(WORD_DICT), cmp_fre_up);
    /* for (int de = 0; de < Num; de++)
    {
        printf("%s, count = %d\n", char_list[de].word, char_list[de].times);
    } */

    //printf("%s, count = %d\n", char_list[1].word, char_list[1].times);
    int size = 0;  // number of elements
    size = *p + 1; 
    qsort(char_list, size, sizeof(WORD_DICT), cmp_fre_up);
    for (int de = 0; de < size; de++)
    {
        printf("%s, count = %d\n", char_list[de].word, char_list[de].times);
    }
}

// CHAR ascending sort
int char_comp(const void *a, const void *b)
{
    CHAR_DICT *pa = (CHAR_DICT *)a;
    CHAR_DICT *pb = (CHAR_DICT *)b;

    return (pa->times - pb->times);
}

void cal_charnums(char *filename, CHAR_DICT *char_list)
{
    FILE *fp;
    fp = fopen(filename, "r");
    //char buffer[256];
    if (!fp)
    {
        fprintf(stderr, "can not open %s for reading\n", filename);
        exit(1);
        //return NULL;
    }
    // all ASCII code 128
    // char ASCII from 33 to 126 total94
    //CHAR_DICT char_list[94] = {0};
    // all inittial 0
    //memset(char_list, 0, 94 * sizeof(CHAR_DICT));

    char ch;
    while ((ch = getc(fp)) != EOF)
    {
        int index = (int) ch;
        //strcpy(char_list[index].letter, ch);
        if (32 < index && index < 127)
        {
            //printf("%d", ch);
            char_list[index - 33].letter = ch;
            char_list[index - 33].times++;
        }    
        //char_list[ch - 33].letter = ch;
        //char_list[ch - 33].times++;
    }

    qsort(char_list, 94, sizeof(CHAR_DICT), char_comp);
    for (int de = 0; de < 94; de++)
    {
        printf(" '%c':%d\n", char_list[de].letter, char_list[de].times);   
    }
}
