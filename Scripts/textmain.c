#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "operate_text.h"

int main(int argc, char *argv[])
{
    /* in the vcd.txt, the signal and the identifier of the signal are unique
     * consider how to encode
     */
    /* char para[] = {"Youth means a temperamental predominance of courage over timidity \
                        of the appetite for adventure over the love of ease This often \
                        aaa bbbb cccc bbbb aaa cccc  fff"}; */
    // printf("%s\n", para);
    //create_word_fre_dict(para);
    if (argc == 1)
    {
        fprintf(stderr, "You must supply a filename to read\n");
        exit(1);
    }
    CHAR_DICT char_list[94] = {0};
    // all inittial 0
    memset(char_list, 0, 94 * sizeof(CHAR_DICT));

    //get each char anf its frequency
    cal_char_nums(argv[1], char_list);

    return 0;
}