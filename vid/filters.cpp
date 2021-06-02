#include "filter.hpp"
#include "filter_default.hpp"
#include "filters.hpp"

FltFilters::FltFilters() {
    add("border", new FltBorder());
    add("canny", new FltCanny());
    add("gaussian", new FltGaussianBlur());
    add("smaller", new FltSmaller());
    
}

void FltFilters::add(string name, Filter* f)
{
    _filters[name] = f;
}

Filter* FltFilters::get(string name)
{
    auto it = _filters.find(name);
    if (it != _filters.end()) {
        Filter *filter = (Filter*) it->second;
        return filter;
    }
    return NULL;
}
