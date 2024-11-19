#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <fstream>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>

struct StockData{
    std::string date;
    float open;
    float high;
    float low;
    float close;
    int volume;
};

//Json series interpreter for "Company" class
namespace Parse{

    class Json{
        public:
            static std::vector<StockData> js_invoke(const std::string&);
        
    };
}

#endif