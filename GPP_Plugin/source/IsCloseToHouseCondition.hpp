#ifndef IS_CLOSE_TO_HOUSE_CONDITION
#define IS_CLOSE_TO_HOUSE_CONDITION

#include "FSMCondition.hpp"

namespace ai
{
   class IsCloseToHouseCondition : public FSMCondition
   {
   public:
      IsCloseToHouseCondition(IExamInterface* const interface);

      virtual ~IsCloseToHouseCondition() = default;

      [[nodiscard]] virtual bool Evaluate() const { return false; }
   };
}

#endif