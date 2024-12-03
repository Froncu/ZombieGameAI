#ifndef FRONCU_AGENT_PLUGIN_HPP
#define FRONCU_AGENT_PLUGIN_HPP

#include "pch.hpp"

struct HouseCornerHasher final
{
   std::size_t operator()(Elite::Vector2 const house_corner) const
   {
      std::hash<float> constexpr hasher{};
      std::size_t const hash_x{ hasher(std::round(house_corner.x)) };
      std::size_t const hash_y{ hasher(std::round(house_corner.y)) };

      return hash_x ^ (hash_y << 1);
   }
};

struct HouseCornerComparator final
{
   bool operator()(Elite::Vector2 house_corner1, Elite::Vector2 house_corner2) const
   {
      house_corner1 = { std::round(house_corner1.x), std::round(house_corner1.y) };
      house_corner2 = { std::round(house_corner2.x), std::round(house_corner2.y) };

      return house_corner1 == house_corner2;
   }
};

class FroncuAgentPlugin : public IExamPlugin
{
   using HouseCornersType = std::unordered_set<Elite::Vector2, HouseCornerHasher, HouseCornerComparator>;

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

   HouseCornersType house_corners_{};
   HouseCornersType::iterator closest_house_corner_{ house_corners_.end() };
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