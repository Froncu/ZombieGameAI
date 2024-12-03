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

   virtual void DllInit() override;
   virtual void DllShutdown() override {};

   virtual void Initialize(IBaseInterface* const interface, PluginInfo& info) override;

   virtual SteeringPlugin_Output UpdateSteering(float delta_seconds) override;

   // Called once on initialisation (only in debug mode)
   virtual void InitGameDebugParams(GameDebugParams& parameters) override;
   // Called once every frame (only in debug mode)
   virtual void Update_Debug(float) override {}
   // Additional renderering (only in debug mode)
   virtual void Render(float) const override;

private:
   static float constexpr max_distance_to_house_corner_{ 256.0f };
   static float constexpr epsilon_{ 1.0f };

   IExamInterface* interface_{};

   std::set<Elite::Vector2, HouseCornersComparator> house_corners_{};
   Elite::Vector2 scanner_{};

   // rendering
   static float constexpr house_corner_size_{ 2.0f };
   Elite::Vector3 const closest_house_corner_color_{ 0.0f, 1.0f, 0.0f };
   Elite::Vector3 const house_corner_color_{ closest_house_corner_color_ * 0.75f };

   static float constexpr scanner_size_{ 1.0f };
   Elite::Vector3 const scanner_color_{ 0.0f, 0.0f, 0.0f };
};

extern "C"
{
   __declspec (dllexport) IPluginBase* Register()
   {
      return new FroncuAgentPlugin();
   }
}

#endif