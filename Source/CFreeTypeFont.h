#ifndef _CFREETYPEFONT_H_
#define _CFREETYPEFONT_H_

#include "CFont.h"

#include <ft2build.h> 
#include FT_FREETYPE_H
#include FT_STROKER_H

#ifdef _DEBUG
#	pragma comment(lib, "freetype250_D.lib")
#else
#	pragma comment(lib, "freetype250.lib")
#endif

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////

	struct SCharDesc
	{
		uint	_iWidth;
		uint	_iHeight;
		int		_iAdvX;
		int		_iAdvY;
		int		_iBearingX;
		int		_iBearingY;
		uint	_page;
	};

	///////////////////////////////////////////////////////////////////////////////////////////

	class CTexture;
	class CShader;

	const uint	nSize = 256U;

	class CFreeTypeFont : public CFont
	{
	private:

		SVertexData	m_vertices;

		FT_Library	m_Library;
		FT_Face		m_Face;
		
		std::map<int,SCharDesc> m_charInfo;
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

		void		copyToTexture( uint _width, uint _height, uchar* _data, SCharDesc* _charDesc );
		void		createChar( const  const FT_Face& _ftFace, FT_UInt _glyphIndex );
		void		loadFont( const std::string& _file );
		bool		loadCharToMap( int _char );

		uint		m_xOffTextures;
		uint		m_yOffTextures;
		uint		m_currentTextureIndx;

		//std::vector<CMaterial>	m_charMaterial;
		std::vector<CTexture*>	m_charMaterial;

	public:

		CFreeTypeFont( CNode* _parent = nullptr );
		virtual		~CFreeTypeFont();

		void		loadSystemFont( const std::string& _name );

		void		render();
		void		update( double _deltaTime );

		void		init();

	};

	///////////////////////////////////////////////////////////////////////////////////////////
}

#endif