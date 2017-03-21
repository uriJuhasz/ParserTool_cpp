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
	 cout << "cs0  :" << cs0 << endl;
	 auto cs1 = CharSet::make('c');
	 cout << "cs1  :" << cs1 << endl;
	 auto cs3 = CharSet::make('u');
	 cout << "cs3  :" << cs3 << endl;
	 auto cs2 = CharSet::make('a','z');
	 cout << "cs2  :" << cs2 << endl;
	 assert(!cs0.has('c'));
	 assert(cs1.has('c'));
	 assert(!cs1.has('d'));

	 auto cs1u2 = cs1+cs2;
	 cout << "cs1u2:" << cs1u2 << endl;
	 assert(cs1u2.has('c'));
	 assert(cs1u2.has('e'));
	 auto cs1i2 = cs1*cs2;
	 cout << "cs1i2:" << cs1i2 << endl;
	 assert(cs1i2.has('c'));
	 assert(!cs1i2.has('e'));
	 auto cs2m1 = cs2-cs1;
	 cout << "cs2m1:" << cs2m1 << endl;
	 assert(!cs2m1.has('c'));
	 assert(cs2m1.has('e'));
	 auto cs2m3 = cs2-cs3;
	 cout << "cs2m3:" << cs2m3 << endl;
	 assert(cs2m3.has('c'));
	 assert(!cs2m3.has('u'));
	 auto cs5 = cs2m1 * cs2m3;
	 cout << "cs5  :" << cs5 << endl;
	 auto cs6 = cs2m1 + cs2m3;
	 cout << "cs6  :" << cs6 << endl;
	 auto cs7 = CharSet::make(u'\u0391',u'\u03A9');
	 cout << "cs7  :" << cs7 << endl;
	 auto cs8 = CharSet::make(u'\u03B1',u'\u03C9');
	 cout << "cs8  :" << cs8 << endl;
	 auto cs9 = CharSet::make(u'δ',u'φ');
	 cout << "cs9  :" << cs9 << endl;
	 auto cs10 = cs8 - cs9;
	 cout << "cs10  :" << cs10 << endl;

	 cout << "Testing CharSet - done" << endl;
}

} /* namespace Lexer */
