#include "Timer.hpp"
#include <cstdio>

int main()
{
	int sec = 1000000;
	int tol = 100;
	Timer t1 = Timer();
	Timer t2 = Timer();
	t1.start();
	t2.start();
	
	bool stopped = false;
	while(t1.getTime() < 3*sec)
	{
		if(t1.getTime() > 1*sec && stopped==false ){
			stopped = true;
			t2.pause();
		}

		if(t1.getTime() > 2*sec && t2.isPaused() ){
			t2.unpause();
		}
	}
	float timeDiff = t1.getTime()-t2.getTime();
	if(  timeDiff < sec-tol || timeDiff > sec+tol )
	{
		printf(" TEST FAILURE \n");
		return 1;
	}
	printf("t1 = %f, t2 = %f \n", t1.getTime()/sec, t2.getTime()/sec );

	return 0;
}
