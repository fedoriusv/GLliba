#ifndef _CSPHERESHAPE_H_
#define _CSPHERESHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CSphereShape : public CShape
	{
	protected:

		uint				m_polyCount;

		void				init();

	public:

		CSphereShape( CNode* _pParent = NULL );
		virtual				~CSphereShape();

		void				render();
		void				update( double _dDeltaTime );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif