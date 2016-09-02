/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  test leveldb
 *
 *        Version:  1.0
 *        Created:  2016年09月02日 01时04分58秒
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
#include <string.h>
#include <leveldb/c.h>

void safe_free_leveldb(char * err);

int main( void ) 
{
    leveldb_t               *db;
    leveldb_options_t       *options;
    leveldb_readoptions_t   *roptions;
    leveldb_writeoptions_t  *woptions;
    char *err = NULL;
    char *read;
    const char* dbfile  = "/tmp/testdb_t";
    const char* key     = "name";
    const char* value   = "value";
    size_t read_len;
    /*  leveldb version */
    fprintf(stderr,"version:%d.%d\n",leveldb_major_version(),leveldb_minor_version());
    /*  open the database */
    options = leveldb_options_create();
    leveldb_options_set_create_if_missing(options,1);
    db = leveldb_open(options,dbfile,&err);
    if ( err != NULL )
    {
        fprintf(stderr,"Open testdb fail.\n");
        return ( EXIT_FAILURE );
    }
    /*  reset error var */
    safe_free_leveldb(err);
    /*  WRITE */
    woptions = leveldb_writeoptions_create();
    leveldb_put(db,woptions,key,strlen(key),value,strlen(value), &err);
    if ( err != NULL )
    {
        fprintf(stderr,"Write fail.\n");
        return ( EXIT_FAILURE );
    }
    fprintf(stdout,"put ok!\n");
    /*  reset error var */
    safe_free_leveldb(err);
    /*  READ */
    roptions = leveldb_readoptions_create();
    read = leveldb_get(db,roptions, key, strlen(key), &read_len, &err);
    if ( err != NULL )
    {
        fprintf(stderr, "Read fail.\n");
        return ( EXIT_FAILURE );
    }
    printf("READ %s:%s\n",key,read);
    fprintf(stdout,"get ok!\n");
    leveldb_free( read );
    read = NULL;
    /*  reset error var */
    safe_free_leveldb(err);
    /* ************************************************/
    /* * delete **/
    leveldb_delete(db,woptions, key, strlen(key),&err );
    if ( err != NULL )
    {
        fprintf(stderr,"Delete fail.\n");
    }
    /* ***********************************************/
    /*  close db */
    leveldb_close( db );
    /* **********************************************/
    /*  destroy */
    leveldb_destroy_db( options, dbfile, &err );
    if ( err != NULL )
    {
        fprintf(stderr, "Destory fail.\n");
        return ( EXIT_FAILURE );
    }
    /*  reset error var */
    safe_free_leveldb(err);

    return EXIT_SUCCESS;
}

void safe_free_leveldb(char * err) {
    leveldb_free( err );
    err = NULL;
}
