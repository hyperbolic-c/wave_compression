#include <bits/stdc++.h>
using namespace std;

vector<int> encoding(string s1);
void decoding(vector<int> op);

int main(int argc, char *argv[])
{
	/* struct stat status;
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

	FILE *fp;
	fp = fopen(argv[1], "r"); */


	string s = "WYS*WYGWYS*WYSWYSG";
	vector<int> output_code = encoding(s);
	cout << "Output Codes are: ";
	for (int i = 0; i < output_code.size(); i++)
	{
		cout << output_code[i] << " ";
	}
	cout << endl;
	decoding(output_code);
}

vector<int> encoding(string s1)
{
	cout << "Encoding\n";

	//initial
	unordered_map<string, int> table;
	for (int i = 0; i <= 255; i++)
	{
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	string p = "";  //previous
	string c = "";  //current

	p += s1[0];
	int code = 256;
	vector<int> output_code;
	cout << "String\tOutput_Code\tAddition\n";
	for (int i = 0; i < s1.length(); i++)
	{
		if (i != s1.length() - 1)
			c += s1[i + 1];
		
		//p+c in the table
		if (table.find(p + c) != table.end())
		{
			p = p + c;
		}
		else
		{
			cout << p << "\t" << table[p] << "\t\t"
				 << p + c << "\t" << code << endl;
			output_code.push_back(table[p]);  //output the notation of p
			table[p + c] = code;  //set up a notation of p+c
			code++;
			p = c;  //update
		}
		c = "";
	}
	cout << p << "\t" << table[p] << endl;
	output_code.push_back(table[p]);
	return output_code;
}

void decoding(vector<int> op)
{
	cout << "\nDecoding\n";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++)
	{
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0];  //first notation
	int n;
	string s = table[old];  //first symbol
	string c = "";
	c += s[0];
	cout << s;

	int count = 256;
	for (int i = 0; i < op.size() - 1; i++)
	{
		n = op[i + 1];  //next notation

		if (table.find(n) == table.end())
		{
			s = table[old];
			s = s + c;
		}
		else
		{
			s = table[n];
		}

		cout << s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;  //restore the encoding process
		count++;
		old = n;
	}
}

