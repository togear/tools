/* ************************************************************************
 *       Filename:  dump_hex.c
 *    Description:  
 *        Version:  1.0
 *        Created:  01/13/16 15:16:35
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>
#include <string.h>

void dump_hex(char * str, int len);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name: main 
 *  Description:  
 * =====================================================================================
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage:  HexDump file  \n");
        return 1;
    }
    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("Can't open the file.\n");
        return 2;
    }

    char str[640000];
    int len = 0;
    char d[17] ; d[16]=0;
    unsigned int bytes =  0;

    while (bytes = fread(d, 1, 16, file))
    {
        memcpy(str+len,d,bytes);
	    printf("%s",d);
        len += bytes;
    }

    printf("len = %d\n",len);

    dump_hex(str,len);

    fclose(file);
	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dump_hex
 *  Description:  
 * =====================================================================================
 */

void dump_hex(char * str, int len)
{

    char d[17];
	d[16] = 0;
    unsigned int i, bytes, index = 0;
    int left_len = len;

    while(left_len > 0)
    {
        if(left_len/16 >= 1)
        {
            memcpy(d,str+index,16);
            bytes = 16;
        }
        else
        {
            memcpy(d,str+index,left_len);
            bytes = left_len;
        }

        printf("%08X\t", index);

        index += 16;

        for (i = 0; i < bytes; i++)
        {
            printf("%02X", (unsigned char)(d[i]));

            if ((i + 1) % 4 == 0)
                printf(" ");

            if (d[i] == 127 || d[i] < -127 || (d[i] >= 0 && d[i] <= 31))
                d[i] = '.';
        }

        if (bytes < 16)
        {
            for(i = bytes; i < 16; i++)
            {
                printf("   ");
                if ((i + 1) % 4 == 0)
                    printf(" ");
            }
            d[bytes] = '\0';
        }

        printf("%s\n", d);
        left_len -= 16;
    }
}

