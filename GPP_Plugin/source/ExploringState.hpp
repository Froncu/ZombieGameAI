#ifndef EXPLORING_STATE_HPP
#define EXPLORING_STATE_HPP

#include "FSMState.hpp"
#include "HouseCornerComparator.hpp"
#include "HouseCornerHasher.hpp"

namespace ai
{
   class ExploringState final : public FSMState
   {
      using HouseCornersType = std::unordered_set<Elite::Vector2, HouseCornerHasher, HouseCornerComparator>;

   public:
      ExploringState(IExamInterface* const interface);

      virtual ~ExploringState() override = default;

      virtual void OnEnter() override;
      virtual void OnExit() override;
      virtual SteeringPlugin_Output Update(float delta_seconds) override;
      virtual void Render(float delta_seconds) override;

   private:
      // rendering
      static float constexpr house_corner_size_{ 2.0f };
      static Elite::Vector3 constexpr closest_house_corner_color_{ 0.0f, 1.0f, 0.0f };
      static Elite::Vector3 constexpr house_corner_color_{ closest_house_corner_color_ * 0.75f };

      static float constexpr scanner_size_{ 1.0f };
      static Elite::Vector3 constexpr scanner_color_{ 0.0f, 0.0f, 0.0f };

      static float constexpr max_distance_to_house_corner_{ 256.0f };
      static float constexpr epsilon_{ 1.0f };

      HouseCornersType house_corners_{};
      HouseCornersType::iterator closest_house_corner_{ house_corners_.end() };
      Elite::Vector2 scanner_{};
   };
}

#endif