#include <inttypes.h>
#include <string.h>
#include <queue>

#ifndef StreamStub_h
#define StreamStub_h

#define SIZE_BUFFER 30

//typedef unsigned int size_t;
typedef unsigned char uint8_t;

const int DEC = 0;

class Stream {
private:
	std::queue<uint8_t> buffer;

public:
	Stream();

	// Stub Function
	void put(uint8_t byte);

	int available();
	int read();
	int peek();
	int flush();
	void setTimeout(unsigned long timeout);
	bool find(char *target);
	bool find(char *target, size_t length);
	bool findUntil(char *target, char *terminator);
	bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);
	long parseInt();
	float parseFloat();
	size_t readBytes( char *buffer, size_t length);
	size_t readBytesUntil( char terminator, char *buffer, size_t length);
	//String readString();
	//String readStringUntil(char terminator);

	// Print methods
	int getWriteError() { return 0; }
	void clearWriteError() { /* Nothing Implemented */ }

	size_t write(uint8_t);
	size_t write(const char *str) {
		if (str == NULL) return 0;
		return write((const uint8_t *)str, strlen(str));
	}
	size_t write(const uint8_t *buffer, size_t size);

	//size_t print(const __FlashStringHelper *);
	//size_t print(const String &);
	size_t print(const char[]);
	size_t print(char);
	size_t print(unsigned char, int = DEC);
	size_t print(int, int = DEC);
	size_t print(unsigned int, int = DEC);
	size_t print(long, int = DEC);
	size_t print(unsigned long, int = DEC);
	size_t print(double, int = 2);
	//size_t print(const Printable&);

	//size_t println(const __FlashStringHelper *);
	//size_t println(const String &s);
	//size_t println(const char[]);
	size_t println(char);
	size_t println(unsigned char, int = DEC);
	size_t println(int, int = DEC);
	size_t println(unsigned int, int = DEC);
	size_t println(long, int = DEC);
	size_t println(unsigned long, int = DEC);
	size_t println(double, int = 2);
	//size_t println(const Printable&);
	size_t println(void);
};

#endif
