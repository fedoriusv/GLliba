#include "CMaterial.h"

#include "CRender.h"
#include "CShaderManager.h"
#include "CTextureManager.h"
#include "CShaderUniform.h"
#include "CShader.h"


namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	CMaterial::CMaterial()
		: CObject()
		, m_pShader(nullptr)
		, m_iTextureCount(0)
	{
		m_sMaterialData._ambient		= Vector4(0.2f, 0.2f, 0.2f, 1.0f);
		m_sMaterialData._diffuse		= Vector4(0.2f, 0.2f, 0.2f, 1.0f);
		m_sMaterialData._specular		= Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		m_sMaterialData._emission		= Vector4(0.0f);
		m_sMaterialData._iShininess		= 128U;
		m_sMaterialData._fTransparency	= 1.0f;
		
		m_eTypeObject = OT_MATERIAL;

		for ( uint layer = 0; layer < TL_TEXTURE_MAX; ++layer )
		{
			m_pTexture[layer] = nullptr;
		}

		CMaterial::init();
	}

	
	CMaterial::~CMaterial()
	{
		for ( uint layer = 0; layer < TL_TEXTURE_MAX; ++layer )
		{
			destroyTexture(layer);
		}

		destroyShader();
	}

	
	void CMaterial::init()
	{
		CMaterial::setShader(
			STR_SIMPLE_VERTEX_SHADER,
			STR_SIMPLE_FRAGMENT_SHADER);
	}

	
	void CMaterial::setAmbientColor( const Vector4& _color )
	{
		m_sMaterialData._ambient = _color;
	}

	
	void CMaterial::setDiffuseColor( const Vector4& _color )
	{
		m_sMaterialData._diffuse = _color;
		m_sMaterialData._fTransparency = m_sMaterialData._diffuse.getW();
	}

	
	void CMaterial::setSpecularColor( const Vector4& _color )
	{
		m_sMaterialData._specular = _color;
	}

	
	void CMaterial::setEmissionColor( const Vector4& _color )
	{
		m_sMaterialData._emission = _color;
	}

	
	void CMaterial::setShininess( const float  _value )
	{
		m_sMaterialData._iShininess = _value;
	}

	
	Vector4 CMaterial::getAmbientColor() const
	{
		return m_sMaterialData._ambient;
	}

	
	Vector4 CMaterial::getDiffuseColor() const
	{
		return m_sMaterialData._diffuse;
	}

	
	Vector4 CMaterial::getSpecularColor() const
	{
		return m_sMaterialData._specular;
	}

	
	Vector4	CMaterial::getEmissionColor() const
	{
		return m_sMaterialData._emission;
	}

	
	float CMaterial::getShininess() const
	{
		return m_sMaterialData._iShininess;
	}

	
	void CMaterial::bind()
	{
		if ( m_pShader != nullptr && m_pShader->isEnable() )
		{
			RENDERER->bindShader( m_pShader->getShaderID() );
			
			if (m_pShader->m_uniformList.size() > 0)
			{
				UniformList::iterator iter = m_pShader->m_uniformList.begin();
				CShaderUniform* uniform = iter->second;
				while (iter!= m_pShader->m_uniformList.end())
				{
					RENDERER->setShaderUniform( uniform->m_eShaderType, m_pShader->getShaderID(),
						uniform->m_attribute, uniform->m_uniformValue );
					++iter;
				}
			}

			RENDERER->renderMaterial( m_sMaterialData );
		
			for ( uint i = 0; i < TL_TEXTURE_MAX; ++i )
			{
				if ( m_pTexture[i] != nullptr )
				{
					m_pTexture[i]->bind(i);
				}
			}
		}
	}

		
	CTexture* CMaterial::getTexture( const uint _layer ) const
	{
		if (_layer >= TL_TEXTURE_MAX)
		{
			ASSERT( false && "invalid texture layer" );
			return NULL;
		}

		return m_pTexture[_layer];
	}

	
	uint CMaterial::getTextureCount() const
	{
		return m_iTextureCount;
	}

	
	void CMaterial::setTexture( const uint _textureLayer, const std::string& _attribute, const std::string& _nameFile )
	{
		if (_textureLayer >= TL_TEXTURE_MAX )
		{
			ASSERT( false && "Texture Layer range out" );
			return;
		}

		CTexture* oldTexture = m_pTexture[_textureLayer];
		if ( oldTexture != NULL )
		{
			TEXTURE_MGR->destroyTexture(oldTexture);
			--m_iTextureCount;
		}

		std::string name = _nameFile;
		TEXTURE_MGR->transformString( name, true );

		CTexture* texture = TEXTURE_MGR->createTexture(name);
		m_pTexture[_textureLayer] = texture;
		++m_iTextureCount;

		m_pTexture[_textureLayer]->setAttributeTexture(_attribute);
	}

	
	void CMaterial::setTexture( const uint _textureLayer, const std::string& _attribute, const std::string _nameFiles[6] )
	{
		if (_textureLayer >= TL_TEXTURE_MAX )
		{
			ASSERT( false && "Texture Layer range out" );
			return;
		}

		CTexture* oldTexture = m_pTexture[_textureLayer];
		if ( oldTexture != NULL )
		{
			TEXTURE_MGR->destroyTexture(oldTexture);
			--m_iTextureCount;
		}

		std::string names[6];
		for ( int iStr = 0; iStr < 6; ++iStr )
		{
			names[iStr] = _nameFiles[iStr];
			TEXTURE_MGR->transformString( names[iStr], true );
		}

		CTexture* texture = TEXTURE_MGR->createCubeMap(names);
		m_pTexture[_textureLayer] = texture;
		++m_iTextureCount;

		m_pTexture[_textureLayer]->setAttributeTexture(_attribute);
	}

	
	void CMaterial::destroyTexture( uint _textureLayer )
	{
		if (_textureLayer >= TL_TEXTURE_MAX )
		{
			ASSERT( false && "Texture Layer range out" );
			return;
		}

		CTexture* oldTexture = m_pTexture[_textureLayer];
		if ( oldTexture != NULL )
		{
			TEXTURE_MGR->destroyTexture(oldTexture);
		}

		m_pTexture[_textureLayer] = NULL;
		--m_iTextureCount;
	}

	
	void CMaterial::setTexture( const uint _textureLayer, const std::string& _attribute, CTexture* _texture )
	{
		if (_textureLayer >= TL_TEXTURE_MAX )
		{
			ASSERT( false && "Texture Layer range out" );
			return;
		}

		CTexture* oldTexture = m_pTexture[_textureLayer];
		if ( oldTexture != NULL )
		{
			TEXTURE_MGR->destroyTexture(oldTexture);
			--m_iTextureCount;
		}

		m_pTexture[_textureLayer] = (CTexture*)_texture->getRef();
		++m_iTextureCount;

		m_pTexture[_textureLayer]->setAttributeTexture(_attribute);
	}

	
	void CMaterial::setTransparency( const float _value )
	{

		m_sMaterialData._fTransparency = (_value > 1.0f) ? 1.0f : _value;
	}

	
	float CMaterial::getTransparency() const
	{
		return m_sMaterialData._fTransparency;
	}

	
	CShader* CMaterial::getShader() const
	{
		return m_pShader;
	}

	
	void CMaterial::setShader( CShader* _shader )
	{
		if (m_pShader)
		{
			destroyShader();
		}

		m_pShader = (CShader*)_shader->getRef();
	}

	
	void CMaterial::setShader(  const std::string& _vertexShader, const std::string& _fragmentShader )
	{
		if (m_pShader)
		{
			destroyShader();
		}

		m_pShader = SHADER_MGR->createShader(_vertexShader,_fragmentShader);
	}

	
	void CMaterial::destroyShader()
	{
		if (m_pShader)
		{
			SHADER_MGR->destroyShader(m_pShader);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
}