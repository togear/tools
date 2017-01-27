/*
 * =====================================================================================
 *
 *       Filename:  struct.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年01月27日 10时45分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "typedef.h"

struct async_report_s{
    //ngx_buf_t send_buf;
    //ngx_int_t report_len;
    //ngx_buf_t recv_buf;

    ngx_msec_t   connect_timeout;
    ngx_msec_t   write_timeout;
    ngx_msec_t   read_timeout;

    ngx_http_refresh_handler_pt write_event_handler;
    ngx_http_refresh_handler_pt read_event_handler;
};
