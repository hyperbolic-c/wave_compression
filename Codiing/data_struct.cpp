#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;


int head_info(char *filename);
int time_info(char *filename);
int wave_info(char *filename);
int ID_info(char *filename);
int main(int argc, char *argv[])
{
    //cout << "hello world" << endl;
    
    /*
     * 头文件信息 存储为一个字符串 用通用压缩方法进行压缩
     * 针对时间t 只存储时刻之间的差值
     * 针对信号值 0 1 x z 分别编码为二进制00 01 10 11
     * 针对信号id 依赖对照表进行压缩
     *
     */
    //bitset<4> a;
    //cout << a[2] << endl;
    
    //time_info(argv[1]);
    //head_info(argv[1]);
    wave_info(argv[1]);
    return 0;
}

int ID_info(char *filename)
{
    ifstream fin(filename, ios::in);
    if(!fin)
    {
        cout << "can not open the file" << endl;
    }
    
    //ofstream fout("./time_info.txt", ios::out);
    ofstream fout("./ID_info.txt", ios::out);
    string buff;
    while (getline(fin, buff))
    {
        /*if (buff == "$enddefinitions $end")
        {
            h_end = true;
            continue;
        }*/
        //skip the control ASCII
        char a = buff[0];
        if (int(a) < 32)
        {
            continue;
        }

        if (buff[0] == '#')
        {
            fout << buff << endl;  //save the time info
        }
        else if (buff[0] == 'b' || buff[0] == 'r')
        {
            fout << buff.substr(0, buff.find(' ')) << endl;  //save the vector signal value
        }
        else
        {
            fout << buff.substr(0, 1) << endl;  //save the scalar signal value
        }
            
    }
    fin.close();
    fout.close();
    return 0;
    
}

int time_info(char *filename)
{
    ifstream fin(filename, ios::in);
    if(!fin)
    {
        cout << "can not open the file" << endl;
    }
    
    //ofstream fout("./time_info.txt", ios::out);
    ofstream fout("./time_info_c.txt", ios::out);
    string buff;
    int num = 0;
    int pre = 0;
    int cur = 0;
    while(getline(fin, buff))
    {
        /*
        if(buff[0] == '#')
        {
            //cout << buff << endl;  //the last time #6639164150
            //fout << buff << endl;
            ++num;  //975538
        }*/
            
        buff = buff.substr(1);
        cur = atoi(buff.c_str());
        num = cur - pre;
        pre = cur;
        //num = atoi(buff) - num;
        fout << to_string(num) << endl;
    }
    cout << num << endl;
  
    fin.close();
    fout.close();
    
    return 0;
}

int head_info(char *filename)
{
    ifstream fin(filename, ios::in);
    if(!fin)
    {
        cout << "can not open the file" << endl;
    }

   
    ofstream fout("./head_info.txt", ios::out);
    string buff;
    string h_end = "$enddefinitions $end";
    while(getline(fin, buff))
    {
        fout << buff << endl;
        if(buff == h_end)
        {
            cout << "save the head info" << endl;
            break;
            fin.close();
            fout.close();
        }

    }



}


int wave_info(char *filename)
{
    ifstream fin(filename, ios::in);
    if(!fin)
    {
        cout << "can not open the file" << endl;
    }
    
    ofstream fout("./wave_info.txt", ios::out);
    string buff;
    bool wave = false;
    string h_end = "$enddefinitions $end";

    while(getline(fin, buff))
    {
        
        if(buff == h_end)
        {
            wave = true;
            continue;
        }
        if(wave)
        {
            fout << buff << endl;
        }

    }
    fin.close();
    fout.close();
    return 0;
}
