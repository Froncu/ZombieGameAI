#ifndef SEES_HOUSES_CONDITION
#define SEES_HOUSES_CONDITION

#include "FSMCondition.hpp"

namespace ai
{
   class SeesHousesCondition : public FSMCondition
   {
   public:
      SeesHousesCondition(IExamInterface* const interface);

      virtual ~SeesHousesCondition() = default;

      [[nodiscard]] virtual bool Evaluate() const;
   };
}

#endif