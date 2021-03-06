#include "CTexture.h"
#include "CSampler.h"
#include "CRender.h"


namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int CTexture::s_iTextureCount = -1;
	
	
	CTexture::CTexture()
		: CObject()
		, m_eTarget(TD_INVALID)
		, m_scale(1.0f,1.0f)
		, m_iTextureID(0)
		, m_attribute("texture0")
	{
		++s_iTextureCount;

		m_pSampler = new CSampler();
	}

	
	CTexture::~CTexture()
	{
		--s_iTextureCount;
		
		RENDERER->deleteTexture(m_iTextureID);
		m_iTextureID = 0;

		delete m_pSampler;
		m_pSampler = nullptr;
	}

	
	Vector2 CTexture::getScale() const
	{
		return m_scale;
	}

	
	void CTexture::setScale( const Vector2& _scale )
	{
		m_scale = _scale;
	}

	
	uint CTexture::getTextureID() const
	{
		return m_iTextureID;
	}

	
	uint CTexture::getSamplerID() const
	{
		return m_pSampler->getSamplerID();
	}

	
	CSampler* CTexture::getSampler() const
	{
		return m_pSampler;
	}

	
	void CTexture::bind( uint _textureLayer )
	{
		m_pSampler->update();

		RENDERER->bindTexture( m_iTextureID, CTexture::getSamplerID(), _textureLayer,
			m_attribute, m_eTarget,  m_scale );
	}

	
	TEXTURE_TYPE CTexture::getTarget() const
	{
		return m_eTarget;
	}

	
	void CTexture::setAttributeTexture( const std::string& _attribute )
	{
		m_attribute = _attribute;
	}

		
	std::string CTexture::getAttributeTexture() const
	{
		return m_attribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////

}