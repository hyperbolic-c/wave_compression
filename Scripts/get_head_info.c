#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 提取辅助信息进行压缩 */
int Search_in_File(char *fname, char *str);

// Our main function.
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("filename error");
        exit(1);
    }
    Search_in_File(argv[1], argv[2]);
    return 0;
}


int Search_in_File(char *fname, char *str)
{
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