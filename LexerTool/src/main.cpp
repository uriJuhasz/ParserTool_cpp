#include <iostream>
#include <vector>
using namespace std;

#include "lexer/test/CharSetTester.h"

int main(int argc, char* argv[]) {
	cout << "Start" << endl;
	auto args = vector<string>(argv,argv+argc);
	cout << "  Arguments:" << endl;
	int i=0;
	for (auto a : args)
		cout << "    " << (i++) << ":" << a << endl;

	cout << "Testing Character sets" << endl;
	Lexer::CharSetTester::test();
	cout << "End"   << endl;
	return 0;
}
