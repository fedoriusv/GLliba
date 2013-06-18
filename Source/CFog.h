#ifndef _CFOG_H_
#define _CFOG_H_

#include "CNode.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SFogData
	{
		Vector4		m_color;
		float		m_fStart;
		float		m_fEnd;
		FOG_MODE	m_eMode;
		float		m_fDensity;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CScene;

	class CFog : public CNode
	{
	protected:

		friend		CSceneManager;

		SFogData	m_sFogData;
		
		bool		m_bActive;
		bool		m_bEnabled;

		void		init();

	public:

		CFog();
		virtual		~CFog();

		void		setColor(const Vector4& _color );
		Vector4		getColor() const;

		void		setMode( FOG_MODE _eMode );
		FOG_MODE	getMode() const;

		void		setDensity( const float _fDensity );
		float		getDensity() const;

		void		setStart( const float _fStart );
		float		getStart() const;
		void		setEnd( const float _fEnd );
		float		getEnd() const;

		bool		isActive() const;

		void		render();
		void		update( double _dDeltaTime );

		void		setEnabled( bool _bEnabled );
		bool		getEnabled() const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif