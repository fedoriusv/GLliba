#ifndef _CVERTEXBUFFER_H_
#define _CVERTEXBUFFER_H_

#include "Types.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SVertexData;

	class CVertexBufferGL
	{
	private:

		static void initBufferObject( const uint _target, uint& _bufferID, const uint _size, void* _data);
		static void initVertexAttribPointer ( const uint _vertexAttrib, const uint _size );
		static void updateBufferSubData( const uint _target, const uint _bufferID, const uint _size, void* _data );
		
		static void deleteBuffers( const uint _vertexID );

	public:

		static void initBufferObjects( SVertexData& _vertexData );
		static void updateBufferObject( SVertexData& _vertexData );
		
		static void deleteBufferObjects( SVertexData& _vertexData );
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif