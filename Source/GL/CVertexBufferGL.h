#ifndef _CVERTEXBUFFER_H_
#define _CVERTEXBUFFER_H_

#include "Types.h"

namespace glliba
{
	struct SVertexData;

	class CVertexBufferGL
	{
	private:

		static void initBufferObjectGL( const uint _target, uint& _bufferID, const uint _size, void* _data);
		static void initVertexAttribPointerGL( const uint _vertexAttrib, const uint _size );

		static void updateBufferSubDataGL( const uint _target, const uint _bufferID, const uint _size, void* _data );
		
		static void deleteBuffersGL( const uint _vertexID );

	public:

		static void initBufferObjectsGL( SVertexData& _vertexData );

		static void updateBufferObjectGL( SVertexData& _vertexData );
		
		static void deleteBufferObjectsGL( SVertexData& _vertexData );
	};
}

#endif