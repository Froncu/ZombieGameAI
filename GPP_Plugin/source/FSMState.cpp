#include "pch.hpp"

#include "FSM.hpp"

namespace ai
{
   FSMState::FSMState(IExamInterface* const interface)
      : interface_{ interface }
   {
   }
}