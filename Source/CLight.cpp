#include "CLight.h"

#include "CRender.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	uint CLight::s_iLightCount = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CLight::CLight( CNode* _pParent )
		: CNode( _pParent )
		, m_attribute("light")
	{
		m_eTypeNode = TN_LIGHT;

		++s_iLightCount;
		m_iLightIndex = s_iLightCount - 1;

		m_sLightData._ambient		= Vector4(1.0f);
		m_sLightData._diffuse		= Vector4(1.0f);
		m_sLightData._specular		= Vector4(1.0f);
		m_sLightData._fRadius		= 100.0f;
		m_sLightData._direction		= Vector3(0.0f,0.0f,-1.0f);
		m_sLightData._attenuation	= Vector3(0.5f,0.0f,0.02f);

		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str() << " Id: " << m_iLightIndex );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CLight::~CLight()
	{
		--s_iLightCount;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::init()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::render()
	{
		RENDER->renderLight( m_attribute, Vector4(m_position,1.0f), m_sLightData );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::update( double _dDeltaTime )
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	uint CLight::getLightIndex() const
	{
		return m_iLightIndex;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setAmbientLight( const Vector4& _color )
	{
		m_sLightData._ambient = _color;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setDiffuseLight( const Vector4& _color )
	{
		m_sLightData._diffuse = _color;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setSpecularLight( const Vector4& _color )
	{
		m_sLightData._specular = _color;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector4 CLight::getAmbientLight() const
	{
		return m_sLightData._ambient;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector4 CLight::getDiffuseLight() const
	{
		return m_sLightData._diffuse;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector4 CLight::getSpecularLight() const
	{
		return m_sLightData._specular;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setRadiusLight( const float _fRadius )
	{
		m_sLightData._fRadius = _fRadius;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	float CLight::getRadiusLight() const
	{
		return m_sLightData._fRadius;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setAttenuation( const Vector3& _attenuation )
	{
		m_sLightData._attenuation = _attenuation;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector3 CLight::getAttenuation() const
	{
		return m_sLightData._attenuation;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setDirectionLight( const Vector3& _direction )
	{
		m_sLightData._direction = _direction;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	Vector3 CLight::getDirectionLight() const
	{
		return m_sLightData._direction;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CLight::setAttributeLight( const std::string _attribute )
	{
		m_attribute = _attribute;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string CLight::getAttributeLight() const
	{
		return m_attribute;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

} 