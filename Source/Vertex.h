#ifndef _VERTEX_H_
#define _VERTEX_H_

#ifndef NULL
#	define NULL    0
#endif

#include <VectorMath\vectormath.h>
#include <boost/functional/hash.hpp>
#include <vector>
#include <map>
#include <hash_map>

using namespace Vectormath;

typedef unsigned int	uint;


namespace glliba
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	template< class _Kty, class _Pr = _STD less<_Kty> >
	class hash_compare
	{
	private:
		_Pr pred;
	public:
		enum
		{	
			bucket_size = 4,	// 0 < bucket_size
			min_buckets = 8		// min_buckets = 2 ^^ N, 0 < N
		};	

		hash_compare()
		{	
		}

		hash_compare(_Pr _Pred)
			:pred(_Pr)
		{	
		}

		size_t operator()(const _Kty& _Keyval) const
		{	
			return (get_hash_value(_Keyval));
		}

		bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
		{	
			return (compare(_Keyval1, _Keyval2));
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class T>
	struct SVertices
	{
		uint	iVerticesID;
		T*		vertices;
		SVertices() 
			: iVerticesID(0)
			, vertices(NULL)
		{};
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	struct	SVertex;
	typedef  std::vector<SVertices<Vector2>>	TexCoords;
	typedef  std::hash_map<SVertex,size_t,hash_compare<SVertex>> HashMap;

	struct SVertexData
	{
		uint				nVertices;
		SVertices<Vector3>	Vertex;
		SVertices<Vector3>	Normal;
		TexCoords			TexCoord;

		uint				nIndices;
		SVertices<uint>		Indices;

		uint				iVertexArrayID;

		void clear();
		void malloc( uint _iCountVertices, uint _iCountIndex = 0, uint _iCountTexLayer = 1 );

		void copyVertexData( const std::vector<SVertex>& _vertices,
			const std::vector<uint>& _indices );

		void copyVertexData( const std::map<size_t,SVertex>& _vertices,
			const std::vector<uint>& _indices );

		void copyVertexData( const HashMap& _vertices,
			const std::vector<uint>& _indices );

		SVertexData();
		~SVertexData();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct SVertexHash
	{
		size_t	positionHash;
		size_t	normalHash;
		size_t	texCoordHash;
		inline bool operator==( const SVertexHash& _hash ) const
		{
			return ( positionHash == _hash.positionHash &&
				normalHash == _hash.normalHash &&
				texCoordHash == _hash.texCoordHash );
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	struct SVertex 
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoords;

		SVertexHash hashValue;
		//size_t  hashValue;

		SVertex( const Vector3& _pos = Vector3(0.0f),
			const Vector3& _normal = Vector3(0.0f),
			const Vector2& _texCoords = Vector2(0.0f) )
			: position(_pos)
			, normal(_normal)
			, texCoords(_texCoords)
		{
		}

		bool operator==( const SVertex& _vertex ) const
		{
			return hashValue == _vertex.hashValue;
			/*return ( position == _vertex.position &&
				normal == _vertex.normal &&
				texCoords == _vertex.texCoords );*/
		}

		inline void calcHash()
		{
			//hashValue = hash_value(*this);
			
			hashValue.positionHash = 0;
			boost::hash_combine(hashValue.positionHash, position.getX());
			boost::hash_combine(hashValue.positionHash, position.getY());
			boost::hash_combine(hashValue.positionHash, position.getZ());

			hashValue.normalHash = 0;
			boost::hash_combine(hashValue.normalHash, normal.getX());
			boost::hash_combine(hashValue.normalHash, normal.getY());
			boost::hash_combine(hashValue.normalHash, normal.getZ());

			hashValue.texCoordHash = 0;
			boost::hash_combine(hashValue.texCoordHash, texCoords.getX());
			boost::hash_combine(hashValue.texCoordHash, texCoords.getY());
		}

		friend std::size_t hash_value( const SVertex& _sVertex );
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::size_t get_hash_value( const SVertex& _sVertex )
	{
		return 0;//_sVertex.hashValue;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline std::size_t hash_value( const SVertex& _sVertex )
	{
		std::size_t hash = 0;

		boost::hash_combine(hash, _sVertex.position.getX());
		boost::hash_combine(hash, _sVertex.position.getY());
		boost::hash_combine(hash, _sVertex.position.getZ());

		boost::hash_combine(hash, _sVertex.normal.getX());
		boost::hash_combine(hash, _sVertex.normal.getY());
		boost::hash_combine(hash, _sVertex.normal.getZ());

		boost::hash_combine(hash, _sVertex.texCoords.getX());
		boost::hash_combine(hash, _sVertex.texCoords.getY());

		return hash;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline bool compare( const SVertex& _sVertex1, const SVertex& _sVertex2 )
	{
		return 0;//_sVertex1.hashValue < _sVertex2.hashValue;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif