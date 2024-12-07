#include "pch.hpp"

#include "SearchingState.hpp"

namespace ai
{
   SearchingState::SearchingState(IExamInterface* const interface)
      : FSMState{ interface }
   {
   }

   void SearchingState::OnEnter()
   {
      std::vector<HouseInfo> const houses_in_fov{ interface_->GetHousesInFOV() };
      houses_.insert(houses_in_fov.begin(), houses_in_fov.end());
   }

   void SearchingState::OnExit()
   {
   }

   SteeringPlugin_Output SearchingState::Update(float const)
   {
      Elite::Vector2 const agent_position{ interface_->Agent_GetInfo().Position };
      float const max_linear_velocity{ interface_->Agent_GetInfo().MaxLinearSpeed };

      return SteeringPlugin_Output
      {
         .LinearVelocity{ (interface_->NavMesh_GetClosestPathPoint(houses_.begin()->Center) - agent_position).GetNormalized() * max_linear_velocity }
      };
   }

   void SearchingState::Render(float const)
   {
   }
}