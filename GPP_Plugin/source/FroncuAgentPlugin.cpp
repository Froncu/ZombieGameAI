#include "pch.hpp"

#include "FroncuAgentPlugin.hpp"

void FroncuAgentPlugin::DllInit()
{
   srand(static_cast<int>(time(nullptr)));
}

void FroncuAgentPlugin::Initialize(IBaseInterface* const interface, PluginInfo& info)
{
   interface_ = static_cast<IExamInterface* const>(interface);
   house_corners_ = std::set<Elite::Vector2, HouseCornersComparator>{ HouseCornersComparator{ interface_ } };

   Elite::Vector2 const world_dimensions{ interface_->World_GetInfo().Dimensions };
   max_distance_to_house_corner_ = std::sqrt(world_dimensions.x * world_dimensions.x + world_dimensions.y * world_dimensions.y);

   // information for the leaderboards!
   info.BotName = "xXx_-_RECORD_-_SMASHER_-_xXx";
   info.Student_Name = "JAKUB FRATCZAK"; // no special characters allowed
   info.Student_Class = "2DAE10";
   info.LB_Password = "BigBoss04!";
}

SteeringPlugin_Output FroncuAgentPlugin::UpdateSteering(float)
{
   Elite::Vector2 const current_position{ interface_->Agent_GetInfo().Position };
   Elite::Vector2 const potential_house_corner{ 
      current_position + max_distance_to_house_corner_ *
      Elite::OrientationToVector(interface_->Agent_GetInfo().Orientation) };

   latest_potential_house_corner_ = interface_->NavMesh_GetClosestPathPoint(potential_house_corner);
   if ((latest_potential_house_corner_ - current_position).MagnitudeSquared() <= max_distance_to_house_corner_ * max_distance_to_house_corner_)
      house_corners_.insert(latest_potential_house_corner_);

   Elite::Vector2 const delta_closest_house_corner{ *house_corners_.begin() - current_position };
   float const fov_range{ interface_->Agent_GetInfo().FOV_Range };
   bool const house_corner_in_fov{ delta_closest_house_corner.MagnitudeSquared() <= fov_range * fov_range };

   return SteeringPlugin_Output
   {
      .LinearVelocity{ house_corners_.empty() ? Elite::Vector2{} : delta_closest_house_corner },
      .AngularVelocity{ interface_->Agent_GetInfo().MaxAngularSpeed },
      .AutoOrient{ house_corner_in_fov }
   };
}

void FroncuAgentPlugin::InitGameDebugParams(GameDebugParams& parameters)
{
   parameters.Seed = int(time(nullptr));
   std::cout << std::format("[SEED IN USE: {}]\n", parameters.Seed);
}

void FroncuAgentPlugin::Render(float) const
{
   for (Elite::Vector2 const house_corner : house_corners_)
      interface_->Draw_SolidCircle(house_corner, 2.0f, {}, { 0.0f, 1.0f, 0.0f });

   interface_->Draw_SolidCircle(latest_potential_house_corner_, 1.0f, {}, {});
}