#ifndef _CPLANESHAPE_H_
#define _CPLANESHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CPlaneShape : public CShape
	{
	protected:

		float				m_fExtent;

		void				init();

	public:

		CPlaneShape( CNode* _parent = NULL );
		virtual				~CPlaneShape();

		void				setExtent( const float _extent );
		float				getExtent() const;

		void				render();
		void				update( double _dDeltaTime );

	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif