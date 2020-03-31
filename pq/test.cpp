/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <assert.h>
#include <string>
#include "ExtrinsicMinPQ.h"

int main(int argc, char* argv[]) {
  ExtrinsicMinPQ<std::string> testPQ;

  // Testing add()
  assert(true == testPQ.add("cse", 12.3));
  assert(true == testPQ.add("332", 33.2));
  assert(true == testPQ.add("minpq", -5.67));
  assert(true == testPQ.add("assignment", -0.234));
  assert(true == testPQ.add("tests", 100.0));
  assert(true == testPQ.add("!", -5.66));
  assert(false == testPQ.add("cse", 12.3));
  assert(false == testPQ.add("332", 33.2));
  assert(false == testPQ.add("minpq", -5.67));
  assert(false == testPQ.add("assignment", -0.234));
  assert(false == testPQ.add("tests", 100.0));
  assert(false == testPQ.add("!", -5.66));

  // Testing contains()
  assert(testPQ.contains("assignment"));
  assert(testPQ.contains("332"));
  assert(testPQ.contains("!"));
  assert(testPQ.contains("minpq"));
  assert(testPQ.contains("cse"));
  assert(testPQ.contains("tests"));

  // Testing getSmallest()
  assert("minpq" == *(testPQ.getSmallest()));

  // Testing changePriority()
  testPQ.changePriority("cse", -12.3);
  assert("cse" == *(testPQ.getSmallest()));
  testPQ.changePriority("!", -50.66);
  assert("!" == *(testPQ.getSmallest()));

  // Testing size()
  assert(6 == testPQ.size());

  /*
  ////////////////// Removing until nothing left. //////////////////
  */
  std::string* ptr = testPQ.removeSmallest();
  assert("!" == *ptr);
  delete ptr;
  assert("cse" == *(testPQ.getSmallest()));
  assert(!testPQ.contains("!"));
  assert(5 == testPQ.size());

  ptr = testPQ.removeSmallest();
  assert("cse" == *ptr);
  delete ptr;
  assert("minpq" == *(testPQ.getSmallest()));
  assert(!testPQ.contains("cse"));
  assert(4 == testPQ.size());

  ptr = testPQ.removeSmallest();
  assert("minpq" == *ptr);
  delete ptr;
  assert("assignment" == *(testPQ.getSmallest()));
  assert(!testPQ.contains("minpq"));
  assert(3 == testPQ.size());

  ptr = testPQ.removeSmallest();
  assert("assignment" == *ptr);
  delete ptr;
  assert("332" == *(testPQ.getSmallest()));
  assert(!testPQ.contains("assignment"));
  assert(2 == testPQ.size());

  ptr = testPQ.removeSmallest();
  assert("332" == *ptr);
  delete ptr;
  assert("tests" == *(testPQ.getSmallest()));
  assert(!testPQ.contains("332"));
  assert(1 == testPQ.size());

  ptr = testPQ.removeSmallest();
  assert("tests" == *ptr);
  delete ptr;
  assert(nullptr == testPQ.getSmallest());
  assert(!testPQ.contains("332"));
  assert(0 == testPQ.size());
  assert(true == testPQ.isEmpty());

  // Edge cases: nothing to remove.
  ptr = testPQ.removeSmallest();
  assert(nullptr == ptr);
  assert(true == testPQ.isEmpty());
  ptr = testPQ.removeSmallest();
  assert(nullptr == ptr);
  assert(true == testPQ.isEmpty());
  ptr = testPQ.removeSmallest();
  assert(nullptr == ptr);
  assert(true == testPQ.isEmpty());
}
