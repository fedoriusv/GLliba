#ifndef _CCYLINDERSHAPE_H_
#define _CCYLINDERSHAPE_H_

#include "CShape.h"

namespace glliba
{

	//////////////////////////////////////////////////////////////////////////////////////////////

	class CCylinderShape : public CShape
	{
	protected:

		float				m_fRadius;
		float				m_fHeight;

		void				init();

	public:

		CCylinderShape( CNode* _pParent = nullptr );
		virtual				~CCylinderShape();

		void				render();
		void				update( double _dDeltaTime );

		void				setRadius( const float _fRadius );
		void				setHeight( const float _fHeight );

		float				getRadius() const;
		float				getHeight() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif