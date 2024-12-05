#ifndef FSM_CONDITION_HPP
#define FSM_CONDITION_HPP

namespace ai
{
   class FSMCondition
   {
   public:
      FSMCondition(IExamInterface* const interface);
      FSMCondition(FSMCondition const&) = delete;
      FSMCondition(FSMCondition&&) noexcept = delete;

      virtual ~FSMCondition() = default;

      FSMCondition& operator=(FSMCondition const&) = delete;
      FSMCondition& operator=(FSMCondition&&) noexcept = delete;

      [[nodiscard]] virtual bool Evaluate() const = 0;

   protected:
      IExamInterface* const interface_;
   };
}

#endif