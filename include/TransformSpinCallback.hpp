#ifndef TRANSFORM_SPIN_CALLBACK 
#define TRANSFORM_SPIN_CALLBACK 

#include "UpdateCallback.hpp"

#ifndef TRANSFORM_PTR
#define TRANSFORM_PTR
class Transform;
typedef std::shared_ptr<Transform> transform_ptr;
#endif // TRANSFORM_PTR

class TransformSpinCallback : public UpdateCallback
{
	public:

		TransformSpinCallback(transform_ptr t);
		virtual ~TransformSpinCallback();
	
		void execute();

	private:
		transform_ptr _t;
};

#endif // TRANSFORM_SPIN_CALLBACK 
