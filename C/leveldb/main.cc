/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年09月02日 05时11分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  yong.huang (gk), yong.huang@ngaa.com.cn
 *   Organization:  
 *
 *  g++ main.cc -lleveldb  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "leveldb/db.h"
#include <iostream>

using namespace std;

int main()
{
    leveldb::DB *db;
    leveldb::Options option;

    option.create_if_missing = true;
    leveldb::DB::Open(option, "/tmp/leveldb_t", &db);

    string key = "Name";
    string value = "Like";
    db->Put(leveldb::WriteOptions(), key, value);

    key = "Major";
    value = "Computer Science and Technology";
    db->Put(leveldb::WriteOptions(), key, value);


    string ret_s;
    db->Get(leveldb::ReadOptions(), "Name", &ret_s);
    cout << "key = Name" << endl
        << "value = " << ret_s << endl;

    db->Get(leveldb::ReadOptions(), "Major", &ret_s);
    cout << "key = Major" << endl
        << "value = " << ret_s << endl;

    delete db;
    return 0;
}
