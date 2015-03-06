#ifndef KEYSTATE_HPP
#define KEYSTATE_HPP


void glut_key_callback(unsigned char c, int x, int y);
void resize_callback(int width, int height);

class KeyState{
	
	public:

		enum State {
			KEY_NULL = 0,
			KEY_A = 2,
			KEY_B = 4,
			KEY_C = 8,
			KEY_D = 16,
			KEY_E = 32,  
			KEY_F = 64,
			KEY_G = 128,
			KEY_H = 256,
			KEY_I = 512,
			KEY_J = 1024,
			KEY_K = 2048,
			KEY_L = 4096,
			KEY_M = 8192,
			KEY_N = 16384,
			KEY_O = 32768,
			KEY_P = 65536,
			KEY_Q = 131072,
			KEY_R = 262144,
			KEY_S = 524288,
			KEY_T = 1048576,
			KEY_U = 2097152,
			KEY_V = 4194304,
			KEY_W = 8388608,
			KEY_X = 16777216,
			KEY_Y = 33554432,
			KEY_Z = 67108864
		};

		static KeyState& getInstance(); 

		bool hasWindowChanged();
		void windowChanged();
		void setGlutCallback();
		State get();
		void set(int st);

	private:
		static State _state;
		static bool mWindowChanged;
		
		KeyState();
		virtual ~KeyState();
	
		KeyState(KeyState const&) = delete;
		void operator=(KeyState const&) = delete;
};

#ifndef KEY_STATE_BIT
#define KEY_STATE_BIT
typedef KeyState::State key_state_bit;
#endif // KEY_STATE_BIT


#endif // KEYSTATE
