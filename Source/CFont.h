#ifndef _CFONT_H_
#define _CFONT_H_

#include "CNode.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////

	class CFontsManager;

	class CFont : public CNode
	{
	protected:
		friend		CFontsManager;

		bool		m_bLoaded;

		std::string	m_string;
		uint		m_iSize;

		short		m_iTexWidth;
		short		m_iTexHight;

		virtual void loadFont( const std::string& _file ) = 0;

	public:
		CFont( CNode* _parent = nullptr );
		virtual		~CFont();

		void		setFontString( const std::string& _string );
		std::string	getFontString() const;

		void		setFontSize( const uint _size );
		uint		getFontSize() const;
	};

	///////////////////////////////////////////////////////////////////////////////////////////
}

#endif