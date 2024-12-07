#ifndef FRONCU_AGENT_PLUGIN_HPP
#define FRONCU_AGENT_PLUGIN_HPP

#include "pch.hpp"

#include "ExploringState.hpp"
#include "FSM.hpp"
#include "SeesHousesCondition.hpp"
#include "SearchingState.hpp"

namespace ai
{
   class FroncuAgentPlugin : public IExamPlugin
   {
      using FSMType = FSM<ExploringState, SearchingState, SeesHousesCondition>;

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
      virtual void Update_Debug(float) override {};

   private:
      IExamInterface* interface_{};

      std::unique_ptr<FSMType> state_machine_{};
   };
}

#endif