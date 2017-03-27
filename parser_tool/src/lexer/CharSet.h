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
#include <vector>
#include <utility>
#include <ostream>

namespace parser{
namespace lexer {


class CharSet final{
public:
	~CharSet() {};

	bool has(Char c) const;
	bool isEmpty() const;

	static CharSet make();                //empty set
	static CharSet make(Char c);          //singleton
	static CharSet make(Char c0,Char c1); //inclusive range

	static CharSet parse(std::string);    //parse utf8 string
private:
	typedef std::pair<Char,Char> CP;
	typedef std::vector<CP>      CPV;
	CPV r;
	friend CharSet operator+(const CharSet& s0,const CharSet& s1); //set union
	friend CharSet operator*(const CharSet& s0,const CharSet& s1); //set intersection
	friend CharSet operator-(const CharSet& s0,const CharSet& s1); //set difference
	friend bool    operator==(const CharSet& s0,const CharSet& s1); //set equality
	friend bool    operator!=(const CharSet& s0,const CharSet& s1); //set equality

	friend std::wostream& operator<<(std::wostream&, const CharSet& s); //print
	friend std::ostream& operator<<(std::ostream&, const CharSet& s); //print


	CharSet();
	CharSet(Char c);
	CharSet(Char c0,Char c1);
	CharSet(const CPV& r);
};

CharSet operator+(const CharSet& s0,const CharSet& s1); //set union
CharSet operator-(const CharSet& s0,const CharSet& s1); //set difference
CharSet operator*(const CharSet& s0,const CharSet& s1); //set intersection
bool    operator==(const CharSet& s0,const CharSet& s1); //set equality
bool    operator!=(const CharSet& s0,const CharSet& s1); //set equality
//std::wostream& operator<<(std::wostream&, const CharSet& s); //print
std::ostream& operator<<(std::ostream&, const CharSet& s); //print

}} /* namespace parser::lexer */

#endif /* LEXER_CHARSET_H_ */
