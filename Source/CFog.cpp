#include "CFog.h"

#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFog::CFog()
		: CNode(nullptr)
		, m_attribute("fog")
		, m_bActive(false)
		, m_bEnabled(true)
	{
		m_sFogData._color    = Vector4(1.0f);
		m_sFogData._fStart   = 5.0f;
		m_sFogData._fEnd     = 30.0f;
		m_sFogData._eMode    = FM_EXP;
		m_sFogData._fDensity = 0.5f;

		m_eTypeNode = TN_FOG;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFog::~CFog()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::init()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setColor( const Vector4& _color )
	{
		m_sFogData._color = _color;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector4	CFog::getColor() const
	{
		return m_sFogData._color;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setMode( FOG_MODE _mode )
	{
		m_sFogData._eMode = _mode;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	FOG_MODE CFog::getMode() const
	{
		return m_sFogData._eMode;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setDensity( const float _density )
	{
		m_sFogData._fDensity  =_density;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	float CFog::getDensity() const
	{
		return m_sFogData._fDensity;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setStart( const float _start )
	{
		m_sFogData._fStart = _start;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	float CFog::getStart() const
	{
		return m_sFogData._fStart;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setEnd( const float _end )
	{
		m_sFogData._fEnd = _end;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	float CFog::getEnd() const
	{
		return m_sFogData._fEnd;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CFog::isActive() const
	{
		return m_bActive;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::render()
	{
		if (!m_bActive)
		{
			return;
		}

		RENDERER->renderFog( m_attribute, m_sFogData );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::update( double _deltaTime )
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CFog::setEnabled( bool _enabled )
	{
		m_bEnabled = _enabled;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CFog::getEnabled() const
	{
		return m_bEnabled;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}