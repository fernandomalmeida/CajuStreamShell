#include <string.h>
#include "CajuStreamShell.h"

/*
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
*/

CajuStreamShell::CajuStreamShell(Stream* stream) {
	this->stream = stream;

	this->numCommands = 0;
}

void CajuStreamShell::addCommand(const char* command, void(*func)()) {
	//int i;
	//this->stream->println("teste");
	strncpy(this->commands[this->numCommands], command, strlen(command)+2);
	this->commands[this->numCommands][strlen(command)] = '\n';
	
	//for(i=0; command[i] != '\n'; i++){
	//	this->commands[this->numCommands][i] = command[i];
	//}

	this->limitCommand[this->numCommands] = strlen(command)+1;
	this->countCommand[this->numCommands] = 0;
	(funcCommands[this->numCommands]) = func;
	this->numCommands++;
}

void CajuStreamShell::tick() {
	int i;
	if(this->stream->available()) {
		char c = this->stream->read();
		//this->stream->print(c);
		
		for(i=0; i<this->numCommands; i++) {
			if(c == this->commands[i][this->countCommand[i]]) {
				this->countCommand[i] = this->countCommand[i]+1;
				

				//if(this->commands[i][this->countCommand[i]] == '\n') {
				if(this->countCommand[i] == this->limitCommand[i]) {
					(*this->funcCommands[i])();
					this->countCommand[i] = 0;
				}
			} else {
				this->countCommand[i] = 0;
			}
		}
	}
}