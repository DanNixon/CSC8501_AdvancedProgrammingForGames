#pragma once

#include <windows.h>

class Mutex
{
public:
  Mutex();
  virtual ~Mutex();
  virtual void lock_mutex();
  virtual void unlock_mutex();

protected:
  HANDLE mutex;
};