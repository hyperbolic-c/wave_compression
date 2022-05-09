#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <fstream>

#include <sys/stat.h>

using namespace std;

map<string, int> dict;
map<int, string> revdict;

struct encodeinfo
{
    string P;
    int index;
};
vector<encodeinfo> LZW_encode(string s, int encodenum)
{
    string P = "";
    char C;
    vector<encodeinfo> EncodeResult; //存储编码之后的结果

    for (int i = 0; i < s.length(); i++)
    {
        C = s[i];
        string tempStr = P + C;
        //在字典里面寻找这个字符串
        map<string, int>::iterator iter = dict.find(tempStr);
        if (iter != dict.end())
        { //找到了
            P = tempStr;
        }
        else
        { //没找到
            encodeinfo a = {P, dict[P]};
            EncodeResult.push_back(a); //将P的对应的编码存放起来
            //建立起一个新的索引
            encodenum++;
            dict[tempStr] = encodenum;
            P = C;
        }
    }
    encodeinfo a = {P, dict[P]};
    EncodeResult.push_back(a); //最终结尾处

    /*
    //这是整个字典的输出
    map<string, int>::iterator iter = dict.begin();
    for (; iter != dict.end(); iter++){
    cout << iter->first << " " << iter->second << endl;
    }*/

    /*
    //这是编码过程的输出
    cout << "LZW编码输出的信息如下：" << endl;
    for (int i = 0; i < EncodeResult.size(); i++){
        cout << EncodeResult[i].P << " " << EncodeResult[i].index << endl;
    }
    */
    return EncodeResult;
}
string LZW_decode(vector<encodeinfo> code, int beginnum)
{
    string ret = ""; //最终译码的输出
    string P = "";
    char C;
    int pW, cW;
    //第一步，初始化，读入第一个的符号cW，解码输出
    cW = code[0].index;
    ret += revdict[cW]; //解码输出

    for (int i = 1; i < code.size(); i++)
    {
        pW = cW;
        cW = code[i].index;
        map<int, string>::iterator iter = revdict.find(cW);

        if (iter != revdict.end())
        { //找到了
            //解码输出
            ret += iter->second;
            P = revdict[pW];
            C = revdict[cW][0];
            string tempStr = P + C;
            beginnum++;
            revdict[beginnum] = tempStr;
        }
        else
        {
            P = revdict[pW];
            C = revdict[pW][0];
            beginnum++;
            string tempStr = P + C;
            revdict[beginnum] = tempStr;
            ret += tempStr;
        }
    }
    return ret;
}
int main(int argc, char *argv[])
{

    //get the size of the file
    struct stat status;
    //int ret = stat(filename, &status);
    int ret = stat(argv[1], &status);
    if (ret == -1)
    {
        fprintf(stderr, "can not stat %s: ", argv[1]);
        perror(NULL);
        exit(1);
    }

    int file_size = status.st_size;
    //printf("size is: %d\n", size);
    cout << "the size of the file is " << file_size << " Byte" << endl;

    dict.clear();
    revdict.clear();

    //应该首先建立一个包含所有单个字符ASCII码表的字符串表
    for (int i = 0; i < 128; i++)
    {
        string s = "t";
        s[0] = char(i);
        dict[s] = i;

        revdict[i] = char(i);
    }

    ifstream fin;
    fin.open(argv[1], ios::in);
    if (!fin.is_open())
    {
		cout << "file open failed" << endl;
	}
    
    //read the string
    string allTxtStr;
    string s;
    while (getline(fin, s))
    {
        allTxtStr += s;
        //cout << allTxtStr << endl;

        allTxtStr += '\n';  //for split
    }
    fin.close();
    //cout << allTxtStr << endl;

    cout << "coding..." << endl;
    vector<encodeinfo> res = LZW_encode(allTxtStr, 128);
    cout << "the length after coding: " << res.size() << endl;

    double ratio = (double)file_size / (4 * res.size());  //int is 4 byte
    printf("compression radio ：%10.3f\n", ratio);

    //save the encode result
    FILE *fo;
    //string codefile = "lzw_code.txt";
    string codefile = argv[1];
    codefile = codefile.insert(codefile.find(".txt"), "_code");
    
    fo = fopen(codefile.c_str(), "w");
    
    for (int i = 0; i < res.size(); i++)
    {
        //pW = cW;
        //cW = code[i].index;
        fprintf(fo, "%d\n", res[i].index);
    }
    fclose(fo);

    cout << "decoding..." << endl;
    string result = LZW_decode(res, 128); // result存储的是编码后的结果
    // cout << result << endl;

    // 分割要转换为char *
    int strlen = result.length() + 1;
    char *string1 = new char [strlen];
    int i;
    // cout << result.length() << endl;
    for (i = 0; i < result.length(); i++)
    {
        string1[i] = result[i];
    }
    string1[i] = '\0';

    //result = result + '\0';

    string decodefile = argv[1];
    decodefile = decodefile.insert(decodefile.find(".txt"), "_decode");
    ofstream fout;
    fout.open(decodefile, ios::out);

    //split
    const char *seps = "\n";  //会导致文件中本来的换行符也被筛选掉
    char *p;
    p = strtok(string1, seps);
    //p = strtok(result, seps);

    while(p)
    {
        fout << p << endl;
        p = strtok(NULL, seps);
    }

    fout.close();

    //system("pause");
    return 0;
}
