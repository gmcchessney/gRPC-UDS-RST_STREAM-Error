#include <iostream>
#include <cstdlib>
#include "grpcpp/grpcpp.h"
#include "greeter.grpc.pb.h"

int main()
{
	putenv("GRPC_VERBOSITY=DEBUG");
	putenv("GRPC_TRACE=tcp,http");

	std::string serviceEndpoint("unix:/run/my_app.sock");

	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(serviceEndpoint, grpc::InsecureChannelCredentials());
	std::shared_ptr<greet::Greeter::Stub> greeterClient = greet::Greeter::NewStub(channel);

	grpc::ClientContext context;
	greet::HelloRequest request;
	request.set_name("User1");

	greet::HelloReply response;
	grpc::Status status = greeterClient->SayHello(&context, request, &response);

	if (!status.ok())
	{
		std::cout << "Request Failed: " << status.error_message().c_str();
	}
	else
	{
		std::cout << "Request Succeeded: " << response.message().c_str();
	}

	return 1;
}