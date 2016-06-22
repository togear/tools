/*
 * =====================================================================================
 *
 *       Filename:  rfc1738_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月22日 09时25分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang
 *   Organization:  NGAA
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "rfc1738.h"


int main(int argc ,char *argv[]) {

    char p[] = "http://www.test.com/中国";
    char *r = NULL;
    printf("%s\n",p);


    r = rfc1738_escape(p);
    printf("%s\n",r);

    rfc1738_unescape(r);
    printf("%s\n",r);


    return 0;
}
