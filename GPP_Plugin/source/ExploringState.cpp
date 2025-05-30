#include "pch.hpp"

#include "ExploringState.hpp"

namespace ai
{
   ExploringState::ExploringState(IExamInterface* const interface)
      : FSMState{ interface }
   {
   }

   void ExploringState::OnEnter()
   {
   }

   void ExploringState::OnExit()
   {
   }

   SteeringPlugin_Output ExploringState::Update(float const)
   {
      Elite::Vector2 const current_position{ interface_->Agent_GetInfo().Position };

      scanner_ = current_position + max_distance_to_house_corner_ *
         Elite::OrientationToVector(interface_->Agent_GetInfo().Orientation);
      scanner_ = interface_->NavMesh_GetClosestPathPoint(scanner_);

      if ((scanner_ - current_position).MagnitudeSquared() <=
         max_distance_to_house_corner_ * max_distance_to_house_corner_ - epsilon_ and
         house_corners_.insert(scanner_).second)
      {
         closest_house_corner_ = std::ranges::min_element(house_corners_,
            [current_position](Elite::Vector2 const house_corner1, Elite::Vector2 const house_corner2)
            {
               return
                  (house_corner1 - current_position).MagnitudeSquared() <
                  (house_corner2 - current_position).MagnitudeSquared();
            });
      }

      Elite::Vector2 const delta_closest_house_corner{
         closest_house_corner_ == house_corners_.end() ?
         Elite::Vector2{ 64.0f, 64.0f } :
         *closest_house_corner_ - current_position };

      return SteeringPlugin_Output
      {
         .LinearVelocity{ delta_closest_house_corner },
         .AngularVelocity{ interface_->Agent_GetInfo().MaxAngularSpeed },
         .AutoOrient{ false }
      };
   }

   void ExploringState::Render(float const)
   {
      for (Elite::Vector2 const house_corner : house_corners_)
         interface_->Draw_SolidCircle(house_corner, house_corner_size_, {}, house_corner_color_);

      Elite::Vector2 const current_position{ interface_->Agent_GetInfo().Position };

      if (closest_house_corner_ not_eq house_corners_.end())
      {
         interface_->Draw_Segment(current_position, *closest_house_corner_, closest_house_corner_color_);
         interface_->Draw_SolidCircle(*closest_house_corner_, house_corner_size_, {}, closest_house_corner_color_);
      }

      interface_->Draw_Segment(current_position, scanner_, scanner_color_);
      interface_->Draw_SolidCircle(scanner_, scanner_size_, {}, scanner_color_);
      interface_->Draw_Circle(current_position, max_distance_to_house_corner_, scanner_color_);
   }
}