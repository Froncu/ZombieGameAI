#include "pch.hpp"

#include "SearchingState.hpp"

namespace ai
{
   SearchingState::SearchingState(IExamInterface* const interface)
      : FSMState{ interface }
   {
   }
}