#include<iostream>
#include<string>
#include<nlohmann/json.hpp>
#include<iomanip>
#include<fstream>
#include<sstream>

using json = nlohmann::json;

json all_data;
json employees_data, companyInfo_data, projects_data;

void open()
{
    using namespace std;
    cout << "SCdata command line tool is a simulative company data management system, which is used to modify the data of the simulative company" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Usage:" << endl << "SCdata [command]" << endl;
    cout << "Available Commands:" << endl;
    cout << "\tAddEmployee\tAddEmployee [ID name age department]" << endl;
    cout << "\tDelEmployee\tDelEmployee [ID]" << endl;
    cout << "\tLookEmployee\tLookEmployee [ID]" << endl;
    cout << "\tModiEmployee\tModiEmployee [ID]" << endl;
    cout << "\tChecktheid\tChecktheid [name]" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    return ;
}
void splitdata()
{
    employees_data = all_data["employees"];
    companyInfo_data = all_data["companyInfo"];
    projects_data = all_data["projects"];
    return ;
}
void sumdata()
{
    all_data["employees"] = employees_data;
    all_data["companyInfo"] = companyInfo_data;
    all_data["projects"] = projects_data;
    return ;
}
void Add_Employee(const std::string& ID, const std::string& name, int age, const std::string& depart)
{
    json new_employee;
    new_employee["ID"] = ID ; //to do:员工id通过hash生成，并检查冲突，确保id的唯一性
    new_employee["name"] = name ;
    new_employee["age"] = age ;
    new_employee["department"] = depart ;
    employees_data.push_back(new_employee);
    return ;
}

void Del_Employee(const std::string& ID)
{
    employees_data.erase(std::remove_if(employees_data.begin(), employees_data.end(),
    [ID](const json& employee) { return employee["ID"] == ID; }),
    employees_data.end()
    );
    return ;
}

json Look_Employee(const std::string& ID) 
{
    for (const auto& employee : employees_data) 
    {
        if (employee["ID"] == ID) 
        {
            return employee;
        }
    }
    return json::object();
}

void Modi_Employee(const std::string& ID) 
{
    bool found = false;
    for (auto& employee : employees_data) 
    {
        if (employee["ID"] == ID) 
        {
            found = true;
            std::cout << "Which data do you want to change?(name/age/department): ";
            std::string tmpstr;
            std::cin >> tmpstr;
            std::cout << "Now the " << tmpstr << " is " << employee[tmpstr] << ". It will be changed to: ";
            std::string newdata;
            std::cin >> newdata;
            employee[tmpstr] = newdata;
            return;
        }
    }
    if (!found) 
    {
        std::cout << "Employee with ID: " << ID << " not found." << std::endl;
    }
}

void Check_the_ID(const std::string& name) 
{
    bool found = false;
    for (const auto& employee : employees_data) 
    {
        if (employee["name"] == name)
        {
            std::cout << "Department: " << employee["department"] << ", ID: " << employee["ID"] << std::endl;
            found = true;
        }
    }
    if (!found) 
    {
        std::cout << "Not find " << name << " in this company" << std::endl; 
    }
}

int main()
{
    try{
        std::ifstream file("data.json");
        if(!file.is_open())
        {
            throw std::ios_base::failure("Unable to open file: data.json");
        }
        else
        {
            open();
            std::string json_str((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
            file.close();
            all_data = json::parse(json_str);
            splitdata();
            std::string input;
            std::getline(std::cin, input);
            std::istringstream iss(input);
            std::string st;
            iss >> st;
            if (st == "AddEmployee")
            {
                std::string strI, strN, strD;
                int strA;
                iss >> strI >> strN >> strA >> strD; //todo 输入验证
                Add_Employee(strI,strN,strA,strD); 
            }else if(st == "DelEmployee")
            {
                std::string strI;
                iss >> strI;
                Del_Employee(strI); 
            }else if(st == "LookEmployee")
            {
                std::string strI;
                iss >> strI;
                json res = Look_Employee(strI);
                if(res.empty())
                {
                    std::cout << "not find this employee" << std::endl; 
                }
                else 
                {
                    std::cout << res.dump(4) << std::endl;
                }
            }else if(st == "ModiEmployee")
            {
                std::string strI;
                iss >> strI;
                Modi_Employee(strI);
            }else if(st == "Checktheid")
            {
                std::string strN;
                iss >> strN;
                Check_the_ID(strN);
            }else
            {
                std::cout << "Unknown command, please try again";
            }
            sumdata();
            std::string updated_all_data = all_data.dump(4);
            std::ofstream outfile ("data.json");
            if(!outfile.is_open())
            {
                throw std::ios_base::failure("Unable to open file: data.json");
            }
            else
            {
                outfile << updated_all_data;
                outfile.close();
                std::cout << "The information is updated" << std::endl;
            }
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << "File I/O error: " << e.what() << std::endl;
        return 1;
    }
    catch(const json::parse_error& e) 
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error:" << e.what() << std::endl;
        return 1;
    }
    return 0;
}