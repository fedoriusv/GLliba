#ifndef _CDISKSHAPE_H_
#define _CDISKSHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CDiskShape : public CShape
	{
	protected:

		uint				m_iSegmentsCount;
		float				m_fRadius;

		void				init();

	public:

		CDiskShape( CNode* _parent = NULL );
		virtual				~CDiskShape();

		void				setRadius( const float& _radius );
		void				setSegmentsCount( const uint& _count );

		float				getRadius() const;

		void				render();
		void				update( double _dDeltaTime );
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif