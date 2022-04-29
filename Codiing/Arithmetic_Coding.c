#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// clock_t start, stop;
// double duration;

#define CAPACITY 10

int encode(char *str);
int decode(float num);

/*
 * 字符序列长度
 * 编码概率
 * 编码长度
 * 编码结果
 * 解码结果
 *
 */

int float2bin(double denum, int *bins);
float bin2float(int *bins, int size);
// int main(int argc, char *argv[])
int main()
{
    // if (argc == 1)
    // {
    //     fprintf(stderr, "You must supply a filename to read\n");
    //     exit(1);
    // }
    //double num = 0.6028047367709117821384322878364;
    //printf("%lf\n", num);
    double num = 0.4453125;
    int *bins = malloc(CAPACITY * sizeof(int));
    int size;
    size = float2bin(num, bins);
    printf("\n");
    printf("%d\n", size);

    float denum;
    denum = bin2float(bins, size);
    printf("%lf\n", denum);
}

int float2bin(double denum, int *bins)
{
    // double a = 0.2784;
    int capacity = CAPACITY;
    int size = 0;
    while (denum != 0)
    {
        denum = denum * 2;
        if (denum >= 1.0)
        {
            bins[size] = 1;
            printf("%d", bins[size]);
        }
        else
        {
            bins[size] = 0;
            printf("%d", bins[size]);
        }
        denum = denum - (int)denum;
        size++;

        if (size == capacity)
        {
            capacity += CAPACITY;
            bins = realloc(bins, capacity * sizeof(int));
        }
        
    }
    return size;
}


float bin2float(int *bins, int size)
{
    //有精度问题
    double denum = 0;
    for (int i = 0; i < size; i++)
    {
        denum = denum + bins[i] * pow(2, -(double)(i + 1));
        //printf("%lf\n", denum);
    }
    return denum;
}

int adaptive_encode(char *filename)
{
    FILE *fp = fopen(filename, "r");
    
}
