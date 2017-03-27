/*
 * CharStream.h
 *
 *  Created on: 26 Mar 2017
 *      Author: uri
 */

#ifndef PARSER_STREAM_ISTREAM_H_
#define PARSER_STREAM_ISTREAM_H_

#include <vector>
#include <stack>

namespace parser {
namespace stream {

class Position{
public:
	typedef int Nat;
	Position(Nat abs,Nat row,Nat col) : abs(abs), row(row),col(col){}

	Nat abs;

	Nat row;
	Nat col;

};

template<class T>class IStream {
public:
	IStream();
	virtual ~IStream()  =0;

	virtual bool isEnd()const {return isEndI();}
	virtual T    cur()  const {return curI();}
	virtual void next(){nextI();}

protected:
	virtual bool isEndI() const =0;
	virtual T    curI()   const =0;
	virtual void nextI() =0;

};

template<class T>class IPosStream : public IStream<T>{
public:
	IPosStream();
	virtual ~IPosStream();

	virtual void next() override;

	virtual Position pos() const;
private:
	Position curPos = Position(0,1,1);
};

template<class T>class IBufferStream : public IPosStream<T>{
public:
	IBufferStream();
	virtual ~IBufferStream();

	virtual void push();
	virtual void pop();

	virtual bool isEnd() const override;
	virtual T    cur()   const override;
	virtual void next()        override;

protected:
	virtual bool isEOL(T t) const = 0;

private:
	bool invariant() const;
	void extendBuffer() const;
	mutable std::vector<T> buffer;
	typedef unsigned int Index;
	mutable Index bufPos = 0;   //current position in the buffer
	Index bufStart = 0; //position of buffer start (bottom of stack)
	std::stack<Position> posStack;
};

} /* namespace stream */
} /* namespace parser */

#endif /* PARSER_STREAM_ISTREAM_H_ */
