#include "../heads/interpreter.hpp"

std::vector<StockData> Parse::Json::js_invoke(const std::string& file_name){
    std::ifstream file("fetched_data/"+file_name+".json");
    if(!(file.is_open())){ 
        std::cerr<<"Cannot locate data for given name"<<std::endl;
        return {};
    }
    nlohmann::json jData;

    //FIX THIS
    file >> jData; 

    file.close();

    const nlohmann::json & timeSeries = jData["Time Series (Daily)"];
    std::vector<StockData> v;
    v.reserve(timeSeries.size());

    for(auto it = timeSeries.begin(); it!=timeSeries.end(); ++it){
        try{
        const nlohmann::json& Info = it.value();
        v.emplace_back(StockData{
            it.key(),
            std::stof(Info.at("1. open").get<std::string>()),
            std::stof(Info.at("2. high").get<std::string>()),
            std::stof(Info.at("3. low").get<std::string>()),
            std::stof(Info.at("4. close").get<std::string>()),
            std::stoi(Info.at("5. volume").get<std::string>()),
        });
        }catch(const std::exception& e){
            std::cerr<<"Failure loading chunck of data <"<<it.key()<<">"<<std::endl;
            continue;
        }
    }
    std::reverse(v.begin(), v.end());
    return v;
}