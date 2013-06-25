#include "Vertex.h"

namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	SVertexData::SVertexData()
		: nVertices(0)
		, nIndices(0)
		, iVertexArrayID(0)
	{
	}


	SVertexData::~SVertexData()
	{
		clear();
	}


	void SVertexData::clear()
	{
		if (Vertex.vertices != NULL )
		{
			delete[] Vertex.vertices;
			Vertex.vertices = NULL;
		}

		if (Normal.vertices != NULL )
		{
			delete[] Normal.vertices;
			Normal.vertices = NULL;
		}

		for ( uint i = 0; i < TexCoord.size(); ++i )
		{
			if (TexCoord.at(i).vertices != NULL )
			{
				delete[] TexCoord.at(i).vertices;
				TexCoord.at(i).vertices = NULL;
				TexCoord.pop_back();
			}
		}
		TexCoord.clear();

		if (Indices.vertices != NULL )
		{
			delete[] Indices.vertices;
			Indices.vertices = NULL;
		}

	};


	void SVertexData::malloc( uint _count, uint _countIndex, uint _countTexLayer )
	{
		clear();

		nVertices = _count;
		Vertex.vertices = new Vector3[nVertices];
		Normal.vertices = new Vector3[nVertices];
		TexCoord.reserve(_countTexLayer);
		for ( uint i = 0; i < _countTexLayer; ++i )
		{
			SVertices<Vector2> texCoord;
			texCoord.vertices = new Vector2[nVertices];
			TexCoord.push_back(texCoord);
		}

		if ( _countIndex > 0 )
		{
			nIndices = _countIndex;
			Indices.vertices = new uint[nIndices];
		}
	}


	void SVertexData::copyVertexData( const std::vector<SVertex>& _vertices,
		const std::vector<uint>& _indices )
	{
		malloc( _vertices.size(), _indices.size() );

		int index  = -1;

		for ( std::vector<SVertex>::const_iterator iter = _vertices.begin(); iter < _vertices.end(); ++iter )
		{
			const SVertex& vertex = (*iter);

			++index;
			Vertex.vertices[index] = vertex.position;
			Normal.vertices[index] = vertex.normal;
			TexCoord.at(0).vertices[index] = vertex.texCoords;
		}

		if ( _indices.size() > 0 )
		{
			nIndices = _indices.size();
			memcpy(Indices.vertices,_indices.data(), nIndices*sizeof(uint));
		}
	}

	void SVertexData::copyVertexData( const std::map<size_t,SVertex>& _vertices,
			const std::vector<uint>& _indices )
	{
		malloc( _vertices.size(), _indices.size() );

		int index  = -1;

		for ( std::map<size_t,SVertex>::const_iterator iter = _vertices.begin(); iter != _vertices.end(); ++iter )
		{
			++index;
			Vertex.vertices[index] = (*iter).second.position;
			Normal.vertices[index] = (*iter).second.normal;
			TexCoord.at(0).vertices[index] = (*iter).second.texCoords;
		}

		if ( _indices.size() > 0 )
		{
			nIndices = _indices.size();
			memcpy(Indices.vertices,_indices.data(), nIndices*sizeof(uint));
		}
	}

	void SVertexData::copyVertexData( const HashMap& _vertices,
			const std::vector<uint>& _indices )
	{
		malloc( _vertices.size(), _indices.size() );

		int index  = -1;

		for ( HashMap::const_iterator iter = _vertices.begin(); iter != _vertices.end(); ++iter )
		{
			++index;
			Vertex.vertices[index] = (*iter).first.position;
			Normal.vertices[index] = (*iter).first.normal;
			TexCoord.at(0).vertices[index] = (*iter).first.texCoords;
		}

		if ( _indices.size() > 0 )
		{
			nIndices = _indices.size();
			memcpy(Indices.vertices,_indices.data(), nIndices*sizeof(uint));
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
}