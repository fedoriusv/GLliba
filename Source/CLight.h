#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#define	_MAX_LIGHTS_ 8

#include "CNode.h"

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SLightData
	{
		Vector4			_ambient;
		Vector4			_diffuse;
		Vector4			_specular;
		Vector3			_direction;
		Vector3			_attenuation;
		float			_fRadius;
		
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CLight : public CNode
	{
	protected:

		static uint			s_iLightCount;

		uint				m_iLightIndex;
		SLightData			m_sLightData;

		std::string			m_attribute;

	public:

		CLight( CNode* _pParent = nullptr );
		virtual				~CLight();

		void				init();

		void				render();
		void				update( double _dDeltaTime );

		void				setAmbientLight ( const Vector4& _color );
		void				setDiffuseLight ( const Vector4& _color );
		void				setSpecularLight( const Vector4& _color );

		Vector4				getAmbientLight() const;
		Vector4				getDiffuseLight() const;
		Vector4				getSpecularLight() const;

		void				setRadiusLight	 ( const float		 _fRadius	);
		void				setAttenuation	 ( const Vector3&	 _attenuation);
		void				setDirectionLight( const Vector3&	 _direction );
		void				setAttributeLight( const std::string _attribute );

		float				getRadiusLight() const;
		Vector3				getAttenuation() const;
		Vector3				getDirectionLight() const;
		std::string			getAttributeLight() const;
		
		uint				getLightIndex() const;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif