#include <iostream>
#include <string>
#include <vector>

#include "Mutex.h"
#include "Thread.h"

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

class HelloWorld : public Thread
{
public:
  HelloWorld(std::ostream &str)
      : m_stream(str)
  {
  }

protected:
  virtual void run()
  {
    for (size_t i = 0; i < 10; i++)
    {
      m_stream << "Hello, world!\n";
      Sleep(250);
    }
  }

private:
  std::ostream &m_stream;
};

int main()
{
  Producer prod;
  Consumer cons;
  HelloWorld hw(std::cout);

  hw.start();
  cons.start();
  Sleep(1000);
  prod.start();

  prod.join();
  cons.join();
  hw.join();

  return 0;
}
