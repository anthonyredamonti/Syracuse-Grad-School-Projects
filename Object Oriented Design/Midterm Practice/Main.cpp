/*

#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    
    // use unique lock for polling (waiting) thread. Use mutex to access shared boolean variable.
    std::unique_lock<std::mutex> lck(mtx);

    // use while loop to handle spurious wakeups.
    while (!ready) cv.wait(lck);
    
    // print the thread id to the console.
    std::cout << "thread " << id << '\n';
}

void go() {
    // use a lock guard on the shared boolean variable
    std::lock_guard<std::mutex> lck(mtx);

    // change the state of the boolean variable.
    ready = true;

    // notify all of the threads waiting on the condition variable
    cv.notify_all();
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(print_id, i);

    std::cout << "10 threads ready to race...\n";
    go();                       // go!

    for (auto& th : threads) th.join();

    return 0;
}
*/


#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mutex1;
std::mutex mutex2;
std::condition_variable conditionVariable1;
std::condition_variable conditionVariable2;
using std::endl;
using std::cout;
using std::vector;

bool beingUsed{ false };
int threadRun{ 0 };

void Foo(int x, int totalNumberOfThreads);
void ExitFoo(int x, int totalNumberOfThreads);


void EnterFoo(int threadNumber, int totalNumberOfThreads){
    
    std::unique_lock<std::mutex> lck(mutex1);
    conditionVariable1.wait(lck, []{ return !beingUsed; });   // (4)

    beingUsed = true; // this thread is using Foo.

    cout << threadNumber << " wants to enter foo " << endl;

    Foo(threadNumber, totalNumberOfThreads);

    beingUsed = false;

    lck.unlock();
    conditionVariable1.notify_one();
}

void Foo(int x, int totalNumberOfThreads) {

    // increment the global variable.
    threadRun = threadRun + 1;

    cout << x << " has entered Foo." << endl;
    cout << threadRun << endl;
}

void ExitFoo(int x, int totalNumberOfThreads){

    std::unique_lock<std::mutex> lck(mutex2);
    conditionVariable2.wait(lck, [&] { return (threadRun == totalNumberOfThreads); });   // (4)

    // notify all the threads to exit.
    conditionVariable2.notify_all();

    cout << "All threads are exiting." << endl;
                       // (3)
}

void ThreadFunction(int x) {

    vector<std::thread> threadVector;

    // create x number of threads and call enterfoo
    for (int i = 0; i < x; i++) {
        std::thread thread1(EnterFoo, i, x);

        std::thread thread2(ExitFoo, i, x);

        threadVector.push_back(thread1);
        threadVector.push_back(thread2);
    }

    for (int i = 0; i < threadVector.size(); i++) {
        threadVector[i].join();
    }


}

int main(){
    ThreadFunction(5);
}


/*

//Directives
#include <Windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;
using std::runtime_error;

// declare threads.
thread thread1;
thread thread2;

// print out number to console
static void ThreadProc() {
    
    try {
        // get the ID of the current thread.
        thread::id idCurrentThread = std::this_thread::get_id();

        // if thread 1 and thread 2 is joinable, wait for thread 2 to complete (join thread 2).
        if ((idCurrentThread == thread1.get_id()) && (thread2.joinable())) {
            thread2.join();
        }

        // if using thread 1, print this message.
        if (idCurrentThread == thread1.get_id()) {
            cout << "I am thread 1." << endl;
        }

        // if using thread 2, print this message.
        if (idCurrentThread == thread2.get_id()) {
            cout << "I am thread 2." << endl;
        }

        Sleep(100); // sleep for 100 milliseconds.
    }
    catch (const runtime_error& exception) {
        cout << "\nRuntime error in thread: " << std::this_thread::get_id() << endl;
        cout << exception.what();
        throw exception;
    }
    catch (...) {
        cout << "\nException occurred in thread: " << std::this_thread::get_id() << endl;
        throw;
    }

}

int main()
{
    // record the thread ID's.
    thread::id threadId1 = thread1.get_id();
    thread::id threadId2 = thread2.get_id();

    // start threads.
    thread1 = thread(ThreadProc);
    thread2 = thread(ThreadProc);

    // main thread will wait for thread1 to finish.
    thread1.join();

    getchar();
}

*/

/*

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;//you can use std::lock_guard if you want to be exception safe
int i = 0;

void makeACallFromPhoneBooth()
{
    m.lock();//man gets a hold of the phone booth door and locks it. The other men wait outside
      //man happily talks to his wife from now....
    std::cout << i << " Hello Wife" << std::endl;
    i++;//no other thread can access variable i until m.unlock() is called
    //...until now, with no interruption from other men
    m.unlock();//man lets go of the door handle and unlocks the door
}

int main()
{
    //This is the main crowd of people uninterested in making a phone call

    //man1 leaves the crowd to go to the phone booth
    std::thread man1(makeACallFromPhoneBooth);
    //Although man2 appears to start second, there's a good chance he might
    //reach the phone booth before man1
    std::thread man2(makeACallFromPhoneBooth);
    //And hey, man3 also joined the race to the booth
    std::thread man3(makeACallFromPhoneBooth);

    man1.join();//man1 finished his phone call and joins the crowd
    man2.join();//man2 finished his phone call and joins the crowd
    man3.join();//man3 finished his phone call and joins the crowd
    return 0;
}
*/

/*

#include<iostream>
using std::getchar;

template <typename firstType, typename secondType> class TemplateClass {    

public:

    // initialization constructor
    TemplateClass(const firstType& arg1, const secondType& arg2) {
        
        // initialize the pointers on the heap.
        firstTypePntr = new firstType();
        secondTypePntr = new secondType();

        // dereference the pointers (assign values)
        *firstTypePntr = arg1;
        *secondTypePntr = arg2;
    }

    // [] operator overloading. Return value by reference.
    TemplateClass & operator[] (int x) {
       if (x == 0) {
           return (firstType)(*(this->firstTypePntr));
       }

       if (x == 1) {
           return (secondType)(*(this->secondTypePntr));
       }
    }

    // copy constructor
    TemplateClass(const TemplateClass& oldObj) {
        
        // initialize the pointers on the heap.
        firstTypePntr = new firstType();
        secondTypePntr = new secondType();

        // copy over the old pointer to the new pointers.
        *firstTypePntr = *oldObj.firstTypePntr;
        *secondTypePntr = *oldObj.secondTypePntr;
    }

    // move constructor
    TemplateClass(const TemplateClass&& oldObj) : 
        firstTypePntr{ nullptr }, 
        secondTypePntr{ nullptr }
    {
        // assign the old pointers to the new pointers.
        firstTypePntr = oldObj.firstTypePntr;
        secondTypePntr = oldObj.secondTypePntr;
        
        // free the old pointers
        oldObj.firstTypePntr = nullptr;
        oldObj.secondTypePntr = nullptr;
    }

    // destructor
    ~TemplateClass() {
        
        // if it is non-NULL, delete the pointer
        if (firstTypePntr != nullptr) {
            delete firstTypePntr;
        }

        // if it is non-NULL, delete the pointer
        if (secondTypePntr != nullptr) {
            delete secondTypePntr;
        }
    }

private:
    firstType* firstTypePntr;
    secondType* secondTypePntr;
};

int main()
{
    int intTemp = 5; 
    char charTemp = 'a';

    TemplateClass<int, char> test(intTemp, charTemp);

    int x = (int)test[0];

    getchar();
}

*/




