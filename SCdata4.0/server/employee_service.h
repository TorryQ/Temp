//定义服务接口
#ifndef EMPLOYEE_SERVICE_H
#define EMPLOYEE_SERVICE_H

#include <string>

namespace employee {

class EmployeeService {
public:
    virtual ~EmployeeService() {}
    virtual void AddEmployee(const std::string& id, const std::string& name, int age, const std::string& department) = 0;
    virtual void DelEmployee(const std::string& id) = 0;
    virtual void LookEmployee(const std::string& id) = 0;
    virtual void ModiEmployee(const std::string& id, const std::string& field, const std::string& value) = 0;
    virtual void Checktheid(const std::string& name) = 0;
};

} // namespace employee

#endif // EMPLOYEE_SERVICE_H