#include "CFontsManager.h"
#include "CFont.h"
#include "CFreeTypeFont.h"
#include "Utils.h"

namespace glliba
{
	CFontsManager::CFontsManager()
	{
	}

	CFontsManager::~CFontsManager()
	{
	}

	CFont* CFontsManager::createFont( const std::string& _fontName )
	{
		std::string fontName = _fontName;
		Utils::transformString(fontName);

		if (m_fonts.find(_fontName) != m_fonts.end())
		{
			return (CFont*)m_fonts[_fontName]->getRef();
		}

		CFont* newFont = new CFreeTypeFont();
		newFont->loadFont(_fontName);

	}

	void CFontsManager::destroyFont( const std::string& _fontName )
	{

	}
}