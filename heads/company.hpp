#ifndef COMPANY_HPP
#define COMPANY_HPP
#include <string>
#include <vector>
#include <stdexcept>
#include "interpreter.hpp"
#include "error_handle.hpp"
#include <unordered_map>

class Company{
    private:
        std::string stock_name;
        std::vector<StockData> data;
    public:
        Company(const std::string&, const bool&);
        ~Company();
        //terminal display
        void display(short int) const;

        //graph display
        void gdisplay(short int, const std::string&) const;

        //stock status
        double stock_status(const short int&, const std::string&) const;
};

#endif