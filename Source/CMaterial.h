#ifndef _CMATERIAL_H_
#define _CMATERIAL_H_

#include "CTexture.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SMaterialData
	{
		Vector4		_ambient;
		Vector4		_diffuse;
		Vector4		_specular;
		Vector4		_emission;
		float		_iShininess;
		float		_fTransparency;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CTexture;
	class CShader;


	class CMaterial : public CObject 
	{
	protected:

		SMaterialData		m_sMaterialData;

		uint				m_iTextureCount;
		CTexture*			m_pTexture[TL_TEXTURE_MAX];
		CShader*			m_pShader;

	public:

		CMaterial();
		virtual				~CMaterial();

		void				init();

		void				setAmbientColor ( const Vector4& _color );
		void				setDiffuseColor ( const Vector4& _color );
		void				setSpecularColor( const Vector4& _color );
		void				setEmissionColor( const Vector4& _color );
		void				setShininess	( const float&   _value );
		void				setTransparency ( const float&   _value );

		Vector4				getAmbientColor() const;
		Vector4				getDiffuseColor() const;
		Vector4				getSpecularColor() const;
		Vector4				getEmissionColor() const;
		float				getShininess() const;
		float				getTransparency() const;

		void				bind();

		void				setTexture( const uint _layer, const std::string& _attribute, const std::string& _nameFile );
		void				setTexture( const uint _layer, const std::string& _attribute, const std::string _nameFiles[6] );
		void				setTexture( const uint _layer, const std::string& _attribute, CTexture* _texture );
		CTexture*			getTexture( const uint _layer ) const;
		void				destroyTexture( uint _layer );
		uint				getTextureCount() const;

		
		CShader*			getShader() const;
		void				setShader( CShader* _shader );
		void				setShader( const std::string& _vertShader, const std::string& _fragShader );
		void				destroyShader();

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif