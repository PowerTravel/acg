#ifndef MAIN_WINDOW_CPP
#define MAIN_WINDOW_CPP

class MainWindow
{

	public:
		MainWindow();
		MainWindow(int x, int y);
		virtual ~MainWindow();
	
		bool isZombie();
		bool isRunning();

		void getInput();
		void update();
		void draw();

		Rect getSize();
		void setSize(Rect r);

	private:
		
		int windowID;
			
		
};

#endif // MAIN_WINDOW_CPP
