#ifndef _CDCCAMERA_H_
#define _CDCCAMERA_H_

#include "CCamera.h"
#include "CReciever.h"

namespace glliba
{
	class CReciever;

	class CDCCamera : public CCamera
	{
	protected:
		
	public:
		CDCCamera( CNode* _parent = nullptr );
		virtual		~CDCCamera();
		void		update();


	};
}

#endif