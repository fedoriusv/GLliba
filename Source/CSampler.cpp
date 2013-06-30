#include "CSampler.h"
#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CSampler::CSampler()
		: m_iSamplerID(0)
		, m_eWrapType(WT_CLAMP_TO_EDGE)
		, m_eMinFilerType(FT_LINEAR_MIPMAP_LINEAR)
		, m_eMagFilerType(FT_LINEAR)

		, m_bNeedUpdate(false)
	{
		CSampler::init();
	}

		
	CSampler::~CSampler()
	{
		RENDERER->deleteSampler(m_iSamplerID);
		m_iSamplerID = 0;
	}

	
	uint CSampler::getSamplerID() const
	{
		return m_iSamplerID;
	}

		
	WRAP_TYPE CSampler::getWrapType() const
	{
		return m_eWrapType;
	}

	
	FILTER_TYPE	CSampler::getMinFilerType() const
	{
		return m_eMinFilerType;
	}

	
	FILTER_TYPE	CSampler::getMagFilerType() const
	{
		return m_eMagFilerType;
	}

	
	void CSampler::setWrapType( WRAP_TYPE _type )
	{
		m_eWrapType = _type;
		m_bNeedUpdate = true;
	}

		
	void CSampler::setFilterType( FILTER_TYPE _minType, FILTER_TYPE _magType )
	{
		m_eMinFilerType = _minType;
		m_eMagFilerType = _magType;
		m_bNeedUpdate = true;
	}

	
	void CSampler::init()
	{
		RENDERER->initSampler( m_iSamplerID, m_eWrapType, m_eMinFilerType, m_eMagFilerType );
	}

	
	void CSampler::update()
	{
		if (!m_bNeedUpdate)
		{
			return;
		}

		RENDERER->updateSampler( m_iSamplerID, m_eWrapType, m_eMinFilerType, m_eMagFilerType );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
}