#include "CModelF3D.h"
#include "CResourceManager.h"

#include <fstream>

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModelF3D::CModelF3D( CNode* _pParent )
		: CModel(_pParent)
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModelF3D::~CModelF3D()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModelF3D::init()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModelF3D::loadFromFile( const std::string _nameFile )
	{
		m_modelNameFile = _nameFile;

		std::ifstream inFile(_nameFile, std::ios::in | std::ios::binary | std::ios::_Nocreate);
		if(!inFile) 
		{
			ASSERT(true && "Cant load f3d file");
			return;
		}

		uint numMeshes = 0;
		inFile.read((char *)&numMeshes, sizeof(int));
		
		for ( uint iMesh = 0; iMesh < numMeshes; ++iMesh )
		{
			CMesh* mesh = new CMesh();
			
			std::string modelName("");
			loadString	( inFile, modelName );
			mesh->setName(modelName);

			loadVertices( inFile, mesh );
			loadMaterial( inFile, mesh );
			
			m_pMesh.push_back(mesh);
		}

		for ( std::vector<CMesh*>::iterator iter = m_pMesh.begin(); iter < m_pMesh.end(); ++iter )
		{
			(*iter)->init();
		}
		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModelF3D::loadVertices( std::ifstream& _file, CMesh* _pMesh )
	{
		std::streampos Tmp;

		_file.read((char *)&Tmp, sizeof(int));
		int countVert = (int)Tmp;
		_file.read((char *)&Tmp, sizeof(int));
		int countInd = (int)Tmp;
		_file.read((char *)&Tmp, sizeof(int));
		int countFaces = (int)Tmp;

		std::vector<SVertex>	vertices;
		std::vector<uint>		indices;

		for (int i = 0; i < countVert; ++i )
		{
			Vector3 pos;
			_file.read((char*)&pos[0],sizeof(float)*3);
	
			Vector3 normal;
			_file.read((char*)&normal[0],sizeof(float)*3);
			
			Vector2 textCoord;
			_file.read((char*)&textCoord[0],sizeof(float)*2);
			

			SVertex vertex(pos,normal,textCoord);
			vertices.push_back(vertex);
		}

		for (int i = 0; i < countInd; ++i )
		{
			uint id = 0;
			_file.read((char*)&id,sizeof(int));
			indices.push_back(id);
		}


		_pMesh->m_vertices.copyVertexData( vertices, indices );

		vertices.clear();
		indices.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModelF3D::loadMaterial( std::ifstream& _file, CMesh* _pMesh )
	{
		int material;
		_file.read((char*)&material,sizeof(int));
		if (material == 0)
		{
			LOG_CONSOLE("Material not found\n");
			return;
		}

		std::streampos Tmp;

		std::string materialName("");
		loadString	( _file, materialName );
		_pMesh->getMaterial()->setName(materialName);

		Vector3 ambient;
		_file.read((char*)&ambient[0],sizeof(float)*3);
		
		Vector3 diffuse;
		_file.read((char*)&diffuse[0],sizeof(float)*3);
		
		Vector3 specular;
		_file.read((char*)&specular[0],sizeof(float)*3);
		
		Vector3 emission;
		_file.read((char*)&emission[0],sizeof(float)*3);
		
		float opacity;
		_file.read((char*)&opacity,sizeof(float));

		float shininess;
		_file.read((char*)&shininess,sizeof(float));

		_pMesh->getMaterial()->setTransparency(opacity);
		_pMesh->getMaterial()->setAmbientColor(Vector4(ambient[0],ambient[1],ambient[2],1.0f));
		_pMesh->getMaterial()->setDiffuseColor(Vector4(diffuse[0],diffuse[1],diffuse[2],opacity));
		_pMesh->getMaterial()->setSpecularColor(Vector4(specular[0],specular[1],specular[2],1.0f));
		_pMesh->getMaterial()->setEmissionColor(Vector4(emission[0],emission[1],emission[2],1.0f));
		_pMesh->getMaterial()->setShininess(shininess);

		_file.read((char *)&Tmp, sizeof(int));
		int numTextures = (int)Tmp;

		for ( int i = 0; i < numTextures; ++i )
		{
			std::string textureFile("");
			loadString	( _file, textureFile );

			_pMesh->getMaterial()->setTexture(i, "texture0", "data/" + textureFile);
			
			std::string textureName("");
			loadString	( _file, textureName );
			_pMesh->getMaterial()->getTexture(i)->setName(textureName);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModelF3D::loadString( std::ifstream& _file, std::string& _stringOut )
	{
		char Ch;

		do
		{
			_file >> Ch;
			_stringOut += Ch;
		} 
		while(Ch != 0);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
