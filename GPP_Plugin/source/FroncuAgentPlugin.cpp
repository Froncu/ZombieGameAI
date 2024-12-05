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

      // information for the leaderboards!
      info.BotName = "xXx_-_RECORD_-_SMASHER_-_xXx";
      info.Student_Name = "JAKUB FRATCZAK"; // no special characters allowed
      info.Student_Class = "2DAE10";
      info.LB_Password = "BigBoss04!";
   }

   SteeringPlugin_Output FroncuAgentPlugin::UpdateSteering(float const)
   {
      return {};
   }

   void FroncuAgentPlugin::Render(float const) const
   {
   }

   void FroncuAgentPlugin::InitGameDebugParams(GameDebugParams& parameters)
   {
      parameters.Seed = int(time(nullptr));

      std::cout << std::format("\n[SEED IN USE: {}]\n\n", parameters.Seed);
   }
}