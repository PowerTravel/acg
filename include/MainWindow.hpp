#ifndef MAIN_WINDOW_CPP
#define MAIN_WINDOW_CPP

class MainWindow
{
    private:
		
		int windowID;

	public:
		struct Rect{
			int x, y, h, w;
		};		


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

		
};

#endif // MAIN_WINDOW_CPP
