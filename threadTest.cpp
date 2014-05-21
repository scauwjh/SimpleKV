#include "thread.h"
#include <iostream>
using namespace std;

class Test :public Thread {
public:
	void run() {
		for (int i = 0; i < 10; i++) {
			cout << "ID: " << i << endl;
			cout << "PID: " << getpid() << endl;
			cout << "TID: " << getThreadID() << endl;
			sleep(1);
		}
	}
};

int main() {
	Test a, b;
	a.start();
	b.start();
	cout << "end" << endl;
	a.join();
	b.join();
	return 0;
}
