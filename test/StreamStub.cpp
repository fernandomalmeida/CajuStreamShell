#include "StreamStub.h"

Stream::Stream(){

}

int Stream::available(){
	return buffer.size();
}
int Stream::read(){
	uint8_t element;
	if(!buffer.empty()){
		element = buffer.front();
		buffer.pop();
	} else {
		element = 0;
	}

	return element;
}

void Stream::put(uint8_t byte){
	buffer.push(byte);
}