#include "Base.h"

namespace sc {

  Base::Base()
    :state(SC_NONE)
    ,callback(NULL)
    ,user(NULL)
	, mousecallback(NULL)
  {
  }

  Base::~Base() {

    state = SC_NONE;
    callback = NULL;
    user = NULL;
	mousecallback = NULL;
  }
  
} /* namespace sc */
