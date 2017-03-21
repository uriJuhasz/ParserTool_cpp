/*
 * CharSetTester.cpp
 *
 *  Created on: 20 Mar 2017
 *      Author: uri
 */

#include "CharSetTester.h"

#include <iostream>
#include <chrono>
#include <random>
using namespace std;

#include "../CharSet.h"
namespace Lexer {

void CharSetTester::test(){
	 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	 cout << "Testing CharSet - seed=" << seed << endl;

	 std::minstd_rand0 g1 (seed);

	 auto cs0 = CharSet::make();
	 wcout << "cs0  :" << cs0 << endl;
	 auto cs1 = CharSet::make('c');
	 wcout << "cs1  :" << cs1 << endl;
	 auto cs3 = CharSet::make('u');
	 wcout << "cs3  :" << cs3 << endl;
	 auto cs2 = CharSet::make('a','z');
	 wcout << "cs2  :" << cs2 << endl;
	 assert(!cs0.has('c'));
	 assert(cs1.has('c'));
	 assert(!cs1.has('d'));

	 auto cs1u2 = cs1+cs2;
	 wcout << "cs1u2:" << cs1u2 << endl;
	 assert(cs1u2.has('c'));
	 assert(cs1u2.has('e'));
	 auto cs1i2 = cs1*cs2;
	 wcout << "cs1i2:" << cs1i2 << endl;
	 assert(cs1i2.has('c'));
	 assert(!cs1i2.has('e'));
	 auto cs2m1 = cs2-cs1;
	 wcout << "cs2m1:" << cs2m1 << endl;
	 assert(!cs2m1.has('c'));
	 assert(cs2m1.has('e'));
	 auto cs2m3 = cs2-cs3;
	 wcout << "cs2m3:" << cs2m3 << endl;
	 assert(cs2m3.has('c'));
	 assert(!cs2m3.has('u'));
	 auto cs5 = cs2m1 * cs2m3;
	 wcout << "cs5  :" << cs5 << endl;
	 auto cs6 = cs2m1 + cs2m3;
	 wcout << "cs6  :" << cs6 << endl;
	 auto cs7 = CharSet::make(L'\u0370',L'\u03ff');
	 cout << "A0:" << u8'ɵ' << endl;

	 cout << "A1:" << u8'\u03B1' << endl;
	 cout << "A2:" <<  L'\u03C9' << endl;
	 wcout << "A3:" << u8'\u03B1' << endl;
	 wcout << "A4:" <<  L'\u03C9' << endl;
	 wcout << "cs7  :" << cs7 << endl;

	 cout << "Testing CharSet - done" << endl;
}

} /* namespace Lexer */
