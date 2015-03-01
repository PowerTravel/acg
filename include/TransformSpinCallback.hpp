#ifndef TRANSFORM_SPIN_CALLBACK 
#define TRANSFORM_SPIN_CALLBACK 

#include "UpdateCallback.hpp"
#include "Vec3.hpp"

#ifndef TRANSFORM_PTR
#define TRANSFORM_PTR
class Transform;
typedef std::shared_ptr<Transform> transform_ptr;
#endif // TRANSFORM_PTR


class TransformSpinCallback : public UpdateCallback
{
	public:

		TransformSpinCallback(transform_ptr t);
		TransformSpinCallback(transform_ptr t, float angle, Vec3 axis);
		virtual ~TransformSpinCallback();
	
		void setAngleAxis( float angle, Vec3 axis);
		void execute();

	private:
		transform_ptr _t;
		float _angle;
		Vec3 _axis;
};

#endif // TRANSFORM_SPIN_CALLBACK 
