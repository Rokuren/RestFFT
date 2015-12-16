
#include "server.h"

using namespace std;
using namespace utils;
using namespace fftwpp;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener; // HTTP Server

int main() {
	
	http_listener listener("http://localhost:18080/transform");

	listener.support(methods::GET, handle_get);
	listener.support(methods::POST, handle_post);
	//listener.support(methods::PUT, handle_put);
	//listener.support(methods::DEL, handle_del);

	try {
		listener.open().then([&listener]() {
			ucout << "Server Started\n";
		}).wait(); // TODO look into if I have time; not waitng
		
		this_thread::sleep_for(chrono::seconds(30));
	}
	catch (http_exception e){
		listener.close();
		ucout << "An exception occured. Could not open listener";
	}
	


	listener.close();

	std::cout << "Huzzah\n";
	return 0;
}

void handle_get(http_request request) {
	ucout << "handle get";
}

// curl --header "Content-Type:application/octet-stream" --data-binary @spiderman.png http://localhost:18080/transform > out.cplx
void handle_post(http_request request) {
	vector<unsigned char> vec; // vector from request body
	vector<unsigned char> outvec; // reply vector
	vector<unsigned char> image; // raw pixels after decode
	std::complex<float> complexArray[12000];
	unsigned char rgba[4];
	unsigned width, height;
	lodepng::State state; 

	ucout << "Handle post\n";
	request.content_ready();
	this_thread::sleep_for(chrono::seconds(3));
	ucout << "Content Ready\n";

	//concurrency::streams::istream is
	/*auto i = request.body();
	int n = 3;
	 while (i >> n) {
	 ucout << n;
	} */
	/*vec = request.extract_vector().get();
	
	std::stringstream result;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<unsigned char>(result, " "));

	

	string c = result.str();
	
	//unsigned char* arr = new unsigned char[vec.size];
	ImageArray array;
	*/
	vec = request.extract_vector().get();
	height = 120;
	width = 100;
	lodepng::decode(image, width, height, state, vec);

	ucout << image.size(); // size is 48000 for png with height = 120; width = 100; and rgba(4)
	ucout << "\n";
	
	// convert rgba to complex
	for (int x = 0; x < image.size() - 1; x += 4) {

		rgba[0] = image[x];
		rgba[1] = image[x + 1];
		rgba[2] = image[x + 2];
		rgba[3] = image[x + 3];
		
		complexArray[x / 4] = pack_color(rgba);
		
	}

	ucout << "Hello, there\n";  

	// FFT on complex array
	// n complex values, -1, in, out
	Complex *in = ComplexAlign(12000);
	Complex *out = ComplexAlign(12000);

	// Ok let's try moving complexAray to *in
	for(int x = 0; x < 12000; x++) {
		in[x] = complexArray[x];
	}

	fft1d Forward(12000, -1, in, out);
	// Return FFT

	//std::copy(vec.begin(), vec.end(), arr);
	//request.reply(status_codes::OK, arr);
	std::complex<float> data[12000];

	concurrency::streams::istream body;
	

	//body.read_to_end(out);
	for(int x = 0; x < 12000; x++){
	//	outvec.insert(out[x]);
	}

	// Gah, I need to do something about this Complex*&
	//lodepng::encode(outvec, out, width, height, state);

	http_response response(status_codes::OK);
	
	// just returning the original image for now
	response.set_body(vec);
	
	request.reply(response).wait();

	
}

float pack_color(unsigned char rgba[4])
{
	union { float f; unsigned char rgba[4]; } u;
	u.rgba[0] = rgba[0];
	u.rgba[1] = rgba[1];
	u.rgba[2] = rgba[2];
	u.rgba[3] = rgba[3];
	return u.f;
}

