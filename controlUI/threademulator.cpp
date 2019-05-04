#include "threademulator.h"
#include<thread>
ThreadEmulator::ThreadEmulator()
{

}

int volatile ThreadEmulator::X=10;
int volatile ThreadEmulator::Y=10;
int volatile ThreadEmulator::Tag=1;
int volatile ThreadEmulator::count=0;
int volatile ThreadEmulator::xArr[1000];
int volatile ThreadEmulator::yArr[1000];
void ThreadEmulator::threadOn()
{
    using namespace std;

    auto lambdaThread=[]()->void
    {
        _sleep(10000);
    };

    thread t=thread(lambdaThread);
    t.detach();
}
