//modifydata.cpp
#include<iostream>
#include<fstream>
#include<nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::ifstream file("data.json");
    if(!file.is_open()){
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }
    std::string json_str((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    file.close();

    json all_data = json::parse(json_str);
    json employees_data = all_data["employees"];
    json companyInfo_data = all_data["companyInfo"];
    json projects_data = all_data["projects"];

    json new_employee_data = R"(
    {{"name":"Alex"}, {"age":25}, {"department":"Marketing"}}
    )"_json

    employees_data.pushback(new_employee_data);

    all_data["employees"] = employees_data ;
    all_data["companyInfo"] = companyInfo_data ;
    all_data["projects_data"] = projects_data ;

    std::string updated_all_data = all_data.dump(4);

    std::ofstream outfile ("data.json");
    if(!outfile.is_open()){
        std::cerr << "Unable to open file"  << std::endl;
        return 1;
    }
    outfile << updated_all_data ;
    outfile.close();

    std::cout << "The information is updated" << std::endl;
    return 0;
}