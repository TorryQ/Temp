// 注：代码中使用的trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello仅是一个占位符应该替换为实际的trpc服务代理和方法调用
#include <trpc/client/trpc_client.h>
#include "employee_service.pb.h"

int main() {
  // 创建 tRPC 客户端上下文
  trpc::ClientContextPtr context = trpc::MakeClientContext();

  // 创建请求和响应对象
  employee::AddEmployeeRequest add_request;
  employee::AddEmployeeResponse add_response;
  employee::DelEmployeeRequest del_request;
  employee::DelEmployeeResponse del_response;
  employee::LookEmployeeRequest look_request;
  employee::LookEmployeeResponse look_response;
  employee::ModiEmployeeRequest modi_request;
  employee::ModiEmployeeResponse modi_response;
  employee::ChecktheidRequest checktheid_request;
  employee::ChecktheidResponse checktheid_response;

  // 设置 AddEmployee 请求参数
  add_request.set_id("1");
  add_request.set_name("John Doe");
  add_request.set_age(30);
  add_request.set_department("Engineering");

  // 调用 AddEmployee RPC 方法
  auto add_status = trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello(context, &add_request, &add_response);
  if (add_status.OK()) {
    std::cout << "AddEmployee response: " << add_response.success() << std::endl;
  } else {
    std::cerr << "AddEmployee failed: " << add_status.ToString() << std::endl;
  }

  // 设置 DelEmployee 请求参数
  del_request.set_id("1");

  // 调用 DelEmployee RPC 方法
  auto del_status = trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello(context, &del_request, &del_response);
  if (del_status.OK()) {
    std::cout << "DelEmployee response: " << del_response.success() << std::endl;
  } else {
    std::cerr << "DelEmployee failed: " << del_status.ToString() << std::endl;
  }

  // 设置 LookEmployee 请求参数
  look_request.set_id("1");

  // 调用 LookEmployee RPC 方法
  auto look_status = trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello(context, &look_request, &look_response);
  if (look_status.OK()) {
    std::cout << "LookEmployee response: " << look_response.DebugString() << std::endl;
  } else {
    std::cerr << "LookEmployee failed: " << look_status.ToString() << std::endl;
  }

  // 设置 ModiEmployee 请求参数
  modi_request.set_id("1");
  modi_request.set_field("age");
  modi_request.set_value("31");

  // 调用 ModiEmployee RPC 方法
  auto modi_status = trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello(context, &modi_request, &modi_response);
  if (modi_status.OK()) {
    std::cout << "ModiEmployee response: " << modi_response.success() << std::endl;
  } else {
    std::cerr << "ModiaEmployee failed: " << modi_status.ToString() << std::endl;
  }

  // 设置 Checktheid 请求参数
  checktheid_request.set_name("John Doe");

  // 调用 Checktheid RPC 方法
  auto checktheid_status = trpc::test::helloworld::GreeterServiceProxy::GetInstance()->SayHello(context, &checktheid_request, &checktheid_response);
  if (checktheid_status.OK()) {
    std::cout << "Checktheid response: " << checktheid_response.DebugString() << std::endl;
  } else {
    std::cerr << "Checktheid failed: " << checktheid_status.ToString() << std::endl;
  }

  return 0;
}