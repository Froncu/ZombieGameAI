#ifndef FSM_STATE_HPP
#define FSM_STATE_HPP

namespace ai
{
   class FSMState
   {
   public:
      FSMState() = default;
      FSMState(FSMState const&) = delete;
      FSMState(FSMState&&) = delete;

      virtual ~FSMState() = default;

      FSMState& operator=(FSMState const&) = delete;
      FSMState& operator=(FSMState&&) = delete;

      virtual void OnEnter() = 0;
      virtual void OnExit() = 0;
      virtual void Update(float deltaSeconds) = 0;
   };
}

#endif