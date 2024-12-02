#ifndef FRONCU_AGENT_PLUGIN_HPP
#define FRONCU_AGENT_PLUGIN_HPP

#include "pch.hpp"

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
   virtual void InitGameDebugParams(GameDebugParams&) override {}
   // Called once every frame (only in debug mode)
   virtual void Update_Debug(float) override {}
   // Additional renderering (only in debug mode)
   virtual void Render(float) const override {}

private:
   IExamInterface* interface_{};
};

extern "C"
{
   __declspec (dllexport) IPluginBase* Register()
   {
      return new FroncuAgentPlugin();
   }
}

#endif