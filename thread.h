#ifndef __THREAD_H_
#define __THREAD_H_
#include <pthread.h>

class Thread {
private:
	pthread_t tid; //当前线程的ID
	int threadStatus; //当前线程的状态
	//获取执行方法的指针
	static void* run0(void* pVoid);
	static void* thread_proxy_func(void* args);
	void* run1(); //内部执行方法
public:
	Thread();
	virtual void run() = 0; //线程的运行实体，派生类必须实现该函数
	bool start();
	pthread_t getThreadID();
	int getStatus(); //获取线程状态
	void join(); //等待线程直至退出
	void join(unsigned long millisTime); //等待线程退出或者超时

	static const int THREAD_STATUS_NEW = 0;
	static const int THREAD_STATUS_RUNNING = 1;
	static const int THREAD_STATUS_EXIT = -1;
};

#endif
