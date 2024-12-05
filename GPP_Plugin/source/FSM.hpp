// based on Andries Geens' implementation
// http://www.gameaipro.com/GameAIPro3/GameAIPro3_Chapter12_A_Reusable_Light-Weight_Finite-State_Machine.pdf

#ifndef FSM_HPP
#define FSM_HPP

#include "pch.hpp"

#include "FSMState.hpp"
#include "FSMCondition.hpp"

namespace ai
{
   template<typename Derived, typename Base>
   concept StrictlyDerivedFrom = std::derived_from<Derived, Base> and not std::same_as<Derived, Base>;

   template<StrictlyDerivedFrom<FSMState> From, StrictlyDerivedFrom<FSMState> To, StrictlyDerivedFrom<FSMCondition> Condition, typename... Rest>
   consteval bool ValidateTransitionsPack()
   {
      if constexpr (std::same_as<From, To>)
         return false;

      else if constexpr (not sizeof...(Rest))
         return true;

      else
      {
         using CurrentTransitionTuple = std::tuple<From, To, Condition>;
         using RestTuple = std::tuple<Rest...>;
         using NextTransitionTuple = std::tuple<
            std::tuple_element_t<0, RestTuple>,
            std::tuple_element_t<1, RestTuple>,
            std::tuple_element_t<2, RestTuple>>;

         return not std::same_as<CurrentTransitionTuple, NextTransitionTuple> and ValidateTransitionsPack<Rest...>();
      }
   }

   template<typename From, typename To, typename Condition, typename... Rest>
      requires (ValidateTransitionsPack<From, To, Condition, Rest...>())
   class FSM final
   {
      using TransitionsMap = std::unordered_map<FSMState*, std::vector<std::pair<FSMState*, FSMCondition*>>>;

   public:
      FSM(IExamInterface* const interface)
         : current_state_{ ExtractTransitions<From, To, Condition, Rest...>(interface) }
      {
         current_state_->first->OnEnter();
      };

      FSM(FSM const&) = delete;
      FSM(FSM&&) noexcept = delete;

      FSM& operator=(FSM const&) noexcept = delete;
      FSM& operator=(FSM&&) = delete;

      ~FSM() = default;

      [[nodiscard]] SteeringPlugin_Output Update(float delta_sconds)
      {
         for (auto&& [state, condition] : current_state_->second)
            if (condition->Evaluate())
            {
               current_state_->first->OnExit();
               current_state_ = transitions_.find(state);
               current_state_->first->OnEnter();
               break;
            }

         return current_state_->first->Update(delta_sconds);
      }

      void Render(float const delta_seconds)
      {
         current_state_->first->Render(delta_seconds);
      }

   private:
      template<typename From, typename To, typename Condition, typename... Rest>
         requires (ValidateTransitionsPack<From, To, Condition, Rest...>())
      [[nodiscard]] TransitionsMap::iterator ExtractTransitions(IExamInterface* const interface)
      {
         std::unique_ptr<FSMState>& from{ states_[std::type_index(typeid(From))] };
         if (not from.get())
            from = std::make_unique<From>(interface);

         std::unique_ptr<FSMState>& to{ states_[std::type_index(typeid(To))] };
         if (not to.get())
            to = std::make_unique<To>(interface);

         std::unique_ptr<FSMCondition>& condition{ conditions_[std::type_index(typeid(Condition))] };
         if (not condition.get())
            condition = std::make_unique<Condition>(interface);

         transitions_[from.get()].push_back({ to.get(), condition.get() });

         // recursive calls' return value is ignored, but the top call should not be
         if constexpr (sizeof...(Rest))
            std::ignore = ExtractTransitions<Rest...>(interface);

         return transitions_.begin();
      }

      std::unordered_map<std::type_index, std::unique_ptr<FSMState>> states_{};
      std::unordered_map<std::type_index, std::unique_ptr<FSMCondition>> conditions_{};
      TransitionsMap transitions_{};

      TransitionsMap::iterator current_state_;
   };
}

#endif