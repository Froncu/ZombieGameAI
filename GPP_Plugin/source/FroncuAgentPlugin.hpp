#ifndef FRONCU_AGENT_PLUGIN_HPP
#define FRONCU_AGENT_PLUGIN_HPP

#include "pch.hpp"

#include "HouseCornerComparator.hpp"
#include "HouseCornerHasher.hpp"

namespace ai
{
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
      virtual void Render(float) const override;

      // Called once on initialisation (only in debug mode)
      virtual void InitGameDebugParams(GameDebugParams& parameters) override;
      // Called once every frame (only in debug mode)
      virtual void Update_Debug(float) override {}

   private:
      // rendering
      static float constexpr house_corner_size_{ 2.0f };
      static Elite::Vector3 constexpr closest_house_corner_color_{ 0.0f, 1.0f, 0.0f };
      static Elite::Vector3 constexpr house_corner_color_{ closest_house_corner_color_ * 0.75f };

      static float constexpr scanner_size_{ 1.0f };
      static Elite::Vector3 constexpr scanner_color_{ 0.0f, 0.0f, 0.0f };

      static float constexpr max_distance_to_house_corner_{ 256.0f };
      static float constexpr epsilon_{ 1.0f };

      IExamInterface* interface_{};

      HouseCornersType house_corners_{};
      HouseCornersType::iterator closest_house_corner_{ house_corners_.end() };
      Elite::Vector2 scanner_{};
   };
}

#endif