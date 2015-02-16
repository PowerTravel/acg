#ifndef UPDATE_CALLBACK_HPP  
#define UPDATE_CALLBACK_HPP

#include <memory>

class Node;

#ifndef CALLBACK_PTR
#define CALLBACK_PTR
class UpdateCallback;
typedef std::shared_ptr<UpdateCallback> callback_ptr;
#endif // CALLBACK_PTR

class UpdateCallback{

	public:
		virtual void execute() = 0;	
	private:

};


#endif // UPDATE_CALLBACK_HPP

