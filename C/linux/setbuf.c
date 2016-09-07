/*
 * =====================================================================================
 *
 *       Filename:  setbuf.c
 *
 *    Description:  test line buf 
 *
 *        Version:  1.0
 *        Created:  2016年09月08日 05时42分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang (gk), yong.huang@ngaa.com.cn
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Hello");

    if( 0 == fork()) {
        printf("child\n");
        return 0;
    }
    printf("parent\n");
    return 0;
}



