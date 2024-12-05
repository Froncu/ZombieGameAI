#ifndef FSM_STATE_HPP
#define FSM_STATE_HPP

#include "pch.hpp"

namespace ai
{
   class FSMState
   {
   public:
      FSMState(IExamInterface* const interface);
      FSMState(FSMState const&) = delete;
      FSMState(FSMState&&) = delete;

      virtual ~FSMState() = default;

      FSMState& operator=(FSMState const&) = delete;
      FSMState& operator=(FSMState&&) = delete;

      virtual void OnEnter() {};
      virtual void OnExit() {};
      [[nodiscard]] virtual SteeringPlugin_Output Update(float delta_seconds) = 0;
      virtual void Render(float const) {};

   protected:
      IExamInterface* const interface_;
   };
}

#endif