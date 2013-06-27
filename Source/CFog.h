#ifndef _CFOG_H_
#define _CFOG_H_

#include "CNode.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SFogData
	{
		Vector4   _color;
		float     _fStart;
		float     _fEnd;
		FOG_MODE  _eMode;
		float     _fDensity;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CScene;

	class CFog : public CNode
	{
	protected:

		friend		CSceneManager;

		SFogData	m_sFogData;

		std::string	m_attribute;
		
		bool		m_bActive;
		bool		m_bEnabled;

		void		init();

	public:

		CFog();
		virtual		~CFog();

		void		setColor( const Vector4& _color );
		Vector4		getColor() const;

		void		setMode( FOG_MODE _mode );
		FOG_MODE	getMode() const;

		void		setDensity( const float _density );
		float		getDensity() const;

		void		setStart( const float _start );
		float		getStart() const;

		void		setEnd( const float _end );
		float		getEnd() const;

		bool		isActive() const;

		void		render();
		void		update( double _deltaTime );

		void		setEnabled( bool _enabled );
		bool		getEnabled() const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif