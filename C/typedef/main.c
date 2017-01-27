/*
 * =====================================================================================
 *
 *       Filename:  typedef.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年01月27日 10时27分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"


int main(int argc, char **argv) {
    async_report_t t;
    printf("read_timeout= %d\n",t.read_timeout);
    return 1;
}

