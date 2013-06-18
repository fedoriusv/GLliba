#ifndef _COBJECT_H_
#define _COBJECT_H_

#include <vector>
#include <map>
#include <algorithm>
#include "VectorMath\vectormath.h"

#include "CLogger.h"

using namespace Vectormath;

typedef unsigned int	uint;

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	enum OBJECT_TYPE
	{
		OT_UNKNOWN,
		OT_NODE,
		OT_TEXTURE,
		OT_MATERIAL,
		OT_MESH,
		OT_SHADER,
		OT_SHADER_PROGRAM,

		OT_COUNT
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	class CObject
	{
	private:

		uint				m_iRefCount;

	protected:

		uint				m_ID;
		std::string			m_name;

		OBJECT_TYPE			m_eTypeObject;

	public:

		CObject();
		~CObject();

		const std::string	getName() const;
		void				setName( const std::string& _name );
		
		uint				getID() const;
		void				setID( const uint _iId );

		uint				getRefCount() const;
		uint				releaseRef();
		CObject*			getRef();


		OBJECT_TYPE			getObjectType() const;

	};

	/////////////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif