#include "CModel3DS.h"

#include "CLogger.h"

#include <boost/functional/hash.hpp>
#include <hash_map>
#include <time.h>

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline float round( const float& _point )
	{
		return (float)((int)(_point*1000.0f))/1000.0f;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModel3DS::CModel3DS( CNode* _parent )
		: CModel(_parent)
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	CModel3DS::~CModel3DS()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel3DS::init()
	{
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel3DS::loadFromFile( const std::string& _nameFile )
	{
		Lib3dsFile * model;
		model = lib3ds_file_load( _nameFile.c_str() );
		
		if (!model)
		{
			ASSERT( false && "Cant load 3ds file" );
			return;
		}
		
		Lib3dsMesh * mesh3ds;

		uint totalFaces  = 0;
		for( mesh3ds = model->meshes; mesh3ds != NULL; mesh3ds = mesh3ds->next )
		{
			totalFaces += mesh3ds->faces;
		}

		for( mesh3ds = model->meshes; mesh3ds != NULL; mesh3ds = mesh3ds->next )
		{
			int index  = -1;
			
			uint finishedFaces = 0;

			CMesh* mesh = new CMesh();

			std::vector<uint>		indices;
			//std::vector<size_t>		hashes;
			std::vector<SVertexHash> hashes;
			std::vector<SVertex>   vertices;
			//std::hash_map<SVertex,size_t,hash_compare<SVertex>> vertices;
			//std::hash_map<SVertex,size_t,hash_compare<SVertex>>::iterator iterVertices;

			SVertex vertex;
//#ifdef _DEBUG
			clock_t startTime = clock();
//#endif
			for( uint currentFace = 0; currentFace < mesh3ds->faces; ++currentFace )
			{
				const Lib3dsFace * face = &mesh3ds->faceL[currentFace];
				for ( uint i = 0; i < 3; ++i )
				{
					const int pointIndex = face->points[i];
				
					vertex.position = Vector3( round(mesh3ds->pointL[pointIndex].pos[0]), round(mesh3ds->pointL[pointIndex].pos[2]), round(mesh3ds->pointL[pointIndex].pos[1]) );
					vertex.normal = Vector3( round(face->normal[0]), round(face->normal[2]), round(face->normal[1]) );
					vertex.texCoords = Vector2( round(mesh3ds->texelL[pointIndex][0]), round(mesh3ds->texelL[pointIndex][1]) );
					vertex.calcHash();
					
					//LOG_CONSOLE("completed:" << (float)finishedFaces/(float)mesh3ds->faces * 100 << "%");
					//LOG( "normal:  nx = " << face->normal[0] << " ny = " << face->normal[1] << " nz = " << face->normal[2] );
					int indexID = -1;
					
					std::vector<SVertex>::iterator iter = std::find(vertices.begin(),vertices.end(),vertex);
					if ( iter != vertices.end() )
					{
						indexID = std::distance( vertices.begin(), iter );
						indices.push_back(indexID);
						LOG_DEBUG("	Index: %i\n", indexID);
					}
					else
					{
						vertices.push_back( vertex );
						indexID = vertices.size() - 1;
						indices.push_back( indexID );

						LOG_DEBUG("Vertex # %i\n", indexID);
						LOG_DEBUG("	Posinion x:%f; y:%f; z:%f;\n", vertex.position[0], vertex.position[1], vertex.position[2] );
						LOG_DEBUG("	Normal x:%f; y:%f; z:%f;\n", vertex.normal[0], vertex.normal[1], vertex.normal[2] );
						LOG_DEBUG("	TexCoords x:%f; y:%f;\n", vertex.texCoords[0], vertex.texCoords[1] );
						LOG_DEBUG("	Index: %i\n", indexID);
					}
				}

				finishedFaces++;
			}

			LOG_CONSOLE( "faces:" << totalFaces << "; vertices:" << vertices.size() << "; indices:" << indices.size() );
//#ifdef _DEBUG
			clock_t endTime = clock();
			LOG_CONSOLE( "time to load: " << (endTime - startTime)/1000.0f << " sec" );
//#endif
			LOG_DEBUG( "faces: %i, vertices: %i, indices: %i\n", totalFaces, vertices.size(), indices.size() );
			LOG_DEBUG( "time to load: %f sec\n", (endTime - startTime)/1000.0f );
			
			mesh->m_vertices.copyVertexData( vertices, indices );

			vertices.clear();
			indices.clear();
			hashes.clear();
			
			mesh->setName(mesh3ds->name);
			m_pMesh.push_back(mesh);
		}

		for ( std::vector<CMesh*>::iterator iter = m_pMesh.begin(); iter < m_pMesh.end(); ++iter )
		{
			(*iter)->init();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CModel3DS::loadMateral( CMesh* _mesh, Lib3dsFile* _model3ds )
	{
		CMaterial* material = _mesh->getMaterial();

		ASSERT( material!= NULL || "Material not alloc" );
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
}