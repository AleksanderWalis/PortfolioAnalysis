#include "../heads/fetcher.hpp"


void fetch::Fetcher::alpha_vantage(std::string& key_, const std::string& symbol_){
    if(!(handle::Checker::dpython3())){
        std::cerr<<"REQUEST FAILURE: Python3 not defined"<<std::endl;
        return;
    }
    std::string input_;
    //In addition reserve 20 for initial command and 2 for ", "
    input_.reserve(key_.size() + symbol_.size() + 2 + 20);
    input_ = "python3 get_data.py " + key_ + + ", " +symbol_;
    system(input_.c_str());
}