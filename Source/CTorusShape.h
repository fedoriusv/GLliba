#ifndef _CTORUSSHAPE_H_
#define _CTORUSSHAPE_H_

#include "CShape.h"

namespace glliba
{

	//////////////////////////////////////////////////////////////////////////////////////////////

	class CTorusShape : public CShape
	{
	protected:

		float			m_fMajorRadius;
		float			m_fMinorRadius;
		
		void			init();

	public:

		CTorusShape( CNode* _parent = nullptr );
		virtual			~CTorusShape();

		void			render();
		void			update( double _deltaTime );

		void			setMinorRadius( const float _radius );
		void			setMajorRadius( const float _radius );

		float			getMinorRadius() const;
		float			getMajorRadius() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif