#include "../heads/company.hpp"

static const std::unordered_map<std::string, float StockData::*> & getFieldMap(){
    static const std::unordered_map<std::string, float StockData ::*>& ref={
        {"Open", &StockData::open},
        {"Close", &StockData::close},
        {"High", &StockData::high},
        {"Low", &StockData::low}
    };
    return ref;
}


Company::Company(const std::string& stock_symbol, const bool& check){
    this->stock_name= stock_symbol;
    this->data = std::move(Parse::Json::js_invoke(stock_symbol));
    if(check){
    if(!(handle::Checker::av_json(stock_symbol))){
        this->data = {};
        std::string f = "rm fetched_data/"+stock_symbol+".json";
        system(f.c_str());
    }
    }
}

Company::~Company(){}

void Company::display(short int n) const {
    if(this->data.size() == 0){
        std::cerr<<"Display error: Company data is emtpy"<<std::endl;
        return;
    }
    if(n < 0 || n > this->data.size())
        n=this->data.size();
    std::cout<<std::left<<std::setw(12)<<"Date"
    <<std::setw(9)<<"High"
    <<std::setw(9)<<"Low"
    <<std::setw(9)<<"Open"
    <<std::setw(9)<<"Close"
    <<std::setw(9)<<"Vol."
    <<std::endl;
    for(int i = 0; i<n; i++){
        std::cout<<std::setw(12)<<std::fixed<<std::setprecision(2)<<this->data[i].date
        <<std::setw(9)<<std::fixed<<std::setprecision(2)<<this->data[i].high
        <<std::setw(9)<<std::fixed<<std::setprecision(2)<<this->data[i].low
        <<std::setw(9)<<std::fixed<<std::setprecision(2)<<this->data[i].open
        <<std::setw(9)<<std::fixed<<std::setprecision(2)<<this->data[i].close
        <<std::setw(9)<<std::fixed<<std::setprecision(2)<<this->data[i].volume
        <<std::endl;
    }
}




void Company::gdisplay(short int n, const std::string& select_) const{

     auto fieldMap = getFieldMap();
     auto it = fieldMap.find(select_);
     if(it==fieldMap.end()){
        std::cerr<<"gDisplay error: invalid selection"<<std::endl;
        return;
     }
     if(this->data.size() == 0){
        std::cerr<<"gDisplay error: Company data is emtpy"<<std::endl;
        return;
    }
    n = (n < 0 || n > this->data.size()) ? this->data.size() : 0;
    FILE* gnuplotPipe = popen("gnuplot -p", "w");
    if(!gnuplotPipe){
        throw std::runtime_error("Cannot open gnuplot pipe");
	    return;
    }
    std::string * title = new std::string;
    *title = "set title '" +this->stock_name + " " + select_ + " Prices Over Time'\n";
    fprintf(gnuplotPipe, title->c_str());
    delete title;
    fprintf(gnuplotPipe, "set xdata time\n");
    fprintf(gnuplotPipe, "set timefmt '%%Y-%%m-%%d'\n");
    fprintf(gnuplotPipe, "set format x '%%Y-%%m-%%d'\n");
    fprintf(gnuplotPipe, "set xlabel 'Date'\n");
    fprintf(gnuplotPipe, "set ylabel 'Price'\n");
    fprintf(gnuplotPipe, "plot '-' using 1:2 with lines title 'Price'\n");
    for (size_t i = this->data.size(); i > 0; --i)
      fprintf(gnuplotPipe, "%s %f\n", this->data[i-1].date.c_str(), this->data[i-1].*(it->second));

    fprintf(gnuplotPipe, "e\n");
    pclose(gnuplotPipe);
    
}
static int counter{};
void* operator new(size_t n){
    counter++;
    return malloc(n);
}
double Company::stock_status(const short int& days, const std::string& select_) const{
    if(days < 1 || days > this->data.size())
    {
        std::cerr<<"Invalid \'days\' selection. Got "<<days<<". Expected \'days\' in {1, ...,"<<this->data.size()<<"}"<<std::endl;
        return 0.0;
    }
    const auto& field_map = getFieldMap();
    const auto& it = field_map.find(select_);
    if(it == field_map.end()){
        std::cerr<<"stock_status error: invalid selection"<<std::endl;
        return 0.0;
    }
    return (this->data[0].*(it->second) - this->data[days-1].*(it->second))/this->data[0].*(it->second);
}
