#ifndef FSM_CONDITION_HPP
#define FSM_CONDITION_HPP

namespace ai
{
   class FSMCondition
   {
   public:
      FSMCondition() = default;
      FSMCondition(FSMCondition const&) = delete;
      FSMCondition(FSMCondition&&) noexcept = delete;

      virtual ~FSMCondition() = default;

      FSMCondition& operator=(FSMCondition const&) = delete;
      FSMCondition& operator=(FSMCondition&&) noexcept = delete;

      virtual bool Evaluate() const = 0;
   };
}

#endif