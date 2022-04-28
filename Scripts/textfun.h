/* 
 * text file operate function
 */
#pragma once

#ifndef __TEXTFUN_H__
#define __TEXTFUN_H__

#define WORD_MAX_SIZE 100

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

/* 按字典序排序 */
int cmp_dict(const void *a, const void *b);

/* 按词频从小到大排序 */
int cmp_fre_up(const void *a, const void *b);

/* 按词频从大到小排序 */
int cmp_fre_down(const void *a, const void *b);

/* 计算单词的个数 */
void create_word_fre_dict(char *paragraph);


/* 字符升序排序 */
int char_comp(const void *a, const void *b);

/* 计算字符个数 */
void cal_char_nums(char *filename, CHAR_DICT *char_list);

/* extract a part of the text */
int Search_in_File(char *fname, char *str);


#endif