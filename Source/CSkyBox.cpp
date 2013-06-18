#include "CSkyBox.h"
#include "CRender.h"
#include "CResourceManager.h"

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	CSkyBox::CSkyBox()
		: CNode(NULL)
		, m_bIsLoad(false)
	{
		m_eTypeNode = TN_SKYBOX;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());

		for ( uint texNo = 0; texNo < 6U; ++texNo )
		{
			m_pSkyBoxTexture[texNo] = nullptr;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	CSkyBox::~CSkyBox()
	{
		if ( m_bIsLoad )
		{
			delete[] m_pSkyBoxTexture;
			for ( uint texNo = 0; texNo < 6U; ++texNo )
			{
				m_pSkyBoxTexture[texNo] = nullptr;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::loadSkyBox(const std::string* _fileName[6] )
	{
		if (m_bIsLoad)
		{
			destroySkyBox();
		}
		
		for ( uint texNo = 0; texNo < 6U; ++texNo )
		{
				m_pSkyBoxTexture[texNo] = ResourceMgr->createTexture( _fileName[texNo] );
		}

		m_bIsLoad = true;

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::destroySkyBox()
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::init()
	{
		m_vertices.malloc( 24, 36 );

		float s = 0.5f;

		float vertex[][3] = 
		{
			{-s,-s, s },  { s,-s, s },  { s, s, s },  {-s, s, s },
			{-s,-s,-s },  {-s, s,-s },  { s, s,-s },  { s,-s,-s },
			{-s, s,-s },  {-s, s, s },  { s, s, s },  { s, s,-s },
			{-s,-s,-s },  { s,-s,-s },  { s,-s, s },  {-s,-s, s },
			{ s,-s,-s },  { s, s,-s },  { s, s, s },  { s,-s, s },
			{-s,-s,-s },  {-s,-s, s },  {-s, s, s },  {-s, s,-s } 
		};

		float normals[][3] =
		{
			{ 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f},
			{ 0.0f, 0.0f,-1.0f}, { 0.0f, 0.0f,-1.0f}, { 0.0f, 0.0f,-1.0f}, { 0.0f, 0.0f,-1.0f},
			{ 0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 0.0f},
			{ 0.0f,-1.0f, 0.0f}, { 0.0f,-1.0f, 0.0f}, { 0.0f,-1.0f, 0.0f}, { 0.0f,-1.0f, 0.0f},
			{ 1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}
		};

		float texCoord[][2] =
		{
			{0.0f, 0.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 1.0f},
			{1.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 1.0f},	{0.0f, 0.0f},
			{0.0f, 1.0f},	{0.0f, 0.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},
			{1.0f, 1.0f},	{0.0f, 1.0f},	{0.0f, 0.0f},	{1.0f, 0.0f},
			{1.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 1.0f},	{0.0f, 0.0f},
			{0.0f, 0.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},	{0.0f, 1.0f}
		};
		
		uint cubeIndices[] = 
		{
			0,	3,	1,  1,	3,	2,	// front
			4,	7,	5,  5,	7,	6,	// back
			8,	11, 9,  9,	11,	10, // top
			12,	15,	13, 13,	15,	14, // bottom
			16,	19,	17, 17,	19,	18, // left
			20,	23,	21,	21,	23,	22  // right
		};

		memcpy(m_vertices.Vertex.vertices,vertex,sizeof(vertex));
		memcpy(m_vertices.Normal.vertices,normals,sizeof(normals));
		memcpy(m_vertices.TexCoord.at(0).vertices,texCoord,sizeof(texCoord));
		memcpy(m_vertices.Indices.vertices,cubeIndices,sizeof(cubeIndices));

		RENDER->initBufferObjects( m_vertices );
		
		m_vertices.clear();
	}

	void CSkyBox::render()
	{

	}

	void CSkyBox::update()
	{

	}
}