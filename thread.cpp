#include <iostream>
#include "thread.h"
using namespace std;

Thread::Thread() {
	tid = 0;
	threadStatus = THREAD_STATUS_NEW;
}

bool Thread::start() {
	int iRet = 0;
	pthread_create(&tid, NULL, thread_proxy_func, this);
}

void* Thread::thread_proxy_func(void* args) {
	Thread* pThread= static_cast<Thread*>(args);
	pThread->run();
	return NULL;
}

pthread_t Thread::getThreadID() {
	return tid;
}

int Thread::getStatus() {
	return threadStatus;
}

void Thread::join() {
	if (tid > 0)
		pthread_join(tid, NULL);
}

void Thread::join(unsigned long millisTime) {
	if (tid == 0) return;
	if (millisTime <= 0) join();
	else {
		unsigned long cnt = 0;
		while (threadStatus != THREAD_STATUS_EXIT  
				&& cnt <= millisTime) {
			usleep(100);
			cnt++;
		}
	}
}

void* Thread::run0(void* pVoid) {
	Thread* p = (Thread*) pVoid;
	p->run1();
	return p;
}

void* Thread::run1() {
	threadStatus = THREAD_STATUS_RUNNING;
	tid = pthread_self();
	run();
	threadStatus = THREAD_STATUS_EXIT;
	tid = 0;
	pthread_exit(NULL);
}

