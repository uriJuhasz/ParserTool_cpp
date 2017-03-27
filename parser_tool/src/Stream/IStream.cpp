/*
 * CharStream.cpp
 *
 *  Created on: 26 Mar 2017
 *      Author: uri
 */

#include "IStream.h"
#include <algorithm>

namespace parser {
namespace stream {

template<class T>IStream<T>::IStream() {}

template<class T>IStream<T>::~IStream() {}

template<class T>IPosStream<T>::~IPosStream() {}

template<class T> void IPosStream<T>::next()
{
	assert(!this->isEnd());
	curPos.abs++;
	if (isEOL(this->cur())){ //Advance current position
		curPos.row++;
		curPos.col=1;
	}else
		curPos.col++;
	IStream<T>::next(); //super call
}

template<typename T>bool IBufferStream<T>::invariant() const
{
	return
		   bufPos>=0
		&& bufPos<=buffer.size()
		&& bufStart>=0
		;
}

template<typename T>bool IBufferStream<T>::isEnd() const{
	assert (invariant());
	return bufPos==buffer.size()
			&& IPosStream<T>::isEnd();
}

template<typename T>T IBufferStream<T>::cur() const{
	assert (invariant());
	if (bufPos>=buffer.size()){
		assert(bufPos==buffer.size());
		assert(!this->isEnd());
		extendBuffer();
	};
	assert(this->bufPos>=0);
	assert(bufPos<buffer.size());
	return buffer[bufPos];
}
template<typename T>void IBufferStream<T>::next(){
	assert (invariant());
	assert (!this->isEnd());
	if (bufPos>=buffer.size()){
		assert(bufPos==buffer.size());
		extendBuffer();
	};
	assert(this->bufPos>=0);
	assert(bufPos<buffer.size());
	bufPos++;
}

template<typename T>void IBufferStream<T>::extendBuffer() const{
	const Index n = 1;
	const Index oldEnd = buffer.size();
	buffer.resize(oldEnd+n);
	for (auto i=0;i<n;i++){
		buffer[oldEnd+i] = IPosStream<T>::cur();
		IPosStream<T>::next();
	}
}

} /* namespace common */
} /* namespace parser */
