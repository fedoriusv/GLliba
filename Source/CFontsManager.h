#ifndef _CFONTSMANAGER_H_
#define _CFONTSMANAGER_H_

#include "Types.h"

namespace glliba
{
	class CFont;
	typedef std::map<std::string,CFont*>	FontList;
	typedef std::pair<std::string,CFont*>	FontPair;

	class CFontsManager
	{
	private:

		FontList	m_fonts;

	public:

		CFontsManager();
		~CFontsManager();
		CFont*		createFont( const std::string& _fontName );
		void		destroyFont( const std::string& _fontName );

	};
}

#endif