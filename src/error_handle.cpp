#include "../heads/error_handle.hpp"



bool handle::Checker::dpython3(){
    return !(system("python3 --version > /dev/null 2>&1"));
}

bool handle::Checker::av_json(const std::string& stock_name){
    std::ifstream file("fetched_data/"+stock_name+".json");
    if(!(file.is_open())){
        std::cerr<<"Fetched data file cannot be located"<<std::endl;
        return false;
    }
    nlohmann::json jData = nlohmann::json::parse(file);
  //  file >> jData;
    std::string buffor;
    for(auto it = jData.begin(); it!=jData.end(); ++it){
        if(it.key() == "Error Message"){
            std::cerr<<stock_name<<".json \"Error\": "<<it.value()<<std::endl;
            return false;
        }
    }
    return true;
}
