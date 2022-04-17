/* C语言<stdio.h>提供了四个预定义的函数来读取文件内容
 * fgetc() -- this function is used to read a single character from the file
 * fgets() -- this function is used to read strings from files
   char * fgets(char *str, int size, FILE * ptr);
   str -- the strings which fgets() read from file
   size -- the maximum to read from steam
   ptr -- fie pointer
 * fscanf() -- this function is used to read the block of raw bytes from files.
   this used to read binary files
 * fread() -- this function is used to read formatted input from a file
 *
 * steps to read a file
 * 用fopen()打开一个文件 并将该文件的引用存储在FILE指针中
 * 用函数读取文件内容
 * 用fclose()关闭文件
 */

// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Course
{
    char cname[30];
    char sdate[30];
};

// Driver code
int main()
{
    
    //fgets() usage

    FILE* ptr;
    char str[50];
    ptr = fopen("test.txt", "a+");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    printf("content of this file are \n");

    while (fgets(str, 50, ptr) != NULL) {
        printf("%s", str);
    }

    fclose(ptr);
    //return 0;
   

    /* 
    //fread() usage
    FILE *of;
    of = fopen("test.txt", "w");
    if (of == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }

    struct Course inp1 = {"Algorithms",
                          "30OCT"};
    struct Course inp2 = {"DataStructures",
                          "28SEPT"};
    struct Course inp3 = {"Programming",
                          "1NOV"};
    fwrite(&inp1, sizeof(struct Course),
           1, of);
    fwrite(&inp2, sizeof(struct Course),
           1, of);
    fwrite(&inp3, sizeof(struct Course),
           1, of);
    if (fwrite != 0)
        printf("Contents to file written successfully !\n");
    else
        printf("Error writing file !\n");
    fclose(of);

    // File pointer to read from file
    FILE *inf;
    struct Course inp;
    inf = fopen("test.txt", "r");

    if (inf == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }

    while (fread(&inp, sizeof(struct Course),
                 1, inf))
        printf("Course Name = %s Started = %s\n",
               inp.cname, inp.sdate);
    fclose(inf); 
    */
}
