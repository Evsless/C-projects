#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool
{
public:
  T *Allocate()
  {
    if (!deallocated_objects.empty())
    {
      return CopyDeallocatedObject();
    }
    T *new_object = new T;
    allocated_objects.insert(new_object);
    return new_object;
  }

  T *TryAllocate()
  {
    if (!deallocated_objects.empty())
    {
      return CopyDeallocatedObject();
    }
    return nullptr;
  }

  void Deallocate(T *object)
  {
    if (allocated_objects.count(object) == 0)
    {
      throw invalid_argument("");
    }
    allocated_objects.erase(object);
    deallocated_objects.push(object);
  }

  ~ObjectPool()
  {
    for (auto &item : allocated_objects)
    {
      delete item;
    }
    allocated_objects.clear();
    while (!deallocated_objects.empty())
    {
      delete deallocated_objects.front();
      deallocated_objects.pop();
    }
  }

private:
  set<T *> allocated_objects;
  queue<T *> deallocated_objects;
  T *CopyDeallocatedObject()
  {
    auto obj_from_stack = deallocated_objects.front();
    allocated_objects.insert(obj_from_stack);
    deallocated_objects.pop();
    return obj_from_stack;
  }
};

void TestObjectPool()
{
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
