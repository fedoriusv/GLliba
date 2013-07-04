#include "CFont.h"

namespace glliba
{
	CFont::CFont( CNode* _parent )
		: CNode(_parent)
		, m_bLoaded(false)
		, m_string("")
		, m_iSize(24U)
	{

	}


	CFont::~CFont()
	{
	}


	void CFont::setFontString( const std::string& _string )
	{
		m_string = _string;
	}


	std::string CFont::getFontString() const
	{
		return m_string;
	}


	void CFont::setFontSize( const uint _size )
	{
		m_iSize = _size;
	}


	uint CFont::getFontSize() const
	{
		return m_iSize;
	}
}