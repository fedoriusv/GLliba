#include "CVertexBufferGL.h"

#include "Param.h"
#include "Vertex.h"
#include "CLogger.h"

namespace glliba
{
	
	void CVertexBufferGL::initVertexAttribPointerGL( const uint _vertexAttrib, const uint _size )
	{
		glEnableVertexAttribArray( _vertexAttrib );
		glVertexAttribPointer( _vertexAttrib, _size, GL_FLOAT, GL_FALSE, NULL, NULL );
	}

	

	void CVertexBufferGL::initBufferObjectGL( const uint _target, uint& _bufferID, const uint _size, void* _data)
	{
		glGenBuffers( 1, &_bufferID );
		glBindBuffer( _target, _bufferID );
		ASSERT(glIsBuffer( _bufferID ) && "Invalid VBO index");
		glBufferData( _target, _size, _data, GL_STATIC_DRAW );
	}

	
	void CVertexBufferGL::initBufferObjectsGL( SVertexData& _vertexData )
	{
		glGenVertexArrays(1, &_vertexData.iVertexArrayID);
		glBindVertexArray(_vertexData.iVertexArrayID);
		ASSERT(glIsVertexArray( _vertexData.iVertexArrayID ) || "Invalid VAO index");

		//Vertex
		initBufferObjectGL( GL_ARRAY_BUFFER, _vertexData.Vertex.iVerticesID,
			sizeof(GLfloat)*_vertexData.nVertices*3, _vertexData.Vertex.vertices );
		initVertexAttribPointerGL( GL_ATTRIBUTE_VERTEX, 3 );
		
		//Normal
		initBufferObjectGL( GL_ARRAY_BUFFER, _vertexData.Normal.iVerticesID,
			sizeof(GLfloat)*_vertexData.nVertices*3, _vertexData.Normal.vertices );
		initVertexAttribPointerGL( GL_ATTRIBUTE_NORMAL, 3 );
		
		//TexCoords
		for (uint i = 0; i < _vertexData.TexCoord.size(); ++i )
		{
			initBufferObjectGL( GL_ARRAY_BUFFER, _vertexData.TexCoord.at(i).iVerticesID,
				sizeof(GLfloat)*_vertexData.nVertices*2, _vertexData.TexCoord.at(i).vertices );
			initVertexAttribPointerGL( GL_ATTRIBUTE_TEXTURE0 + i, 2 );
		}

		//Indices
		if ( _vertexData.nIndices > 0 )
		{
			initBufferObjectGL( GL_ELEMENT_ARRAY_BUFFER, _vertexData.Indices.iVerticesID,
				sizeof(GLint)*_vertexData.nIndices, _vertexData.Indices.vertices );
		}

		glBindVertexArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	}

	
	void CVertexBufferGL::deleteBufferObjectsGL( SVertexData& _vertexData )
	{
		if ( _vertexData.iVertexArrayID != 0 )
		{
			glDeleteVertexArrays( 1, &_vertexData.iVertexArrayID );
		}

		deleteBuffersGL( _vertexData.Vertex.iVerticesID	);
		deleteBuffersGL( _vertexData.Normal.iVerticesID  );
		deleteBuffersGL( _vertexData.Indices.iVerticesID );
		for (uint i = 0; i < _vertexData.TexCoord.size(); ++i )
		{
			deleteBuffersGL( _vertexData.TexCoord.at(i).iVerticesID );
		}
	}

	
	void  CVertexBufferGL::deleteBuffersGL( const uint _vertexID )
	{
		if ( _vertexID != 0 )
		{
			ASSERT(glIsShader( _vertexID ) || "Invalid Index Buffer");
			glDeleteBuffers( 1, &_vertexID );
		}
	}

	
	void CVertexBufferGL::updateBufferObjectGL( SVertexData& _vertexData )
	{
		updateBufferSubDataGL( GL_ARRAY_BUFFER, _vertexData.Vertex.iVerticesID,
			sizeof(GLfloat)*_vertexData.nVertices*3, _vertexData.Vertex.vertices );
		
		updateBufferSubDataGL( GL_ARRAY_BUFFER, _vertexData.Normal.iVerticesID,
			sizeof(GLfloat)*_vertexData.nVertices*3, _vertexData.Normal.vertices );
		
		for (uint i = 0; i < _vertexData.TexCoord.size(); ++i )
		{
			updateBufferSubDataGL( GL_ARRAY_BUFFER, _vertexData.TexCoord.at(i).iVerticesID,
				sizeof(GLfloat)*_vertexData.nVertices*2,  _vertexData.TexCoord.at(i).vertices );
		}

		if ( _vertexData.nIndices > 0 )
		{
			updateBufferSubDataGL( GL_ELEMENT_ARRAY_BUFFER, _vertexData.Indices.iVerticesID,
				sizeof(GLint)* _vertexData.nIndices, _vertexData.Indices.vertices );
		}

		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	
	void CVertexBufferGL::updateBufferSubDataGL( const uint _target, const uint _bufferID, const uint _size, void* _data )
	{
		ASSERT(glIsBuffer( _bufferID ) || "Invalid VBO index");
		glBindBuffer( _target, _bufferID );
		glBufferData( _target, _size, NULL, GL_STATIC_DRAW );
		glBufferSubData( _target, 0, _size, _data );
	}
}