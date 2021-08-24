#pragma once 

#include <list>

#include "../include/nlohmann/json.hpp"

#include "filter.hpp"
#include "filter_default.hpp"

using namespace std;
using json = nlohmann::json;

extern Filter*          filter(string name);
extern list<string>     filter_names();
extern json             filter_json();
