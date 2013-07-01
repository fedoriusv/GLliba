#ifndef _CFREETYPEFONT_H_
#define _CFREETYPEFONT_H_

#include "CNode.h"

#include <ft2build.h> 
#include FT_FREETYPE_H

#ifdef _DEBUG
#	pragma comment(lib, "freetype250_D.lib")
#else
#	pragma comment(lib, "freetype250.lib")
#endif

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////
	class CTexture;
	class CShader;

	const uint	nSize = 256U;

	class CFreeTypeFont : public CNode
	{
	private:

		SVertexData	m_vertices;
		
		CTexture*	m_pCharTextures[nSize];
		CShader*	m_pShader;
		Vector4		m_color;

		uint		m_iCharWidth[nSize];
		uint		m_iCharHeight[nSize];
		int			m_iAdvX[nSize];
		int			m_iAdvY[nSize];
		int			m_iBearingX[nSize];
		int			m_iBearingY[nSize];

		int			m_iNewLine;
		int			m_iLoadedPixelSize;

		bool		m_bLoaded;
		std::string m_string;

		void		createChar( const FT_Face& _ftFace, FT_UInt _glyphIndex );
		void		loadFont( const std::string& _file );

	public:

		CFreeTypeFont();
		virtual		~CFreeTypeFont();

		void		loadSystemFont( const std::string& _name );

		void		render();
		void		update( double _deltaTime );

		void		init();
	};

	///////////////////////////////////////////////////////////////////////////////////////////
}

#endif