/*
 * =====================================================================================
 *
 *       Filename:  rfc1738.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月22日 09时22分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang
 *   Organization:  NGAA
 *
 * =====================================================================================
 */

extern char *rfc1738_escape(const char *);
extern char *rfc1738_escape_unescaped(const char *);
extern char *rfc1738_escape_part(const char *);
extern void rfc1738_unescape(char *);
