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
		void				setShininess	( const float   _iValue );
		void				setTransparency ( const float   _fValue );

		Vector4				getAmbientColor() const;
		Vector4				getDiffuseColor() const;
		Vector4				getSpecularColor() const;
		Vector4				getEmissionColor() const;
		float				getShininess() const;
		float				getTransparency() const;

		void				bind();

		void				setTexture( const uint _iTextureLayer, const std::string& _attribute, const std::string& _nameFile	 );
		void				setTexture( const uint _iTextureLayer, const std::string& _attribute, const std::string _nameFiles[6]);
		void				setTexture( const uint _iTextureLayer, const std::string& _attribute, CTexture* _pTexture			 );
		CTexture*			getTexture( const uint _iTextureLayer ) const;
		void				destroyTexture( uint _iTextureLayer );
		uint				getTextureCount() const;

		
		CShader*			getShader() const;
		void				setShader( CShader* _pShader  );
		void				setShader( const std::string& _vertexShader, const std::string& _fragmentShader );
		void				destroyShader();

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif