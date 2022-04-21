#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 提取辅助信息进行压缩 */
int Search_in_File(char *fname, char *str);

// Our main function.
int main(int argc, char *argv[])
{
    //int result, errno;

    if (argc < 2)
    {
        //Usage(argv[0]);
        printf("filename error");
        exit(1);
    }
    // Use system("cls") on windows
    // Use system("clear") on Unix/Linux
    //system("cls");
    //printf("%s%s", argv[1], argv[2]);
    Search_in_File(argv[1], argv[2]);
    // if (result == -1)
    // {
    //     perror("Error");
    //     printf("Error number = %d\n", errno);
    //     exit(1);
    // }
    return 0;
}

// void Usage(char *filename) {
// 	printf("Usage: %s <file> <string>\n", filename);
// 	printf("%s version 1.0 \nCopyright(c) CodingUnit.com\n", filename);
// }

int Search_in_File(char *fname, char *str) {
	FILE *fp;
	//int line_num = 1;
	//int find_result = 0;
	char buffer[512];
    //char *info = "_info";
    //char *outname = (char *)malloc(strlen(fname)+strlen(info));
	//sprintf(outname, "%s%s", fname, info);  //辅助信息文件
    FILE *fout;
	//gcc users
	//if((fp = fopen(fname, "r")) == NULL) {
	//	return(-1);
	//}

	//Visual Studio users
	// if((fopen_s(&fp, fname, "r")) != NULL) {
	// 	return(-1);
	// }
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
        //strstr()返回子串在字符串中第一次出现的位置
		//if((strstr(buffer, str)) != NULL)
        // "$enddefinitions"
        //putc()
        //printf("%s", buffer);

        /* int slen = strlen(buffer);
        char *s = malloc((slen + 1) * sizeof(char));
        strcpy(s, buffer);
        fprintf(fout, "%s", s); */
        
        fprintf(fout, "%s", buffer);  // 写入
        //if (strcmp(buffer, str) == 0)
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
			//printf("A match found on line: %d\n", line_num);
			//printf("\n%s\n", buffer);
			//find_result++;
		}
		//line_num++;
	}

	// if(find_result == 0) {
	// 	printf("\nSorry, couldn't find a match.\n");
	// }
	
	// //Close the file if still open.
	// if(fp) {
	// 	fclose(fp);
	// }
    printf("done");
    fclose(fp);
   	return 0;
}