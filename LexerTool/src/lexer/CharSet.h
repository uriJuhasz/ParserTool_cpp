/*
 * CharSet.h
 *
 *  Created on: 17 Mar 2017
 *      Author: uri
 */

#ifndef LEXER_CHARSET_H_
#define LEXER_CHARSET_H_

#include "LexerTypes.h"
#include <cassert>

namespace Lexer {

class CharSet {
public:
	CharSet();
	virtual ~CharSet() = 0;

	virtual bool has(Char c) = 0;
};

class SingletonCharSet final : public CharSet{
public:
	SingletonCharSet(Char c) : c(c){}
	bool has (Char k) override{return c==k;}
	const Char c;
};
class RangeCharSet final : public CharSet{
public:
	RangeCharSet(Char c0,Char c1) : c0(c0), c1(c1){ assert(c0 <= c1);}
	bool has (Char k) override{return k>=c0 && k<=c1;}
	const Char c0,c1;
};

} /* namespace Lexer */

#endif /* LEXER_CHARSET_H_ */
