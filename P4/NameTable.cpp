// NameTable.cpp

// on Xcode it gives 15-16 msec on Average

#include "NameTable.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <functional>
using namespace std;

class HashTable
{
public:

    bool insert(const string& s, const int& lineNum, const int& scope)
    {
        int index = hashFunc(s);

        if(!buckets[index].empty())
        {
            list<Bucket>::const_iterator p = buckets[index].begin();
            while(p != buckets[index].end())
            {
                if(p->scope == scope && p->s == s)
                    return false;
                p++;
            }
        }

        Bucket temp;
        temp.s = s;
        temp.line = lineNum;
        temp.scope = scope;

        buckets[index].push_front(temp);

        return true;

    }

    int find(const string& s) const
    {
        int index = hashFunc(s);

        if(buckets[index].empty())
            return -1;

        list<Bucket>::const_iterator p = buckets[index].begin();

        while(p != buckets[index].end())
        {
            if(p->s == s)
                return p->line;
            p++;
        }

        return -1;
    }

    bool remove(const string& s)
    {
        int index = hashFunc(s);

        if(buckets[index].empty())
            return false;

        buckets[index].pop_front();

        return false;
    }

    int hashFunc(const string& s) const
    {
        unsigned int x = std::hash<string>()(s) % 19997;
        return x;
    }

private:
    struct Bucket
    {
        string s;
        int line = -1;
        int scope = 0;
    };

    list<Bucket> buckets[19998]; // push_front

};

  // This class does the real work of the implementation.

class NameTableImpl
{
  public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, const int& lineNum);
    int find(const string& id) const;
  private:
    HashTable hash;
    vector<vector<string>> scopes;
    int latest = 0;
};

void NameTableImpl::enterScope()
{
    vector<string> newScope;
    scopes.push_back(newScope);
    latest++;
}

bool NameTableImpl::exitScope()
{
    if(scopes.size() == 1)
        return false;

    for(int i = 0; i < scopes[latest].size(); i++)
    {
        hash.remove(scopes[latest][i]);
    }

    latest--;
    scopes.pop_back();
    return true;
}

bool NameTableImpl::declare(const string& id, const int& lineNum)
{
    if(scopes.empty())
    {
        vector<string> newScope;
        scopes.push_back(newScope);
    }

    if(!hash.insert(id, lineNum, latest))
        return false;

    scopes[latest].push_back(id);
    return true;
}

int NameTableImpl::find(const string& id) const
{
    return hash.find(id);
}

//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}

