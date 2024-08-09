#include "employee_service.h"
#include <trpc/trpc.h>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include "cppconn/statement.h"
#include "cppconn/resultset.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"

using sql::mysql::MySQL_Driver;
using sql::Connection;
using sql::Statement;
using sql::PreparedStatement;
using sql::ResultSet;
using sql::SQLException;

class Employee {
 private:
  int age;
  string name, id, department;
 public:
  void Add_Employee(Connection *con, const Employee &A);
  void Del_Employee(Connection *con, const string del_id);
  void Look_Employee(Connection *con, const string look_id);
  void Modi_Employee(Connection *con, const string modi_id);
  void Check_the_id(Connection *con, const string checkname);
};

void Employee::Add_Employee(Connection *con, const Employee &A) {
    try {
        std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement("INSERT INTO employees (name, age, id, department) VALUES(?,?,?,?)"));
        pstmt->setString(1, A.name);
        pstmt->setInt(2, A.age);
        pstmt->setString(3, A.id);
        pstmt->setString(4, A.department);
        pstmt->executeUpdate();
    } catch (SQLException &e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void Employee::Del_Employee(Connection *con, const string del_id) {
    try {
        std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement("DELETE FROM employees WHERE id = ?"));
        pstmt->setString(1,del_id);
        pstmt->executeUpdate();
    } catch (SQLException &e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void Employee::Look_Employee(Connection *con, const string look_id) {
  try {
    std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement("SELECT id, name, age, department FROM employees WHERE id = ?"));
    pstmt->setString(1, look_id);
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    while(res->next())
    {
      string Id = res->getString("id");
      string Name = res->getString("name");
      int Age = res->getInt("age");
      string Department = res->getString("department");
      cout << "Find this employee" << endl << "id: " << Id << endl << "name: " << Name << endl << "age: " << Age << endl << " department: " << Department << endl;
    }
  } catch (SQLException &e) {
    cout << "SQL Error: " << e.what() << endl;
  }
}

void Employee::Modi_Employee(Connection *con, const string modi_id) {
  try {
    string opt1, opt2;
    cout << "Which data do you want to change?" << endl;
    cin >> opt1;
    cout << "You want to change it to " << endl;
    cin >> opt2;
    string query = "UPDATE employees SET " + opt1 + " = ? WHERE id = ?";
    std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement(query));
    pstmt->setString(1, opt2);
    pstmt->setString(2, modi_id);
    pstmt->executeUpdate();
  } catch (SQLException &e) {
    cout << "SQL Error: " << e.what() << endl;
  }
}

void Employee::Check_the_id(Connection *con, const string checkname) 
{
  try {
    std::unique_ptr<PreparedStatement> pstmt(con->prepareStatement("SELECT id, department FROM employees WHERE name = ?"));
    pstmt->setString(1, checkname);
    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
    while(res->next())
    {
      string Id = res->getString("id");
      string Department = res->getString("department");
      cout << "id: " << Id << " department: " << Department << endl;
    }
  } catch (SQLException &e) {
    cout << "SQL Error: " << e.what() << endl;
  }
}

::trpc::Status EmployeeServiceImpl::AddEmployee(::trpc::ServerContextPtr context,
                                               const employee::AddEmployeeRequest* request,
                                               employee::AddEmployeeResponse* response) 
{
  Employee A;
  A.id = request->id();
  A.name = request->name();
  A.age = request->age();
  A.department = request->department();
  A.Add_Employee(con.get(), A);
  response->set_success(true);
  return ::trpc::kSuccStatus;
}

::trpc::Status EmployeeServiceImpl::DelEmployee(::trpc::ServerContextPtr context,
                                               const employee::DelEmployeeRequest* request,
                                               employee::DelEmployeeResponse* response) 
{
  Employee().Del_Employee(con.get(), request->id());
  response->set_success(true);
  return ::trpc::kSuccStatus;
}

::trpc::Status EmployeeServiceImpl::LookEmployee(::trpc::ServerContextPtr context,
                                                const employee::LookEmployeeRequest* request,
                                                employee::LookEmployeeResponse* response) 
{
  Employee().Look_Employee(con.get(), request->id());
  response->set_id(response->id());
  response->set_name(response->name());
  response->set_age(response->age());
  response->set_department(response->department());
  return ::trpc::kSuccStatus;
}

::trpc::Status EmployeeServiceImpl::ModiEmployee(::trcpp::ServerContextPtr context,
                                                 const employee::ModiEmployeeRequest* request,
                                                 employee::ModiaEmployeeResponse* response) 
{
  Employee().Modi_Employee(con.get(), request->id());
  response->set_succuess(true);
  return ::trpc::kSuccStatus;
}

::trpc::Status EmployeeServiceImpl::Checktheid(::trpc::ServerContextPtr context,
                                               const employee::ChecktheidRequest* request,
                                               employee::ChecktheidResponse* response) 
{
  Employee().Check_the_id(con.get(), request->name());
  response->set_id(response->id());
  response->set_department(response->department());
  return ::trpc::kSuccStatus;
}