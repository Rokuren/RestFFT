
#include "server.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener; // HTTP Server

int main() {
	
	http_listener listener(L"http://localhost:18080/transform");

	listener.support(methods::GET, handle_get);
	listener.support(methods::POST, handle_post);
	//listener.support(methods::PUT, handle_put);
	//listener.support(methods::DEL, handle_del);

	try {
		listener.open().then([&listener]() {
			ucout << "Server Started\n";
		}).wait();
		
		while (true);
	}
	catch (http_exception e){
		listener.close();
		ucout << "An exception occured. Could not open listener";
	}
	


	listener.close();

    std::cout << "Hello,World\n";
	return 0;
}
