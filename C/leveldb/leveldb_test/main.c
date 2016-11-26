#include"leveldb.h"

int main( void ) 
{

    levelDB_init();

    char * key1     = "http://www.test.com/123/456/789/index.html";
    char * key2     = "http://www.test.com/123/456/index.html";
    char * key3     = "http://www.test.com/123/mo.mp3";
    char * key4     = "http://www.test.com/index.html";
    char * key5     = "http://www.baidu.com/index.html";
    char * key7     = "http://www.baidu.com/d.cc";
    char  key[1024]     = "http://www.test.com/s.rmvb";
    char * seek_key_1 = "http://www.test.com/123/456/789";
    char * seek_key_2 = "http://www.test.com/123/";

    
    printf("Writing ..\n");
    levelDB_write(key);
    levelDB_write(key1);
    levelDB_write(key2);
    levelDB_write(key3);
    levelDB_write(key4);
    levelDB_write(key5);
    levelDB_write(key7);

    printf("Reading ..\n");
    levelDB_read();
    
    printf("Seeking %s..\n",seek_key_1);
    levelDB_seek(seek_key_1);

    printf("Seeking %s..\n",seek_key_2);
    levelDB_seek(seek_key_2);

    //leveldb_options_set_create_if_missing(options, 0);

    levelDB_close();
    levelDB_destroy();

    return EXIT_SUCCESS;
}


