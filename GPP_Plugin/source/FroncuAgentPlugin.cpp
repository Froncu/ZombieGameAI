#include "pch.hpp"

#include "FroncuAgentPlugin.hpp"

namespace ai
{
   void FroncuAgentPlugin::DllInit()
   {
      srand(static_cast<int>(time(nullptr)));
   }

   void FroncuAgentPlugin::Initialize(IBaseInterface* const interface, PluginInfo& info)
   {
      interface_ = static_cast<IExamInterface* const>(interface);
      state_machine_ = std::make_unique<FSMType>(interface_);

      // information for the leaderboards!
      info.BotName = "xXx_-_RECORD_-_SMASHER_-_xXx";
      info.Student_Name = "JAKUB FRATCZAK"; // no special characters allowed
      info.Student_Class = "2DAE10";
      info.LB_Password = "BigBoss04!";
   }

   SteeringPlugin_Output FroncuAgentPlugin::UpdateSteering(float const delta_seconds)
   {
      return state_machine_->Update(delta_seconds);
   }

   void FroncuAgentPlugin::Render(float const delta_seconds) const
   {
      state_machine_->Render(delta_seconds);
   }

   void FroncuAgentPlugin::InitGameDebugParams(GameDebugParams& parameters)
   {
      parameters.Seed = int(time(nullptr));

      std::cout << std::format("\n[SEED IN USE: {}]\n\n", parameters.Seed);
   }
}