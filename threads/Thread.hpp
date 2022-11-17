#pragma once
class Thread {
public:
	Thread(Thread *childThread);
	~Thread();
	virtual void run() = 0;
	void start();
private:
	void *state;
	Thread *childThread;
};
