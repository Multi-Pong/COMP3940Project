#pragma once
#include <string>
class Thread {
public:
	Thread(Thread *childThread);
	virtual ~Thread();
	virtual void run() = 0;
    virtual void send(std::string) = 0;
	void start();
private:
	void *state;
	Thread *childThread;
};
