#ifndef TEST
#include <Stream.h>
#else
#include "test/StreamStub.h"
#endif

#ifndef CajuStreamShell_h
#define CajuStreamShell_h

#ifndef NUM_COMMANDS
#define NUM_COMMANDS 5
#endif

#ifndef COMMAND_STRING_SIZE
#define COMMAND_STRING_SIZE 25
#endif

class CajuStreamShell {
public:
	CajuStreamShell(Stream* stream);

	void addCommand(const char* command, void(*func)());
	void tick();
#ifndef TEST
private:
#endif
	Stream* stream;

	unsigned char numCommands;

	unsigned char limitCommand[NUM_COMMANDS];
	char commands[NUM_COMMANDS][COMMAND_STRING_SIZE];
	unsigned char countCommand[NUM_COMMANDS];

	void(*funcCommands[NUM_COMMANDS])();
};

#endif