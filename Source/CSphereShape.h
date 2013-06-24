#ifndef _CSPHERESHAPE_H_
#define _CSPHERESHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CSphereShape : public CShape
	{
	protected:

		uint		m_iSlices; 
		uint		m_iStacks;
		float		m_fRadius;

		void		init();

	public:

		CSphereShape( CNode* _pParent = nullptr );
		virtual		~CSphereShape();

		void		render();
		void		update( double _dDeltaTime );

		void		setSlices( const uint _iValue );
		void		setStacks( const uint _iValue );
		void		setRadius( const float _iRadius );

		uint		getSlices() const;
		uint		getStacks() const;
		float		getRadius() const;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif