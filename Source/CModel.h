#ifndef _CMODEL_H_
#define _CMODEL_H_

#include "CNode.h"
#include "CMesh.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CModel : public CNode
	{
	protected:

		friend CResourceManager;

		std::vector<CMesh*>		m_pMesh;
		std::string				m_modelNameFile;

		bool					compareByName( const std::string& _name );

	public:

		CModel( CNode* _parent = nullptr );
		virtual					~CModel();

		void					addMesh( CMesh* _mesh );
		CMesh*					getMesh( const uint _id ) const;
		int						getMeshCount() const;

		virtual void			loadFromFile( const std::string& _nameFile ) = 0;

		void					update( double _deltaTime ) final;
		void					render() final;

		void					setShaderForAllMesh( CShader* _shader );
		void					setShaderForAllMesh( const std::string& _vertShader, const std::string& _fragShader );
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif