#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>
using namespace std;

#include "lexer/test/CharSetTester.h"


void testUnicode();

int main(int argc, char* argv[]) {
	cout << "Start" << endl;
	auto args = vector<string>(argv,argv+argc);
	cout << "  Arguments:" << endl;
	int i=0;
	for (auto a : args)
		cout << "    " << (i++) << ":" << a << endl;

	cout << "Testing unicode" << endl;
	testUnicode();
	cout << "Testing unicode done" << endl;
	cout << endl;

	cout << "Testing Character sets" << endl;
	parser::lexer::CharSetTester::test();
	cout << "Testing Character sets done" << endl;


	cout << "End"   << endl;
	return 0;
}

static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8c;
std::string u8(const char16_t c16){ return u8c.to_bytes(c16); }
std::string u8(const char32_t c32){ return u8c.to_bytes(c32); }

void testUnicode(){
//	 cout << "A0c:"   << 'ɵ' << endl;
//	 cout << "A0c8:"  << u8'ɵ' << endl;
	char16_t c16 = u'α';
	char32_t c32 = U'α';
	cout << "A0c16:" << c16 << endl;
	cout << "A0c32:" << c32 << endl;
	// the UTF-8 - UTF-32 standard conversion facet
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;

	auto s16to8 = cvt.to_bytes(c16);
	auto s32to8 = cvt.to_bytes(c32);

	 cout << "A0s:" << u8"ɵ" << endl;
	 cout << "A0sf16:" << s16to8 << endl;
	 cout << "A0sf32:" << s32to8 << endl;
//	 cout << "A1c:" << u8'\u03B1' << endl;
	 cout << "A1s:" << u8"\u03B1" << endl;
	 cout << "A2c:" <<  L'\u03C9' << endl;
	 cout << "A2s:" <<  L"\u03C9" << endl;
//	 wcout << "A3:" << u8'\u03B1' << endl;
	 wcout << "A4c:" <<  L'\u03C9' << endl;
	 wcout << "A4s:" <<  L"\u03C9" << endl;



}
