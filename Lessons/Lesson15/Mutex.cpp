#include "Mutex.h"

Mutex::Mutex()
{
  mutex = CreateMutex(NULL,  // default security
                      FALSE, // initially not owned
                      NULL); // unamed mutex
}

Mutex::~Mutex()
{
  CloseHandle(mutex);
}

void Mutex::lock_mutex()
{
  DWORD wait_result;
  wait_result = WaitForSingleObject(mutex,     // handle to mutex
                                    INFINITE); // no time-out interval
}

void Mutex::unlock_mutex()
{
  ReleaseMutex(mutex);
}