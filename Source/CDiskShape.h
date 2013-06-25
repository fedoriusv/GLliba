#ifndef _CDISKSHAPE_H_
#define _CDISKSHAPE_H_

#include "CShape.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	class CDiskShape : public CShape
	{
	protected:

		uint		m_nSlices; 
		uint		m_nStacks;

		float		m_fInnerRadius;
		float		m_fOuterRadius;

		void		init();

	public:

		CDiskShape( CNode* _parent = nullptr );
		virtual		~CDiskShape();

		void		render();
		void		update( double _deltaTime );

		void		setSlices( const uint _value );
		void		setStacks( const uint _value );
		void		setInnerRadius( const float _radius );
		void		setOuterRadius( const float _radius );

		uint		getSlices() const;
		uint		getStacks() const;
		float		getInnerRadius() const;
		float		getOuterRadius() const;

	};

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif