#include "CFreeTypeFont.h"
#include "CRender.h"
#include "CTextureManager.h"
#include "CTexture.h"
#include "CSampler.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////

	inline int next_p2(int _n)
	{
		int res = 1;
		while(res < _n)
		{
			res <<= 1;
		}
		
		return res;
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	CFreeTypeFont::CFreeTypeFont()
		: m_bLoaded(false)
		, m_string("")
	{
		for ( uint i = 0; i < nSize; ++i )
		{
			m_pCharTextures[i] = nullptr;
		}

		m_eTypeNode = TN_FONT;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());
	}


	CFreeTypeFont::~CFreeTypeFont()
	{
		for ( uint i = 0; i < nSize; ++i )
		{
			delete m_pCharTextures[i];
			m_pCharTextures[i] = nullptr;
		}
	}


	void CFreeTypeFont::loadSystemFont(const std::string& _name )
	{
		char buf[512]; 
#ifdef _WIN32
		GetWindowsDirectory(buf, 512);
#endif
		std::string sPath = buf;
		sPath += "\\Fonts\\";
		sPath += _name;

		LOG_CONSOLE( "loading FreeType Font: " << _name.c_str());
		CFreeTypeFont::loadFont(sPath);
	}


	void CFreeTypeFont::loadFont( const std::string& _file )
	{
		if (m_bLoaded)
		{
			ASSERT( false || "Already loaded" );
			return;
		}

		FT_Library ftLib;
		FT_Face ftFace;

		BOOL bError = FT_Init_FreeType( &ftLib );
		if ( bError )
		{
			ASSERT( false || "Error Init Free Type" );
			return;
		}

		bError = FT_New_Face(ftLib, _file.c_str(), 0, &ftFace); 
		if ( bError == FT_Err_Unknown_File_Format ) 
		{ 
			ASSERT( false || "Unknown Font File Format" );
			return;
		} 
		else if ( bError ) 
		{ 
			ASSERT( false || "Font Error" );
			return;
		}

		int iPXSize = 32;
		FT_Set_Pixel_Sizes(ftFace, iPXSize, iPXSize);

		m_vertices.malloc(4 * 128);

		for (uint i = 0; i < 128; ++i)
		{
			CFreeTypeFont::createChar(ftFace,i);
		}
		m_bLoaded = true;

		RENDERER->initBufferObjects(m_vertices);
		m_vertices.clear();

		FT_Done_Face(ftFace);
		FT_Done_FreeType(ftLib);
	}

	void CFreeTypeFont::createChar( const FT_Face& _ftFace, uint _index )
	{
		FT_Load_Glyph(_ftFace, FT_Get_Char_Index(_ftFace, _index), FT_LOAD_DEFAULT);

		FT_Render_Glyph(_ftFace->glyph, FT_RENDER_MODE_NORMAL);
		FT_Bitmap* pBitmap = &_ftFace->glyph->bitmap;

		uint width = pBitmap->width;
		uint hight = pBitmap->rows;
		
		uint iTW = next_p2(width);
		uint iTH = next_p2(hight);

		GLubyte* bData = new GLubyte[iTW*iTH];
		
		// Copy glyph data and add dark pixels elsewhere
		for ( uint ch = 0; ch < iTH; ++ ch)
		{
			for ( uint cw = 0; cw < iTW; ++cw )
			{
				bData[ch*iTW+cw] = (ch >= hight || cw >= width) ? 0 : pBitmap->buffer[(hight-ch-1)*width+cw];
			}
		}

		//texture
		if (m_pCharTextures[_index])
		{
			delete m_pCharTextures[_index];
			m_pCharTextures[_index] = nullptr;
		}
		m_pCharTextures[_index] = TEXTURE_MGR->createTexture2DFromData(iTW,iTH,IF_DEPTH_COMPONENT,IT_UNSIGNED_BYTE,bData);
		m_pCharTextures[_index]->getSampler()->setFilterType(FT_LINEAR, FT_LINEAR);
		m_pCharTextures[_index]->getSampler()->setWrapType(WT_CLAMP_TO_EDGE);

		// Calculate glyph data
		m_iAdvX[_index] = _ftFace->glyph->advance.x>>6;
		m_iBearingX[_index] = _ftFace->glyph->metrics.horiBearingX>>6;
		m_iCharWidth[_index] = _ftFace->glyph->metrics.width>>6;

		m_iAdvY[_index] = (_ftFace->glyph->metrics.height - _ftFace->glyph->metrics.horiBearingY)>>6;
		m_iBearingY[_index] = _ftFace->glyph->metrics.horiBearingY>>6;
		m_iCharHeight[_index] = _ftFace->glyph->metrics.height>>6;

		m_iNewLine = max(m_iNewLine, int(_ftFace->glyph->metrics.height>>6));
		
		delete[] bData;
		

		m_vertices.Vertex.vertices[_index*4].setX(0.0f);
		m_vertices.Vertex.vertices[_index*4].setY(float(-m_iAdvY[_index]+iTH));
		m_vertices.Vertex.vertices[_index*4].setZ(0.0f);

		m_vertices.Vertex.vertices[_index*4+1].setX(0.0f);
		m_vertices.Vertex.vertices[_index*4+1].setY(float(-m_iAdvY[_index]));
		m_vertices.Vertex.vertices[_index*4+1].setZ(0.0f);

		m_vertices.Vertex.vertices[_index*4+2].setX(float(iTW));
		m_vertices.Vertex.vertices[_index*4+2].setY(float(-m_iAdvY[_index]+iTH));
		m_vertices.Vertex.vertices[_index*4+2].setZ(0.0f);

		m_vertices.Vertex.vertices[_index*4+3].setX(float(iTW));
		m_vertices.Vertex.vertices[_index*4+3].setY(float(-m_iAdvY[_index])	);
		m_vertices.Vertex.vertices[_index*4+3].setZ(0.0f);


		m_vertices.TexCoord.at(0).vertices[_index*4].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_index*4].setY(1.0f);

		m_vertices.TexCoord.at(0).vertices[_index*4+1].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_index*4+1].setY(0.0f);

		m_vertices.TexCoord.at(0).vertices[_index*4+2].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_index*4+2].setY(1.0f);

		m_vertices.TexCoord.at(0).vertices[_index*4+3].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_index*4+3].setY(0.0f);
	}

	void CFreeTypeFont::render()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		int iCurX = x, iCurY = y;
		if(iPXSize == -1)iPXSize = m_iLoadedPixelSize;
		float fScale = float(iPXSize)/float(m_iLoadedPixelSize);

		for ( int chunk = 0; chunk < m_string.size(); ++ chunk)
		{
			if(m_string[chunk] == '\n')
			{
				iCurX = x;
				iCurY -= m_iNewLine*iPXSize/m_iLoadedPixelSize;
				continue;
			}
			int iIndex = int(m_string[chunk]);
			iCurX += m_iBearingX[iIndex]*iPXSize/m_iLoadedPixelSize;
			if(m_string[chunk] != ' ')
			{
				m_pCharTextures[iIndex].bindTexture();
				glm::mat4 mModelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(iCurX), float(iCurY), 0.0f));
				mModelView = glm::scale(mModelView, glm::vec3(fScale));
				shShaderProgram->setUniform("modelViewMatrix", mModelView);
				// Draw character
				glDrawArrays(GL_TRIANGLE_STRIP, iIndex*4, 4);
			}

			iCurX += (m_iAdvX[iIndex]-m_iBearingX[iIndex])*iPXSize/m_iLoadedPixelSize;
		}
		glDisable(GL_BLEND);
	}
	
	void CFreeTypeFont::update( double _deltaTime )
	{
	}

	void CFreeTypeFont::init()
	{
	}

	///////////////////////////////////////////////////////////////////////////////////////////
}