#ifndef _CMODEL3DS_H_
#define _CMODEL3DS_H_

#include "CModel.h"

//#include "lib3ds\lib3ds\src\lib3ds.h" v.2.0 RC1
#include "lib3ds\lib3ds-1.3.0\lib3ds\file.h"
#include "lib3ds\lib3ds-1.3.0\lib3ds\mesh.h"
#ifdef _DEBUG
#	include <time.h>
#	pragma comment(lib, "lib3ds\\lib3ds-1.3.0\\msvc8\\debug\\lib3ds.lib")
#else
#	pragma comment(lib, "..\\Libs\\lib3ds\\lib3ds-1.3.0\\msvc8\\release\\lib3ds.lib")
#endif

namespace glliba
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CModel3DS : public CModel
	{
	private:

		void		loadMateral( CMesh* _mesh, Lib3dsFile* _model3ds );

	public:

		CModel3DS( CNode* _parent );
		virtual		~CModel3DS();

		void		loadFromFile( const std::string& _nameFile );

		void		init();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
};

#endif