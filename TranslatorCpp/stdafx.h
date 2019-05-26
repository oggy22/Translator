#pragma once

#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <experimental/generator>

#ifdef _DEBUG
#include <set>
#include <map>
#define myset std::set
#define map std::map
#else
#include <unordered_set>
#include <unordered_map>
#define myset std::unordered_set
#define map std::unordered_map
#endif

#include "parsing_triangle.h"
#include "Assert.h"