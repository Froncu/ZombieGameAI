#ifndef SEARCHING_STATE_HPP
#define SEARCHING_STATE_HPP

#include "FSMState.hpp"

namespace ai
{
   class SearchingState : public FSMState
   {
   public:
      SearchingState(IExamInterface* const interface);

      virtual ~SearchingState() override = default;

      virtual void OnEnter() override {};
      virtual void OnExit() override {};
      virtual SteeringPlugin_Output Update(float const) override {};
      virtual void Render(float const) override {};
   };
}

#endif