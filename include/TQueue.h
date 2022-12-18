#ifndef __TQueue_H__
#define __TQueue_H__

#include <iostream>

using namespace std;

const int maxMemsize = 25;

template <class T>
class TQueue
{
protected:
  T* pMem;
  int memSize;
  int dataCount;
  int li;
  int hi;
public:
  TQueue(int n = maxMemsize);
  TQueue(const TQueue<T>& q);
  ~TQueue();
  TQueue<T>& operator=(const TQueue<T>& q);
  bool IsEmpty() const;
  bool IsFull() const;
  void Put(const T& v);
  virtual T Pop();
  T Top();
  bool operator==(const TQueue<T>& q);
  bool operator!=(const TQueue<T>& q);
};
#endif

template<class T>
inline TQueue<T>::TQueue(int n)
{
  if (n <= 0)
    throw "Error";
  memSize = n;
  pMem = new T[memSize];
  hi = 0;
  li = 0;
  dataCount = 0;
}

template<class T>
inline TQueue<T>::TQueue(const TQueue& q)
{
  if (q.pMem == nullptr)
  {
    memSize = 0;
    pMem = nullptr;
    li = 0;
    hi = 0;
    dataCount = 0;
  }
  else
  {
    memSize = q.memSize;
    li = q.li;
    hi = q.hi;
    dataCount = q.dataCount;
    pMem = new T[memSize];
    if (!(q.IsEmpty()))
    {
      int j = hi;
      for (int i = 0; i < dataCount; i++)
      {
        pMem[j] = q.pMem[j];
        j--;
        if (j < 0) { j = memSize - 1; }
      }
    }
  }
}

template<class T>
inline TQueue<T>::~TQueue()
{
  memSize = 0;
  dataCount = 0;
  li = 0;
  hi = 0;
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
}

template<class T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
  if (this != &q)
  {
    if (pMem != nullptr) { delete[] pMem; }
    memSize = q.memSize;
    pMem = new T[memSize];
    hi = q.hi;
    li = q.li;
    dataCount = q.dataCount;
    if (!(q.IsEmpty()))
    {
      int j = hi;
      for (int i = 0; i < dataCount; i++)
      {
        pMem[j] = q.pMem[j];
        j--;
        if (j < 0) { j = memSize - 1; }
      }
    }
  }
  return *this;
}

template<class T>
inline bool TQueue<T>::IsEmpty() const
{
  return dataCount == 0;
}

template<class T>
inline bool TQueue<T>::IsFull() const
{
  return dataCount == memSize;
}

template<class T>
inline void TQueue<T>::Put(const T& v)
{
  if (IsFull()) throw "error";
  pMem[li++] = v;
  li = (li < memSize) ? li : 0;
  dataCount++;
}

template<class T>
inline T TQueue<T>::Pop()
{
  if (IsEmpty()) throw "error";
  T temp = pMem[hi++];
  hi = (hi < memSize) ? hi : 0;
  dataCount--;
  return temp;
}

template<class T>
inline T TQueue<T>::Top()
{
  if (IsEmpty()) throw "error";
  return pMem[hi];
}

template<class T>
inline bool TQueue<T>::operator==(const TQueue<T>& q)
{
  if (dataCount != q.dataCount) { return false; }
  int j = hi;
  int k = q.hi;
  for (int i = 0; i < dataCount; i++)
  {
    if (pMem[j] != q.pMem[k]) { return false; }
    j--;
    j = (j < 0) ? (memSize - 1) : j;
    k--;
    k = (k < 0) ? (q.memSize - 1) : k;
  }
  return true;
}

template<class T>
inline bool TQueue<T>::operator!=(const TQueue<T>& q)
{
  return (!(this->operator==(q)));
}
