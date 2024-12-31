#pragma once
#define MAX_JOYSTICK_BUTTONS 18

#define TIGER_GAMEPAD_A 0
#define TIGER_GAMEPAD_B 1
#define TIGER_GAMEPAD_X 2
#define TIGER_GAMEPAD_Y 3
#define TIGER_GAMEPAD_LEFT_BUMPER 4
#define TIGER_GAMEPAD_RIGHT_BUMPER 5
#define TIGER_GAMEPAD_BACK 6
#define TIGER_GAMEPAD_START 7
#define TIGER_GAMEPAD_GUIDE 8
#define TIGER_GAMEPAD_LEFT_THUMB 9
#define TIGER_GAMEPAD_RIGHT_THUMB 10
#define TIGER_GAMEPAD_DPAD_UP 11
#define TIGER_GAMEPAD_DPAD_RIGHT 12
#define TIGER_GAMEPAD_DPAD_DOWN 13
#define TIGER_GAMEPAD_DPAD_LEFT 14
#define TIGER_GAMEPAD_LAST   TIGER_GAMEPAD_DPAD_LEFT
#define TIGER_GAMEPAD_CROSS TIGER_GAMEPAD_A
#define TIGER_GAMEPAD_CIRCLE   TIGER_GAMEPAD_B
#define TIGER_GAMEPAD_SQUARE   TIGER_GAMEPAD_X
#define TIGER_GAMEPAD_TRIANGLE   TIGER_GAMEPAD_Y

namespace tiger {

	class JoystickInputData
	{
		friend class JoystickManager;

	public:

		JoystickInputData(char id = 0);
		~JoystickInputData();

		inline void setConnection(bool isConnected) { m_Connected = isConnected; }
		inline void setId(char id) { m_Id = id; }
		inline void setDeadzone(float dead) { m_Deadzone = dead; }
		inline char getNumButtons() { return m_NumButtons; }
		inline glm::vec2& getLeftStick() { return m_LeftStick; }
		inline glm::vec2& getRightStick() { return m_RightStick; }
		inline glm::vec2& getTriggers() { return m_Triggers; }
		inline bool isConnected() { return m_Connected; }

		void update();

	private:
		unsigned char m_ButtonStates[MAX_JOYSTICK_BUTTONS];

		bool m_Connected;
		char m_Id;
		int m_NumButtons;
		float m_Deadzone;
		glm::vec2 m_LeftStick;
		glm::vec2 m_RightStick;
		glm::vec2 m_Triggers;
	};
}