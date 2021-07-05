#pragma once 

#include "filter.hpp"
#include "filter_default.hpp"

class FltFilters
{
private:
    map<string,Filter*> _filters;

public:
    FltFilters();

    void add(string name, Filter* f);
    Filter* get(string name);
};
