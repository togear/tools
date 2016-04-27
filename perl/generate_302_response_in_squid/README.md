# use this to generate 302 in squid

## Table of Contents

* [Config](#Config)
* [Result](#Result)

#Config
config squid.conf

```
acl www_test_com url_regex -i http://www.test.com/.*
url_rewrite_access allow www_test_com
url_rewrite_access deny all 
url_rewrite_program /usr/local/squid/bin/test.pl
url_rewrite_children 200 
storeurl_rewrite_concurrency 10
url_rewrite_host_header on
redirector_bypass off 
```
#Result
use curl to test

```curl
 curl -svo /dev/null http://www.test.com/test1.mp4  -x 10.10.100.33:80 
 * About to connect() to proxy 10.10.100.33 port 80
 *   Trying 10.10.100.33... connected
 * Connected to 10.10.100.33 (10.10.100.33) port 80
 > GET http://www.test.com/test1.mp4 HTTP/1.1
 > User-Agent: curl/7.15.5 (x86_64-redhat-linux-gnu) libcurl/7.15.5 OpenSSL/0.9.8b zlib/1.2.3 libidn/0.6.5
 > Host: www.test.com
 > Pragma: no-cache
 > Accept: */*
 > Proxy-Connection: Keep-Alive
 > 
 < HTTP/1.0 302 Moved Temporarily
 < Date: Tue, 26 Apr 2016 10:45:24 GMT
 < Content-Length: 0
 < Location: http:/www.test.com/test1.mp4
 < X-NGAA: MISS from CH-SH-PD1-311.2
 * HTTP/1.0 connection set to keep alive!
 < Connection: keep-alive
 * Connection #0 to host 10.10.100.33 left intact
```
