#include "UserInterface.hpp"
#include <iostream>

using namespace std;

const int main(const int argc, const char* const* const argv){
#ifdef _DEBUG
	for(size_t i(0), end(static_cast<size_t>(argc)); i < argc; ++i){
		cout << argv[i] << endl;
	}
#endif

	try{
		UserInterface ui;
		while(ui.isEnable()){
			ui.updateWindow();
		}
	}
	catch(const runtime_error& error){
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}