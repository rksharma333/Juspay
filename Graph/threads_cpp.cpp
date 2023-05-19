#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

int count = 0;

mutex stop;

void task()
{
      // stop.lock(); // locking the function when one thread enters

      for (int i = 0; i < 1000000; i++)
      {
            count += 1; // adding 1000000 in every loop
      }
      // stop.unlock(); // unlocking when thread complets it's execution
}

int main()
{

      thread t1(task);
      thread t2(task);

      t1.join();
      t2.join();

      cout << count << endl; // output comes exactly 2000000

      return 0;
}

