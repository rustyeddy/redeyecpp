#pragma once

#include <string>

using namespace std;

class Config
{
private:
    string _fname;

public:
    string      get_fname() { return _fname; }
    void        set_fname(string s) { _fname = s; }
};
