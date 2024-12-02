#ifndef FRONCU_AGENT_PLUGIN_HPP
#define FRONCU_AGENT_PLUGIN_HPP

#include "pch.hpp"

struct HouseCornersComparator final
{
   bool operator()(Elite::Vector2 const house_corner1, Elite::Vector2 const house_corner2) const
   {
      // this is needed because the next check is not fully accurate on it's own;
      // two different points might be at the same distance from the current position
      // (chances of that happening are very low, but this additional check is not expensive)
      if (house_corner1 == house_corner2)
         return false;

      auto const current_position{ interface->Agent_GetInfo().Position };

      return
         (house_corner1 - current_position).MagnitudeSquared() <
         (house_corner2 - current_position).MagnitudeSquared();
   }

   IExamInterface const* interface;
};

class FroncuAgentPlugin : public IExamPlugin
{
public:
   FroncuAgentPlugin() = default;
   virtual ~FroncuAgentPlugin() override = default;

   virtual void Initialize(IBaseInterface* const interface, PluginInfo& info) override;
   virtual void DllInit() override {};
   virtual void DllShutdown() override {};

   virtual SteeringPlugin_Output UpdateSteering(float delta_seconds) override;

   // Called once on initialisation (only in debug mode)
   virtual void InitGameDebugParams(GameDebugParams& parameters) override;
   // Called once every frame (only in debug mode)
   virtual void Update_Debug(float) override {}
   // Additional renderering (only in debug mode)
   virtual void Render(float) const override;

private:
   IExamInterface* interface_{};

   std::set<Elite::Vector2, HouseCornersComparator> house_corners_{};
   float max_distance_to_house_corner_{};

   Elite::Vector2 latest_potential_house_corner_{};
};

extern "C"
{
   __declspec (dllexport) IPluginBase* Register()
   {
      return new FroncuAgentPlugin();
   }
}

#endif