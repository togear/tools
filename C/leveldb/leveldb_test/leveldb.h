#ifndef LEVEDB_H
#define LEVEDB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <leveldb/c.h>
static leveldb_t *db;
static leveldb_options_t       *options;
static const char* dbfile  = "/tmp/leveldbtest";

void safe_free_leveldb(char * err);

int levelDB_init();
int levelDB_read();
int levelDB_write(char * key);
int  levelDB_seek(char * seek_key);
int levelDB_delete(char * key);

void levelDB_close();
int levelDB_destroy();




#endif
