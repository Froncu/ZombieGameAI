#include "pch.hpp"

#include "SeesHousesCondition.hpp"

namespace ai
{
   SeesHousesCondition::SeesHousesCondition(IExamInterface* const interface)
      : FSMCondition{ interface }
   {
   }

   bool SeesHousesCondition::Evaluate() const
   {
      return interface_->FOV_GetStats().NumHouses;
   }
}