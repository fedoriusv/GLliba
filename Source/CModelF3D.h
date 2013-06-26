#ifndef _CMODELF3D_H_
#define _CMODELF3D_H_

#include "CModel.h"

#define ID_NODE_HEADER          0xABCD
#define ID_MTL_HEADER           0x1FF1
#define ID_VERTEX_HEADER        0x2FF2
#define ID_TVERTEX_HEADER       0x2EE2
#define ID_FACE_HEADER          0x3FF3

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CModelF3D : public CModel
	{
	private:
		
		void		loadVertices( std::ifstream& _file, CMesh* _pMesh );
		void		loadMaterial( std::ifstream& _file, CMesh* _pMesh );

		void		loadString( std::ifstream& _file, std::string& _stringOut );

	public:

		CModelF3D( CNode* _parent );
		virtual		~CModelF3D();

		void		loadFromFile( const std::string& _nameFile );

		void		init();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif