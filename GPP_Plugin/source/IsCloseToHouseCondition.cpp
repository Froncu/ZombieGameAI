#include "pch.hpp"

#include "IsCloseToHouseCondition.hpp"

namespace ai
{
   IsCloseToHouseCondition::IsCloseToHouseCondition(IExamInterface* const interface)
      : FSMCondition{ interface }
   {
   }
}