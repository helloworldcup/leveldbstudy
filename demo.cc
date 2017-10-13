#include <cassert>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <algorithm>
using std::transform;

#include <functional>
using std::ptr_fun;

#include <cctype>

#include "leveldb/db.h"

int main(){
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status s = leveldb::DB::Open(options, "/tmp/testdb", &db);
    if(!s.ok()){
        cerr << s.ToString() << endl;
        exit(1);
    }

    string key1 = "foobar";
    s = db->Put(leveldb::WriteOptions(), key1, "1");
    cout << "stat:" << s.ToString() << endl;

    leveldb::ReadOptions options1;
    options1.snapshot = db->GetSnapshot();
    string value1;
    s = db->Get(options1, key1, &value1);
    cout << "stat:" << s.ToString() << endl;
    cout << "value=" << value1 << endl;

    s = db->Put(leveldb::WriteOptions(), key1, "111");
    cout << "stat:" << s.ToString() << endl;
    value1.resize(0);
    s = db->Get(leveldb::ReadOptions(), key1, &value1);
    cout << "stat:" << s.ToString() << endl;
    cout << "value=" << value1 << endl;

    value1.resize(0);
    s = db->Get(options1, key1, &value1);
    cout << "stat:" << s.ToString() << endl;
    cout << "value=" << value1 << endl;

    if(db != nullptr){
        delete db;
    }
    cout << "delete db" << endl;
    return 0;
}