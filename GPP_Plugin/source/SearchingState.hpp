#ifndef SEARCHING_STATE_HPP
#define SEARCHING_STATE_HPP

#include "pch.hpp"

#include "FSMState.hpp"
#include "HouseInfoComparator.hpp"
#include "HouseInfoHasher.hpp"

namespace ai
{
   class SearchingState : public FSMState
   {
   public:
      SearchingState(IExamInterface* const interface);

      virtual ~SearchingState() override = default;

      virtual void OnEnter() override;
      virtual void OnExit() override;
      [[nodiscard]] virtual SteeringPlugin_Output Update(float) override;
      virtual void Render(float) override;

   private:
      std::unordered_set<HouseInfo, HouseInfoHasher, HouseInfoComparator> houses_{};
   };
}

#endif