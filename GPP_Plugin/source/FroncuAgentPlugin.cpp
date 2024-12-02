#include "pch.hpp"

#include "FroncuAgentPlugin.hpp"

void FroncuAgentPlugin::Initialize(IBaseInterface* const interface, PluginInfo& info)
{
   interface_ = static_cast<IExamInterface* const>(interface);

   // information for the leaderboards!
   info.BotName = "xXx_-_RECORD_-_SMASHER_-_xXx";
   info.Student_Name = "JAKUB FRATCZAK"; // no special characters allowed
   info.Student_Class = "2DAE10";
   info.LB_Password = "BigBoss04!";
}

SteeringPlugin_Output FroncuAgentPlugin::UpdateSteering(float)
{
   return SteeringPlugin_Output
   {
      .LinearVelocity{ 100.0f, 0.0f },
      .RunMode{ true }
   };
}