#include "CFreeTypeFont.h"
#include "CRender.h"
#include "CTextureManager.h"
#include "CTexture.h"
#include "CSampler.h"
#include "CShaderManager.h"

namespace glliba
{
	const std::string vertShaderFont2D = "data/shaders/ortho2D.vsh";
	const std::string fragShaderFont2D = "data/shaders/font2D.psh";

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

	CFreeTypeFont::CFreeTypeFont( CNode* _parent )
		: CFont(_parent)
		, m_color(1.0f)
		, m_xOffTextures(0)
		, m_yOffTextures(0)
		, m_currentTextureIndx(0)

	{
		for ( uint i = 0; i < nSize; ++i )
		{
			m_pCharTextures[i] = nullptr;
		}

		m_eTypeNode = TN_FONT;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());

		CFreeTypeFont::init();
		m_string = "string\n d f sd^fejkssdhfherusdvvndfhbdfndfkllbndf\n The glyph image that is loaded in a glyph slot can be converted\n into a bitmap, either by using RENDER when loading it\n, or by calling FT_RenderGlyph. Each time you load a new glyph image, the previous\n one is erased from the glyph slot.";
		
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
			ASSERT( false && "Already loaded" );
			return;
		}

		BOOL bError = FT_Init_FreeType( &m_Library );
		if ( bError )
		{
			ASSERT( false && "Error Init Free Type" );
			return;
		}

		bError = FT_New_Face(m_Library, _file.c_str(), 0, &m_Face); 
		if ( bError == FT_Err_Unknown_File_Format ) 
		{ 
			ASSERT( false && "Unknown Font File Format" );
			return;
		} 
		else if ( bError ) 
		{ 
			ASSERT( false && "Font Error" );
			return;
		}

		int iPXSize = 32;
		m_iLoadedPixelSize = iPXSize;
		FT_Set_Pixel_Sizes(m_Face, iPXSize, iPXSize);

		loadCharToMap('.');
		loadCharToMap('a');
		loadCharToMap('b');
		loadCharToMap('a');

		//ftFace->style_flags = ftFace->style_flags | FT_STYLE_FLAG_ITALIC;
		//if(FT_Set_Char_Size(m_FontFace, size << 6, size << 6, 96, 96) != 0)
		//http://www.asciitable.com

		FT_UInt num_chars = 128;
		m_vertices.malloc(4 * num_chars);

		for (uint glyphIndex = 32/*' '*/; glyphIndex < 126/*~*/; ++glyphIndex)
		{
			CFreeTypeFont::createChar( m_Face, glyphIndex );
		}
		m_bLoaded = true;

		RENDERER->initBufferObjects(m_vertices);
		//m_vertices.clear();

		FT_Done_Face(m_Face);
		FT_Done_FreeType(m_Library);

	}


	bool CFreeTypeFont::loadCharToMap( int _char )
	{
		if (m_charInfo.find(_char) != m_charInfo.end())
		{
			return true;
		}

		static float	outline_thikness = 0 * 64;
		FT_Glyph		glyph;
		FT_GlyphSlot	glyphSlot;
		FT_Stroker		stroker;

		if (FT_Load_Glyph(m_Face, FT_Get_Char_Index(m_Face, _char), FT_LOAD_DEFAULT))
		{
			return false;
		}
		glyphSlot = m_Face->glyph;
		
		if(FT_Load_Char(m_Face, FT_Get_Char_Index(m_Face, _char), FT_LOAD_RENDER ))
		{
			return false;
		}

		if(FT_Stroker_New( m_Library, &stroker ))
		{
			return false;
		}

		FT_Stroker_Set( stroker, outline_thikness, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		if(FT_Get_Glyph( m_Face->glyph, &glyph))
		{
			return false;
		}

		//if(FT_Glyph_StrokeBorder( &glyph, stroker, 0, 1 ))//FT_Glyph_Stroke( &glyph, stroker, 1 ))
		//{
		//	return false;
		//}
       
		if(FT_Glyph_To_Bitmap( &glyph, FT_RENDER_MODE_NORMAL/*FT_RENDER_MODE_LCD*/, 0, 1))
		{
			return false;
		}

		FT_BitmapGlyph ft_bitmap_glyph = (FT_BitmapGlyph) glyph;
		FT_Stroker_Done(stroker);
		
		int scale = 1.0f;
		int fontHeight = 1.0f;

		SCharDesc charDscr;
		charDscr._iAdvX = (glyphSlot->advance.x + outline_thikness) / 64 * scale;
		charDscr._iBearingX = ft_bitmap_glyph->left * scale;
		charDscr._iBearingY = fontHeight / 1.2 - ft_bitmap_glyph->top * scale;

		int width = next_p2( ft_bitmap_glyph->bitmap.width );
		int height = next_p2( ft_bitmap_glyph->bitmap.rows );
		unsigned char* expanded_data = new unsigned char[2 * width * height];
		for(int j = 0; j < height; j++) 
		{
			for(int i = 0; i < width; i++)
			{
				expanded_data[2 * (i + j * width)] = expanded_data[2 * (i + j * width) + 1] =
					(i >= ft_bitmap_glyph->bitmap.width || j >= ft_bitmap_glyph->bitmap.rows) ?
					0 : ft_bitmap_glyph->bitmap.buffer[i + ft_bitmap_glyph->bitmap.width * j];
			}
		}

		CFreeTypeFont::copyToTexture(width,height,expanded_data,&charDscr);

		m_charInfo[_char] = charDscr;

		delete[] expanded_data;
		FT_Done_Glyph( glyph );

		return true;
	}


	void CFreeTypeFont::copyToTexture( uint _width, uint _height, uchar* _data, SCharDesc* _charDesc )
	{
		m_iTexWidth = 1024;
		m_iTexHight = 1024;

		static int lineHeight;
		if (lineHeight < _height) lineHeight = _height;

		if (m_xOffTextures + _width >= m_iTexWidth)
		{
			m_xOffTextures = 0;
			m_yOffTextures += lineHeight + 1;
		}

		if (m_yOffTextures + lineHeight >= m_iTexHight)
		{
			m_yOffTextures = 0;
			m_currentTextureIndx++;
		}

		if (m_currentTextureIndx >= m_charMaterial.size())
		{	// Create big texture
			//char textureId[64];
			//sprintf(textureId, "textureFont%s%d", m_FontFileName.c_str(), m_currentTextureIndx);

			unsigned char* textureData = new GLubyte[2 * m_iTexWidth * m_iTexHight];
			memset(textureData, 0, 2 * m_iTexWidth * m_iTexHight);

			CTexture* texture = TEXTURE_MGR->createTexture2DFromData(m_iTexWidth,m_iTexHight,IF_DEPTH_COMPONENT,IT_UNSIGNED_BYTE,textureData);
			texture->getSampler()->setFilterType(FT_LINEAR, FT_LINEAR);
			texture->getSampler()->setWrapType(WT_CLAMP_TO_EDGE);

			m_charMaterial.push_back(texture);

			delete[] textureData;
		}

		RENDERER->copyToTexture2D(m_charMaterial[m_currentTextureIndx]->getTextureID(),m_xOffTextures, m_yOffTextures, _width, _height,_data);

		// Apply texture coord
		_charDesc->_iBearingX = m_xOffTextures;
		_charDesc->_iBearingY = m_yOffTextures;
		_charDesc->_iWidth = _width;
		_charDesc->_iHeight = _height;
		_charDesc->_page = m_currentTextureIndx;

		m_xOffTextures += _width + 1;
	}


	void CFreeTypeFont::createChar( const FT_Face& _ftFace1, FT_UInt _glyphIndex )
	{
		FT_Load_Glyph(m_Face, FT_Get_Char_Index(m_Face, _glyphIndex), FT_LOAD_DEFAULT);
		FT_Render_Glyph(m_Face->glyph, FT_RENDER_MODE_NORMAL);

		FT_Stroker stroker;
		FT_Stroker_New( m_Library, &stroker );

		FT_Glyph glyph;
		FT_Get_Glyph( m_Face->glyph, &glyph);
		FT_Glyph_StrokeBorder( &glyph, stroker, 0, 5 );

		FT_Bitmap* pBitmap = &m_Face->glyph->bitmap;

		uint width = pBitmap->width;
		uint hight = pBitmap->rows;
		
		//uint iTW = next_p2(width);
		//uint iTH = next_p2(hight);

		//GLubyte* bData = new GLubyte[iTW*iTH];
		// Copy glyph data and add dark pixels elsewhere
		/*for ( uint ch = 0; ch < iTH; ++ ch)
		{
			for ( uint cw = 0; cw < iTW; ++cw )
			{
				bData[ch*iTW+cw] = (ch >= hight || cw >= width) ? 0 : pBitmap->buffer[(hight-ch-1)*width+cw];
			}
		}*/

		unsigned int * bData = new unsigned int[width*hight];
		memset(bData, NULL, width * hight * sizeof(unsigned char));
		memcpy(bData, pBitmap->buffer, sizeof(unsigned char) * width * hight);

		//texture
		if (m_pCharTextures[_glyphIndex])
		{
			delete m_pCharTextures[_glyphIndex];
			m_pCharTextures[_glyphIndex] = nullptr;
		}
		m_pCharTextures[_glyphIndex] = TEXTURE_MGR->createTexture2DFromData(width,hight,IF_DEPTH_COMPONENT,IT_UNSIGNED_BYTE,bData);
		m_pCharTextures[_glyphIndex]->getSampler()->setFilterType(FT_LINEAR, FT_LINEAR);
		m_pCharTextures[_glyphIndex]->getSampler()->setWrapType(WT_CLAMP_TO_EDGE);

		// Calculate glyph data
		m_iAdvX[_glyphIndex] = m_Face->glyph->advance.x>>6;
		m_iBearingX[_glyphIndex] = m_Face->glyph->metrics.horiBearingX>>6;
		m_iCharWidth[_glyphIndex] = m_Face->glyph->metrics.width>>6;

		m_iAdvY[_glyphIndex] = (m_Face->glyph->metrics.height - m_Face->glyph->metrics.horiBearingY)>>6;
		m_iBearingY[_glyphIndex] = m_Face->glyph->metrics.horiBearingY>>6;
		m_iCharHeight[_glyphIndex] = m_Face->glyph->metrics.height>>6;

		m_iNewLine = max(m_iNewLine, int(m_Face->glyph->metrics.height>>6));
		
		delete[] bData;
		bData = nullptr;
		

		m_vertices.Vertex.vertices[_glyphIndex*4].setX(0.0f);
		m_vertices.Vertex.vertices[_glyphIndex*4].setY(float(-m_iAdvY[_glyphIndex]+hight));
		m_vertices.Vertex.vertices[_glyphIndex*4].setZ(0.0f);

		m_vertices.Vertex.vertices[_glyphIndex*4+1].setX(0.0f);
		m_vertices.Vertex.vertices[_glyphIndex*4+1].setY(float(-m_iAdvY[_glyphIndex]));
		m_vertices.Vertex.vertices[_glyphIndex*4+1].setZ(0.0f);

		m_vertices.Vertex.vertices[_glyphIndex*4+2].setX(float(width));
		m_vertices.Vertex.vertices[_glyphIndex*4+2].setY(float(-m_iAdvY[_glyphIndex]+hight));
		m_vertices.Vertex.vertices[_glyphIndex*4+2].setZ(0.0f);

		m_vertices.Vertex.vertices[_glyphIndex*4+3].setX(float(width));
		m_vertices.Vertex.vertices[_glyphIndex*4+3].setY(float(-m_iAdvY[_glyphIndex]));
		m_vertices.Vertex.vertices[_glyphIndex*4+3].setZ(0.0f);


		/*m_vertices.TexCoord.at(0).vertices[_glyphIndex*4].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4].setY(1.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+1].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+1].setY(0.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+2].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+2].setY(1.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+3].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+3].setY(0.0f);*/

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4].setY(0.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+1].setX(0.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+1].setY(1.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+2].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+2].setY(0.0f);

		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+3].setX(1.0f);
		m_vertices.TexCoord.at(0).vertices[_glyphIndex*4+3].setY(1.0f);
	}

	void CFreeTypeFont::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		RENDERER->bindShader( m_pShader->getShaderID() );

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		////m_pMaterial->bind();
		
		//RENDERER->updateTransform(m_worldMatrix, m_offset);
		//RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices);
		///*for (int i = 0; i < 128; ++i)
		//{
		//	RENDERER->bindTexture(m_pCharTextures[i]->getTextureID(),m_pCharTextures[i]->getSamplerID(),
		//		0,"texture0",m_pCharTextures[i]->getTarget(),m_pCharTextures[i]->getScale());
		//}*/
		////RENDERER->updateTransform(m_worldMatrix, m_offset);

		int iFontSize = 32;
		int y = RENDERER->getHeight() -10-iFontSize;;
		int x = 20;
		int iPXSize = iFontSize;
		int iCurX = x, iCurY = y;
		if(iPXSize == -1)iPXSize = m_iLoadedPixelSize;
		float fScale = float(iPXSize)/float(m_iLoadedPixelSize);

		for ( int chunk = 0; chunk < m_string.size(); ++chunk)
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
				RENDERER->bindTexture(m_pCharTextures[iIndex]->getTextureID(),m_pCharTextures[iIndex]->getSamplerID(),
				0,"texture0",m_pCharTextures[iIndex]->getTarget(),m_pCharTextures[iIndex]->getScale());

				Matrix4 mModelView = Matrix4::identity();
				m_position = Vector3(float(iCurX), float(iCurY), 0.0f);
				m_scale = Vector3(fScale,fScale,1.0f);
				CNode::updateTransform( 0 );
				//mModelView = Vectormath::transpose(Matrix4::translation(pos));

				RENDERER->updateTransform(m_worldMatrix, m_offset);

				RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices, iIndex*4,4);
								
				/*glm::mat4 mModelView = glm::translate(glm::mat4(1.0f), glm::vec3(float(iCurX), float(iCurY), 0.0f));
				mModelView = glm::scale(mModelView, glm::vec3(fScale));
				shShaderProgram->setUniform("modelViewMatrix", mModelView);*/
				// Draw character
				//glDrawArrays(GL_TRIANGLE_STRIP, iIndex*4, 4);
			}

			iCurX += (m_iAdvX[iIndex]-m_iBearingX[iIndex])*iPXSize/m_iLoadedPixelSize;
		}

		glDisable(GL_BLEND);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	void CFreeTypeFont::update( double _deltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform( _deltaTime );
			m_bNeedUpdate = false;
		}
	}

	void CFreeTypeFont::init()
	{
		m_pShader = m_pShader = SHADER_MGR->createShader(vertShaderFont2D,fragShaderFont2D);
	}

	///////////////////////////////////////////////////////////////////////////////////////////
}