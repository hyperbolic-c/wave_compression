#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "operate_text.h"


/* 词频字典结构体 */
/* typedef struct word_dict
{
    char word[WORD_MAX_SIZE]; //假设单词长度最长为100
    int times;                //在一篇文章出现次数不超过 2^31 - 1次
} WORD_DICT; */

/* 字符字典结构体 */
/* typedef struct char_dict
{
    char letter;
    long int times;
} CHAR_DICT; */

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

/* 计算单词的个数 */
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

/* 字符升序排序 */
int char_comp(const void *a, const void *b)
{
    CHAR_DICT *pa = (CHAR_DICT *)a;
    CHAR_DICT *pb = (CHAR_DICT *)b;

    return (pa->times - pb->times);
}

/* 计算字符个数 */
void cal_char_nums(char *filename, CHAR_DICT *char_list)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "can not open %s for reading\n", filename);
        exit(1);
        //return NULL;
    }
    // all ASCII code 128
    // char ASCII from 33 to 126 total 94
    //CHAR_DICT char_list[94] = {0};
    // all inittial 0
    //memset(char_list, 0, 94 * sizeof(CHAR_DICT));

    char ch;
    while ((ch = getc(fp)) != EOF)
    {
        int index = (int) ch;
        if (32 < index && index < 127)
        {
            //printf("%d", ch);
            char_list[index - 33].letter = ch;
            char_list[index - 33].times++;
        }    
    }

    qsort(char_list, 94, sizeof(CHAR_DICT), char_comp);
    for (int de = 0; de < 94; de++)
    {
        printf(" '%c':%d\n", char_list[de].letter, char_list[de].times);   
    }
}

/* extract a part of the text */
int Search_in_File(char *fname, char *str)
{
    //fname--filename
    //str--flag of string end
    
	FILE *fp;
	char buffer[512];
    FILE *fout;

    fp = fopen(fname, "r");
    fout = fopen("info.txt", "w");
    /* 
      修改为创建临时文件
      fout = tmpfile();
      //在这里对临时文件中的预备信息进行操作
      fclose(fout);
     */

	while(fgets(buffer, 512, fp) != NULL)
    {

        fprintf(fout, "%s", buffer);  // 写入

        if((strstr(buffer, str)) != NULL)  //这一行检索到 "$enddefinitions"
        {
            //check the file size
            fseek(fout, 0L, SEEK_END);
            long int res = ftell(fp);
            printf("%ld\n", res);
            fclose(fout);
            break;
            /* 
              接下来的buffer就是波形数据
              buffer[0] == '#'
              就是一个时刻
             */
		}
	}
    fclose(fp);
   	return 0;
}