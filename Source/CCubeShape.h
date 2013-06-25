#ifndef _CCUBESHAPE_H_
#define _CCUBESHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CCubeShape : public CShape
	{
	protected:
		void				init();

	public:

		CCubeShape( CNode* _parent = nullptr );
		virtual				~CCubeShape();

		void				render();
		void				update( double _deltaTime );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif