#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <fstream>

#include <sys/stat.h>

using namespace std;

int get_ID(char *filename);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "please enter file name" << endl;
    }
    get_ID(argv[1]);
    return 0;
}

int get_ID(char *filename)
{
    ifstream fin;
    fin.open(filename, ios::in);
    if (!fin.is_open())
    {
		cout << "file open failed" << endl;
	}

    string IDfile = filename;
    IDfile = IDfile.insert(IDfile.find(".txt"), "_ID");
    ofstream fout;
    fout.open(IDfile, ios::out);

    if (!fout.is_open())
    {
		cout << "file created failed" << endl;
	}

    //bool h_end = false;
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
            fout << buff << endl;
        }
        else if (buff[0] == 'b' || buff[0] == 'r')
        {
            fout << buff.substr(buff.find(' ')+1) << endl;
        }
        else
        {
            fout << buff.substr(1) << endl;
        }
            
    }
    fin.close();
    fout.close();
    return 0;
}
