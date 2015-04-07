#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "StreamStub.h"
#include "../CajuStreamShell.h"

void doNothing(){
	mock().actualCall("doNothing");
}

void doNothing2(){
	mock().actualCall("doNothing2");
}

TEST_GROUP(CajuStreamShell) {
	Stream stream;
	CajuStreamShell* ss;
	
	void setup(){
		ss = new CajuStreamShell(&stream);
	}

	void teardown(){
		mock().checkExpectations();
		mock().clear();
		delete ss;
	}
};

TEST(CajuStreamShell, VerifyCajuStreamShellConstructor){
	CHECK_EQUAL(&stream, ss->stream);
	CHECK_EQUAL(0, ss->numCommands);
}

TEST(CajuStreamShell, AddCommandToCajuStreamShell){
	ss->addCommand("test", doNothing);
	CHECK_EQUAL(1, ss->numCommands);
	CHECK_EQUAL(0, ss->countCommand[0]);
	CHECK_EQUAL(5, ss->limitCommand[0]);
	STRCMP_EQUAL("test\n", ss->commands[0]);

	ss->addCommand("test2", doNothing);
	CHECK_EQUAL(2, ss->numCommands);
	CHECK_EQUAL(0, ss->countCommand[1]);
	CHECK_EQUAL(6, ss->limitCommand[1]);
	STRCMP_EQUAL("test2\n", ss->commands[1]);
}

TEST(CajuStreamShell, TestStream){
	stream.put('t');
	CHECK_EQUAL('t', stream.read());
	stream.put('e');
	stream.put('s');
	stream.put('t');
	CHECK_EQUAL('e', stream.read());
	CHECK_EQUAL('s', stream.read());
	CHECK_EQUAL('t', stream.read());
}

TEST(CajuStreamShell, StreamTick){
	mock().expectOneCall("doNothing2");

	ss->addCommand("test", doNothing);
	ss->addCommand("test2", doNothing2);
	stream.put('t');
	stream.put('e');
	stream.put('s');
	stream.put('t');
	stream.put('2');
	stream.put('\n');

	ss->tick();
	CHECK_EQUAL(1, ss->countCommand[0]);
	CHECK_EQUAL(1, ss->countCommand[1]);
	ss->tick();
	CHECK_EQUAL(2, ss->countCommand[0]);
	CHECK_EQUAL(2, ss->countCommand[1]);
	ss->tick();
	CHECK_EQUAL(3, ss->countCommand[0]);
	CHECK_EQUAL(3, ss->countCommand[1]);
	ss->tick();
	CHECK_EQUAL(4, ss->countCommand[0]);
	CHECK_EQUAL(4, ss->countCommand[1]);
	ss->tick();
	CHECK_EQUAL(0, ss->countCommand[0]);
	CHECK_EQUAL(5, ss->countCommand[1]);
	ss->tick();
	CHECK_EQUAL(0, ss->countCommand[0]);
	CHECK_EQUAL(0, ss->countCommand[1]);
}

int main(int ac, char** av){
	return CommandLineTestRunner::RunAllTests(ac, av);
}
