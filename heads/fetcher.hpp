#ifndef FETCHER_HPP
#define FETCHER_HPP
#include <string>
#include "error_handle.hpp"



namespace fetch{
    class Fetcher{
        public:
            //default, daily time series
            static void alpha_vantage(std::string&,const std::string&);
    };

}

#endif