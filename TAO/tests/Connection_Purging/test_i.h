//
// $Id: test_i.h 77008 2007-02-12 11:52:38Z johnnyw $
//

#ifndef TEST_I_H
#define TEST_I_H
#include /**/ "ace/pre.h"

#include "testS.h"

class test_i
  : public virtual POA_test
{
public:
  // = The skeleton methods
  virtual void send_stuff (const char* string);

private:
};

#include /**/ "ace/post.h"
#endif /* TEST_I_H */
