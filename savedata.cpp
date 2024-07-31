//savedata.cpp
#include<iostream>
#include<fstream>
#include<nlohmann/json.hpp>
#include<iomanip>

using json = nlohmann::json;

int main()
{
    json employees = R"(
    [
        {"name":"Alice", "age":26, "department":"Sales"},
        {"name":"Bob", "age":30, "department":"Marketing"},
        {"name":"Kelly","age":33,"department":"IT"}
    ]
    )"_json;
    
    json companyInfo = R"(
    {
        "name":"AAA",
        "location":"New York",
        "establishedYear":1990
    }
    )"_json;

    json projects = R"(
    [
        {"name":"projectA", "category":"Research", "budget":500000},
        {"name":"projectB", "category":"Develop", "budget":1000000}
    ]
    )"_json;

    json data;
    data["employees"] = employees ;
    data["companyInfo"] = companyInfo ;
    data["projects"] = projects ;
    
    std::ofstream file ("data.json");
    if(file.is_open()) {
        file << std::setw(4) << data << std::endl;
        file.close();
        std::cout << "The data has been saved to data.json" << std::endl;
    }
    else 
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
    return 0;
}