#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <map>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
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
double scaled_encode();
// int main(int argc, char *argv[])

int main()
{
    // if (argc == 1)
    // {
    //     fprintf(stderr, "You must supply a filename to read\n");
    //     exit(1);
    // }

    // double num = 0.6028047367709117821384322878364;
    // printf("%lf\n", num);
    //  double num = 0.4453125;
    //  int *bins = malloc(CAPACITY * sizeof(int));
    //  int size;
    //  size = float2bin(num, bins);
    //  printf("\n");
    //  printf("%d\n", size);

    // float denum;
    // denum = bin2float(bins, size);
    // printf("%lf\n", denum);
    
    double res;
    res = scaled_encode();
    cout << res << endl;
}

// int float2bin(double denum, int *bins)
// {
//     // double a = 0.2784;
//     int capacity = CAPACITY;
//     int size = 0;
//     while (denum != 0)
//     {
//         denum = denum * 2;
//         if (denum >= 1.0)
//         {
//             bins[size] = 1;
//             printf("%d", bins[size]);
//         }
//         else
//         {
//             bins[size] = 0;
//             printf("%d", bins[size]);
//         }
//         denum = denum - (int)denum;
//         size++;

//         if (size == capacity)
//         {
//             capacity += CAPACITY;
//             bins = realloc(bins, capacity * sizeof(int));
//         }

//     }
//     return size;
// }

// float bin2float(int *bins, int size)
// {
//     //有精度问题
//     double denum = 0;
//     for (int i = 0; i < size; i++)
//     {
//         denum = denum + bins[i] * pow(2, -(double)(i + 1));
//         //printf("%lf\n", denum);
//     }
//     return denum;
// }

// int adaptive_encode(char *filename)
// {
//     FILE *fp = fopen(filename, "r");

// }

typedef struct pro_inter
{
    //float pro[2];
    double pro[2];
} PRO_INT;

double scaled_encode()
{
    /*
     * l(n) = l(n-1) + (u(n-1)-l(n-1))F(x-1)
     * u(n) = l(n-1) + (u(n-1)-l(n-1))F(x)
     *
     * E1:[0, 0.5) -> [0, 1); E1(x)=2x  send 0
     * E1:[0.5, 1) -> [0, 1); E2(x)=2(x-0.5)  send 1
     * E3:
     *
     */
    // map<string, PRO_INT> para;
    map<char, PRO_INT> para;
    // char const *str = "1321";
    string s = "1321";
    PRO_INT exp1 = {0.0, 0.8};
    PRO_INT exp2 = {0.8, 0.82};
    PRO_INT exp3 = {0.82, 1.0};
    para['1'] = exp1;
    para['2'] = exp2;
    para['3'] = exp3;
    double l = 0.0;
    double u = 1.0;
    // printf("%d\n", para.size());

    // cout<<para.at("1").pro[0]<<endl;
    // int len = sizeof(para)/sizeof();
    //  float Fx = 0.0;
    for (int i = 0; i < s.size(); i++)
    {
        //cout << u-l <<endl;
        //string skey(1, s[i]);
        //cout << para.at(skey).pro[0] << endl;
        //cout << l <<"\t"<< u << endl;
        double delta = u - l;
        //cout << delta << endl;

        u = l + delta * para.at(s[i]).pro[1];
        l = l + delta * para.at(s[i]).pro[0];
        
        //cout << 0.656 + 0.144*0.82 <<endl;
        //std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);  
        //cout << l <<"\t"<< u << endl;
    }
    //cout << l << endl;
    return (u+l)/2;

    // printf("%d\n%d\n", sizeof(para), sizeof(para)/sizeof(PARA));
}
