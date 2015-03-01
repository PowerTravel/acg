#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Group.hpp"
#include "Hmat.hpp"
#include "TransformMatrix.hpp"

#ifndef CAMERA_PTR
#define CAMRA_PTR
class Camera;
typedef std::shared_ptr<Camera> camera_ptr;
#endif //CAMERA_PTR

class Camera : public Group
{

	public:
		Camera();
		Camera(Vec3 eye, Vec3 at, Vec3 up);
		virtual ~Camera();

		void acceptVisitor(NodeVisitor& v);
		void update();

		void lookAt(Vec3 v);
		void lookAt(Vec3 eye, Vec3 at, Vec3 up);
		void rotateAroundOrigin(float angle, Vec3 axis);
		void translate(Vec3 t);
		Hmat getProjectionMat();
		Hmat getViewMat();

		void setPerspectiveProjection(float fovy=45.f, float aspect=4.f/3.f, float near=-1.f, float far=-1000.f);
		void setOrthographicProjection(float left=-4.f, float right=4.f, float bottom=-2.f, float top=2.f, float near = -100.f, float far =100.f );
		

	private:
		Hmat _P; // Projection
		TransformMatrix _V;
		float fovy,aspect,near,far;
		float _width;
		float _height;
		
		Vec3 _eye, _at, _up;
		
		void perspective(float fovy, float aspect, float near, float far);
		void orthographic( float left, float right, float bottom,
				    float top,  float near,  float far);


};

#endif // CAMERA_HPP
