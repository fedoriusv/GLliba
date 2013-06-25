#ifndef _CSAMPLER_H_
#define _CSAMPLER_H_

#include "CObject.h"
#include "Param.h"

namespace glliba
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class CSampler : public CObject
	{
	private:

		uint			m_iSamplerID;

		WRAP_TYPE		m_eWrapType;
		FILTER_TYPE		m_eMinFilerType;
		FILTER_TYPE		m_eMagFilerType;

		bool			m_bNeedUpdate;

	public:
		CSampler();
		virtual			~CSampler();

		void			init();
		void			update();

		uint			getSamplerID() const;
		WRAP_TYPE		getWrapType() const;
		FILTER_TYPE		getMinFilerType() const;
		FILTER_TYPE		getMagFilerType() const;

		void			setWrapType	 ( WRAP_TYPE	_type );
		void			setFilterType( FILTER_TYPE	_minType, FILTER_TYPE _magType );

	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif