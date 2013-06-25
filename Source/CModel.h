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

		bool					compareByName( std::string _name );
	public:

		CModel( CNode* _parent = NULL );
		virtual					~CModel();

		void					addMesh( CMesh* _pMesh );
		CMesh*					getMesh( const uint _iID ) const;
		int						getMeshCount() const;

		virtual void			loadFromFile( const std::string _nameFile ) = 0;

		void					update( double _deltaTime );
		void					render();

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif