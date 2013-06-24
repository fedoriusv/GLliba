#ifndef _CTORUSSHAPE_H_
#define _CTORUSSHAPE_H_

#include "CShape.h"

namespace glliba
{

	//////////////////////////////////////////////////////////////////////////////////////////////

	class CTorusShape : public CShape
	{
	protected:

		float			m_majorRadius;
		float			m_minorRadius;
		
		void			init();

	public:

		CTorusShape( CNode* _pParent = nullptr );
		virtual			~CTorusShape();

		void			render();
		void			update( double _dDeltaTime );

		void			setMinorRadius( const float _fRadius );
		void			setMajorRadius( const float _fRadius );

		float			getMinorRadius() const;
		float			getMajorRadius() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif