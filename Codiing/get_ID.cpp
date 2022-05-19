#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>

#include <sys/stat.h>

using namespace std;

int get_ID(char *filename);
int ID_vector(char *filename);
int ID_encode(char *filename);
int ID_decode(char *encodefile, char *codefile);
int time_encode(char *filename);
int time_decode(char *filename);

unordered_map<string, string> ID_Dict;
unordered_map<string, int> encode;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "please enter file name" << endl;
    }
    //get_ID(argv[1]);
    //ID_vector(argv[1]);
    //ID_encode(argv[1]);
    ID_decode(argv[1], argv[2]);
    //consider to just restore the difference between time
    //but the question is map has its order, not the original time order
    return 0;
}

int time_encode(char *filename)
{
    //input:encode file(time index)
    //output:encode file(encode_time index)
    //restore the difference between time to compress the time info
    ifstream fin(filename, ios::in);
    if (!fin.is_open())
    {
        cout << "file open failed" << endl;
    }

    ofstream fout("./time_encode.txt", ios::out);

    string buff;
    string time_buff;
    string index_buff;
    int num = 0;
    int pre = 0;
    int cur = 0;
    while(getline(fin, buff))
    {
        time_buff = buff.substr(0, buff.find(' '));
        index_buff = buff.substr(buff.find(' '));    

        cur = atoi(time_buff.c_str());
        num = cur - pre;
        pre = cur;
        fout << to_string(num) << index_buff <<endl;
    }
    //cout << num << endl;
  
    fin.close();
    fout.close();
    
    return 0;
}

int time_decode(char *filename)
{
    //input:encode file(encode_time index)
    //output:encode file(time index)
    //restore the difference between time to compress the time info
    ifstream fin(filename, ios::in);
    if (!fin.is_open())
    {
        cout << "file open failed" << endl;
    }

    ofstream fout("./time_decode.txt", ios::out);

    string buff;
    string time_buff;
    string index_buff;
    int num = 0;
    int pre = 0;
    int cur = 0;
    while(getline(fin, buff))
    {
        time_buff = buff.substr(0, buff.find(' '));
        index_buff = buff.substr(buff.find(' '));    

        cur = atoi(time_buff.c_str());
        num = cur + pre;
        pre = cur;
        fout << to_string(num) << index_buff <<endl;
    }
    //cout << num << endl;
  
    fin.close();
    fout.close();
    
    return 0;
}

int ID_decode(char *encodefile, char *codefile)
{
    ifstream fencode;  //the encode file include time and index
    fencode.open(encodefile, ios::in);

    ifstream fcode;  //the dict file include the signal and index
    fcode.open(codefile,ios::in);

    string outfile = codefile;
    outfile = outfile.insert(outfile.find("code"), "de");
    //string outfile = "./wave_info_decode.txt";  //decode file to reconstruct time and signal
    FILE *fout = fopen(outfile.c_str(), "w");
    
    unordered_map<string, string> dict;  //reconstruct the dict from file
    string codebuff;
    string dict_index;
    string dict_ID;
    while(getline(fcode,codebuff))
    {
        dict_index = codebuff.substr(0, codebuff.find(' '));
        dict_ID = codebuff.substr(codebuff.find(' ')+1);
        dict[dict_index] = dict_ID;
    }

    string buff;
    while(getline(fencode, buff))
    {
        //get the index
        string ID_index = buff.substr(buff.find(' ')+1);
        unordered_map<string, string>::iterator iter = dict.find(ID_index);
        if (iter != dict.end())
        {
            //write to the decode file
            fprintf(fout, "%s %s\n", buff.substr(0, buff.find(' ')).c_str(), iter->second.c_str());
        }

    }
    fclose(fout);
    return 0;
}


int ID_encode(char *filename)
{
    //input file:time signal_ID
    ifstream fin;
    fin.open(filename, ios::in);
    if (!fin.is_open())
    {
        cout << "file open failed" << endl;
    }
    
    //write the map dict to a txt file:index signal_ID
    string outfile = filename;
    outfile = outfile.insert(outfile.find(".txt"), "_code");
    FILE *fout = fopen(outfile.c_str(), "w");

    //save the encode content:time index
    string encodefile = filename;
    encodefile = encodefile.insert(encodefile.find(".txt"), "_encode");
    FILE *fcode = fopen(encodefile.c_str(), "w");

    string buff;
    int encodenum = 0;
    int index = 0;
    while(getline(fin, buff))
    {
        string ID_buff = buff.substr(buff.find(' ')+1);
        unordered_map<string, int>::iterator iter = encode.find(ID_buff);
        if (iter != encode.end())  //find the signal_ID in the map dict
        {
            index = iter->second;
            fprintf(fcode, "%s %d\n", buff.substr(0, buff.find(' ')).c_str(), index);
        }
        else  //not find, add the signal_ID to the map dict
        {
            encode[ID_buff] = encodenum;
            fprintf(fcode, "%s %d\n", buff.substr(0, buff.find(' ')).c_str(), encodenum);
            encodenum++;
        }
    }
    fclose(fcode);
    //save the map dict to a txt file
    for (unordered_map<string, int>::iterator it = encode.begin(); it != encode.end(); it++)
    {
        fprintf(fout, "%d %s\n", it->second, it->first.c_str());
    }
    fclose(fout);
    return 0;
}


int get_ID(char *filename)
{
    //input file just inlcude wave information
    ifstream fin;
    fin.open(filename, ios::in);
    if (!fin.is_open())
    {
        cout << "file open failed" << endl;
    }
    
    //save the time and signal_ID info not include signal_form
    string IDfile = filename;
    //if ".txt" make some error, change to '.'
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
            fout << buff << endl;  //save the time info
        }
        else if (buff[0] == 'b' || buff[0] == 'r')
        {
            fout << buff.substr(buff.find(' ')+1) << endl;  //save the vector signal
        }
        else
        {
            fout << buff.substr(1) << endl;  //save the scalar signal
        }
            
    }
    fin.close();
    fout.close();
    return 0;
}


int ID_vector(char *filename)
{
    ifstream fin;
    fin.open(filename, ios::in);
    if (!fin.is_open())
    {
	cout << "file open failed" << endl;
    }
    
    string IDfile = filename;
    IDfile = IDfile.insert(IDfile.find(".txt"), "_vec");
    /*FILE *fp = fopen(IDfile.c_str(), "w");*/
    ofstream fb(IDfile, ios::out);
    string buff;
    //string t_str = "";
    //string ID_str = "";
    
    //saved form:time signal_ID
    while (getline(fin, buff))
    {
    //ofstream fb("./fb.txt",ios::out);
    //saved form:time signal_ID
    //while (getline(fin, buff))
    //{
        //skip the control ASCII
        char a = buff[0];
        if(int(a) < 32)
        {
            continue;
        }

        if(buff[0] == '#')
        {
            if(buff != "#0")
            {
                fb << endl;
            }
            fb << buff << ' ';
            //fb << buff << endl;
            //cout << "\n" << endl;
        }
        else if (buff[0] == 'b' || buff[0] == 'r')
        {
            
            fb << buff.substr(buff.find(' ')+1);  //save vector signal
        }
        else
        {
            fb << buff.substr(1);  //save scalar signal
        }


        /*if (buff == "$enddefinitions $end")
        {
            h_end = true;
            continue;
        }*/
        //skip the control ASCII
        /*char a = buff[0];
        if (int(a) < 32)
        {
            continue;
        }
        
        //save time
        if (buff[0] == '#')
        {
            //to get first time
            if (buff == "#0")
            {
                t_str = buff;
                continue;
            }

            ID_Dict[t_str] = ID_str;  //save previous time
            t_str = "";  //clear for next time
            ID_str = "";
            t_str = buff;
        }
        else if (buff[0] == 'b' || buff[0] == 'r')
        {
            ID_str += buff.substr(buff.find(' ')+1);  //save vector signal
        }
        else
        {
            ID_str += buff.substr(1);  //save scalar signal
        }*/

    }
    //save the map dict to a txt file
    /*for (unordered_map<string, string>::iterator it = ID_Dict.begin(); it != ID_Dict.end(); it++)
    {
        fprintf(fp, "%s %s\n", it->first.c_str(), it->second.c_str());

    }
    fclose(fp);*/
    fb.close();
    return 0;
}



