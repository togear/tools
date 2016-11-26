#include "leveldb.h"


void print_self(const char * type, const char *start, size_t len);

int levelDB_init()
{

    char *err = NULL;
     /*  leveldb version */
  //  fprintf(stderr,"version:%d.%d\n",leveldb_major_version(),leveldb_minor_version());
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
    return 0;
}


int levelDB_write(char * key)
{
    leveldb_writeoptions_t  *woptions;
    char *err = NULL;
  /*  WRITE */
    woptions = leveldb_writeoptions_create();
    char * value = "";

    leveldb_put(db,woptions,key,strlen(key),value,strlen(value),&err);
    if ( err != NULL )
    {
        fprintf(stderr,"Write fail.\n");
        return ( EXIT_FAILURE );
    }
    fprintf(stdout,"put ok %s ...!\n",key);
    /*  reset error var */
    safe_free_leveldb(err);

    printf("Write over.\n");
    return 0;

}
/* read all*/
int levelDB_read()
{
   /*  READ */
    leveldb_readoptions_t   *roptions;
    roptions = leveldb_readoptions_create();

    /*  leveldb iterator */
    leveldb_iterator_t * iter;
    int len = 0;
    char * tmp = NULL;
    const char *key;

    iter= leveldb_create_iterator(db,roptions);

    leveldb_iter_seek_to_first(iter);
    while(leveldb_iter_valid(iter))
    {
        key = leveldb_iter_key(iter, (size_t *) &len);                                                               
        print_self("KEY",key,len);
        leveldb_iter_next(iter);
    }

    leveldb_iter_destroy(iter);
    printf("==============Read Over==================\n");
    return 0;

}

int levelDB_seek(char * seek_key)
{
    leveldb_readoptions_t   *roptions;
    roptions = leveldb_readoptions_create();

    leveldb_iterator_t * iter;
    iter= leveldb_create_iterator(db,roptions);

    size_t num = strlen(seek_key);
    size_t key_len,value_len;
    const char *key,*value;

    leveldb_iter_seek(iter,seek_key,num);

    while(leveldb_iter_valid(iter))
    {
        key = leveldb_iter_key(iter,&key_len);
        value = leveldb_iter_value(iter,&value_len);
        print_self("KEY",key,key_len);
        print_self("VALUE",value,value_len);
        leveldb_iter_next(iter);
        if(!leveldb_iter_valid(iter))
            break;
        if((!strstr(leveldb_iter_key(iter,&key_len),seek_key)))
            break;
    }

    leveldb_iter_destroy(iter);
    return 0;

}

int levelDB_delete(char * key)
{
    leveldb_writeoptions_t  *woptions;
    woptions = leveldb_writeoptions_create();
    char * err = NULL;
    leveldb_delete(db,woptions, key, strlen(key),&err );
    if ( err != NULL )
    {
        fprintf(stderr,"Delete fail.\n");
    }
return 0;
}
void levelDB_close()
{
    leveldb_close(db);
}

int levelDB_destroy()
{
//    leveldb_options_t   *options;
    char * err = NULL ;
    /*  destroy */
    leveldb_destroy_db(options,dbfile,&err);
    if ( err != NULL )
    {
        fprintf(stderr, "Destory fail.\n");
        fprintf(stderr, "Destory fail %s.\n",err);
        return ( EXIT_FAILURE );
    }
    /*  reset error var */

    safe_free_leveldb(err);
return 0;
 
}

void safe_free_leveldb(char * err) {
    leveldb_free( err );
    err = NULL;
}

void print_self(const char *type, const char *start, size_t len)
{
    printf("%s: ",type);
    for(; len>0 ; len--)
        printf("%c",*start++);

    printf("\n");
}

