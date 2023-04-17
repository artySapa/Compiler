//// NameTable.cpp
//
//#include "NameTable.h"
//#include <string>
//#include <vector>
//#include <list>
//#include <iostream>
//#include <functional>
//using namespace std;
//
//class HashTable
//{
//public:
//    HashTable()
//    {
//        //buckets = new Bucket*[20000];
//    }
//    ~HashTable()
//    {
//        for(int i = 0; i < declared.size(); i++)
//        {
//            int p = find(declared[i]);
//            if (p != -1)
//                remove(declared[i]);
//        }
//    }
//
//    bool insert(string s, int lineNum)
//    {
//        if(find(s) != -1)
//            return false;
//
//        int index = hashFunc(s);
//        /*Bucket* temp = new Bucket;
//        temp->s = s;
//        temp->line = lineNum;
//        temp->next = nullptr;
//        if(buckets[index] != nullptr)
//            temp->next = buckets[index]->next;
//        buckets[index] = temp;
//        delete temp;*/
//        nItems++;
//        buckets[index] = new Bucket;
//        buckets[index]->s = s;
//        buckets[index]->line = lineNum;
//        buckets[index]->next = nullptr;
//        declared.push_back(s);
//
//        return true;
//
//    }
//
//    int find(string s) const
//    {
//        int index = hashFunc(s);
//
//        Bucket* bucket = buckets[index];
//
//        if(bucket == nullptr)
//            return -1;
//
//        if(bucket->s == s)
//        {
//            return bucket->line;
//        }
//
//        /*while(bucket != nullptr)
//        {
//            if(bucket->s == s)
//            {
//                return bucket->line;
//            }
//            bucket = bucket->next;
//        }*/
//
//        return -1;
//    }
//
//    bool remove(string s)
//    {
//        int index = hashFunc(s);
//        Bucket* bucket = buckets[index];
//
//        if(find(s) == -1)
//            return false;
//        else
//        {
//            //delete bucket;
//            buckets[index] = nullptr;
//            nItems--;
//            /*while(bucket != nullptr)
//            {
//                if(bucket->s == s)
//                {
//                    buckets[index] = bucket->next;
//                    delete bucket;
//                    nItems--;
//                    return true;
//                }
//                bucket = bucket->next;
//            }*/
//        }
//
//        return false;
//    }
//
//    void clear()
//    {
//        for(int i = 0; i < declared.size(); i++)
//        {
//            remove(declared[i]);
//        }
//    }
//
//    int size() const
//    {
//        return nItems;
//    }
//
//    int hashFunc(string s) const
//    {
//        /*unsigned int h = 2166136261u;
//        for(size_t i = 0; i < s.size(); i++)
//        {
//            char c = s[i];
//            h += c;
//            h *= 16777619;
//            h %= 19999;
//        }
//        return h;*/
//    /*int i, total=0;
//
//    for (i=0; i<s.length() ; i++)
//        total = total + (i+1) * s[i];
//
//    return(total%19999);*/
//
//        unsigned int x = std::hash<string>()(s) % 19999;
//        return x;
//
//    }
//
//private:
//    struct Bucket
//    {
//        string s;
//        int line = -1;
//        Bucket* next = nullptr;
//    };
//
//    vector<string> declared;
//
//    Bucket* buckets[20000] = {nullptr};
//    //Bucket** buckets;
//    int nItems = 0;
//};
//
//  // This class does the real work of the implementation.
//
//class NameTableImpl
//{
//  public:
//    NameTableImpl();
//    ~NameTableImpl();
//    void enterScope();
//    bool exitScope();
//    bool declare(const string& id, int lineNum);
//    int find(const string& id) const;
//  private:
//    vector<HashTable> hashes;
//    int latest = -1;
//};
//
//NameTableImpl::NameTableImpl()
//{
//    enterScope();
//}
//
//NameTableImpl::~NameTableImpl()
//{
//    exitScope();
//}
//
//void NameTableImpl::enterScope()
//{
//    latest++;
//    HashTable p;
//    hashes.push_back(p);
//}
//
//bool NameTableImpl::exitScope()
//{
//
//    if (latest == 0)
//        return false;
//
//    //delete hashes[latest];
//    //hashes[latest].clear();
//    hashes.pop_back();
//    latest--;
//    return true;
//}
//
//bool NameTableImpl::declare(const string& id, int lineNum)
//{
//    //assert(hashes[latest] == nullptr);
//    return hashes[latest].insert(id, lineNum);
//}
//
//int NameTableImpl::find(const string& id) const
//{
//    // take track of the variables that are already defined somewhere
//
//    for(int i = latest; i > -1; i--)
//    {
//        if(hashes[i].find(id) != -1)
//        {
//            return hashes[i].find(id);
//        }
//    }
//
//    return -1;
//}
//
////*********** NameTable functions **************
//
//// For the most part, these functions simply delegate to NameTableImpl's
//// functions.
//
//NameTable::NameTable()
//{
//    m_impl = new NameTableImpl;
//}
//
//NameTable::~NameTable()
//{
//    delete m_impl;
//}
//
//void NameTable::enterScope()
//{
//    m_impl->enterScope();
//}
//
//bool NameTable::exitScope()
//{
//    return m_impl->exitScope();
//}
//
//bool NameTable::declare(const string& id, int lineNum)
//{
//    return m_impl->declare(id, lineNum);
//}
//
//int NameTable::find(const string& id) const
//{
//    return m_impl->find(id);
//}
