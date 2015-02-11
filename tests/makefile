quaterniontest:
	g++ -std=c++11 quaterniontest.cpp ../src/Quaternion.cpp ../src/Vec3.cpp ../src/Vec4.cpp -I../include -o quaternion.out

nodetest:
	g++ -std=c++11 nodetest.cpp ../src/Node.cpp -I../include -o nodetest.out

pqueuetest:
	g++ -std=c++11 pqueuetest.cpp -I../include -o pqueuetest.out

listtest:
	g++ -std=c++11 listtest.cpp -I../include -o listtest.out

objectmanager:
	g++ -std=c++11 objectmanagertest.cpp ../src/ObjectManager.cpp ../src/Vec3.cpp -I../include -lGLEW -lassimp -o objectmanagertest.out

vec3:
	g++ -std=c++11 vec3test.cpp ../src/Vec3.cpp -I../include -o vec3test.out

vec4:
	g++ -std=c++11 vec4test.cpp ../src/Vec4.cpp -I../include -o vec4test.out

hmat:
	g++ -std=c++11 hmattest.cpp ../src/Hmat.cpp ../src/Vec3.cpp  ../src/Vec4.cpp -I../include -o hmattest.out

timer:
	g++ -std=c++11 timertest.cpp ../src/Timer.cpp -I../include -o timertest.out
	

clean:
	rm -f *.out
