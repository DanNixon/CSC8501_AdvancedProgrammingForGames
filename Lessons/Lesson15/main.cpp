#include <iostream>
#include <string>
#include <vector>

#include "Thread.h"
#include "Mutex.h"

Mutex mut;
std::vector<std::string> buffer;

class Producer : public Thread
{
protected:
  virtual void run()
  {
    mut.lock_mutex();
    buffer.push_back("Hello from Producer\n");
    mut.unlock_mutex();
  }
};

class Consumer : public Thread
{
protected:
  virtual void run()
  {
    BOOL done = FALSE;
    while (!done)
    {
      mut.lock_mutex();
      if (buffer.size() > 0)
      {
        std::cout << "got msg: " << buffer.front() << "\n";
        done = TRUE;
      }
      mut.unlock_mutex();
    }
  }
};

int main()
{
  Producer prod;
  Consumer cons;

  cons.start();
  Sleep(1000);
  prod.start();

  prod.join();
  cons.join();

  return 0;
}
