#ifndef _CCYLINDERSHAPE_H_
#define _CCYLINDERSHAPE_H_

#include "CShape.h"

namespace glliba
{

	//////////////////////////////////////////////////////////////////////////////////////////////

	class CCylinderShape : public CShape
	{
	protected:

		float			m_fRadius;
		float			m_fHeight;

		void			init();

	public:

		CCylinderShape( CNode* _parent = nullptr );
		virtual			~CCylinderShape();

		void			render();
		void			update( double _deltaTime );

		void			setRadius( const float _radius );
		void			setHeight( const float _height );

		float			getRadius() const;
		float			getHeight() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif