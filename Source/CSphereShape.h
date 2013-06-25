#ifndef _CSPHERESHAPE_H_
#define _CSPHERESHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CSphereShape : public CShape
	{
	protected:

		uint		m_nSlices; 
		uint		m_nStacks;
		float		m_fRadius;

		void		init();

	public:

		CSphereShape( CNode* _parent = nullptr );
		virtual		~CSphereShape();

		void		render();
		void		update( double _deltaTime );

		void		setSlices( const uint _value );
		void		setStacks( const uint _value );
		void		setRadius( const float _radius );

		uint		getSlices() const;
		uint		getStacks() const;
		float		getRadius() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif