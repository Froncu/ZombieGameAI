#include "pch.hpp"

#include "FroncuAgentPlugin.hpp"

extern "C"
{
   __declspec (dllexport) IPluginBase* Register()
   {
      return new ai::FroncuAgentPlugin();
   }
}