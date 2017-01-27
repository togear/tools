/*
 * =====================================================================================
 *
 *       Filename:  typedef.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年01月27日 10时39分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

typedef int ngx_connection_t;
typedef int ngx_msec_t;

typedef struct async_report_s async_report_t;
typedef void (*ngx_http_refresh_handler_pt)(ngx_connection_t *,struct async_report_s *);
