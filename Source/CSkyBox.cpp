#include "CSkyBox.h"
#include "CRender.h"
#include "CResourceManager.h"
#include "CTextureManager.h"

const std::string vertShaderSkyBox = "data/skybox.vsh";
const std::string fragShaderSkyBox = "data/skybox.psh";

namespace glliba
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	CSkyBox::CSkyBox()
		: CNode(nullptr)
		, m_bIsLoad(false)
		, m_pShader(nullptr)
	{
		m_eTypeNode = TN_SKYBOX;
		LOG_CONSOLE( "Initialize node " << type_node[m_eTypeNode].c_str());

		for ( uint texture = 0; texture < 6U; ++texture )
		{
			m_pSkyBoxTexture[texture] = nullptr;
		}

		CSkyBox::init();

		m_eDrawParam._iCullFaceMode  = FM_FRONT;
		m_eDrawParam._iDepthFuncMode = DF_LEQUAL;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	CSkyBox::~CSkyBox()
	{
		if ( m_bIsLoad )
		{
			for ( uint texture = 0; texture < 6U; ++texture )
			{
				delete m_pSkyBoxTexture[texture];
				m_pSkyBoxTexture[texture] = nullptr;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::loadSkyBox(const std::string* _fileNames )
	{
		if (m_bIsLoad)
		{
			destroySkyBox();
		}
		
		for ( uint texure = 0; texure < 6U; ++texure )
		{
				m_pSkyBoxTexture[texure] = TEXTURE_MGR->createTexture( _fileNames[texure] );
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
		m_pShader = new CShader();
		m_pShader->loadShader(vertShaderSkyBox,fragShaderSkyBox);

		m_vertices.malloc( 24 );

		float s = 50.0f;

		float vertex[][3] = 
		{
			{ s, s, s },  { s,-s, s },  {-s, s, s },  {-s,-s, s },
			{-s, s,-s },  {-s,-s,-s },  { s, s,-s },  { s,-s,-s },
			{-s, s, s },  {-s,-s, s },  {-s, s,-s },  {-s,-s,-s },
			{ s, s,-s },  { s,-s,-s },  { s, s, s },  { s,-s, s },
			{-s, s,-s },  { s, s,-s },  {-s, s, s },  { s, s, s },
			{ s,-s,-s },  {-s,-s,-s },  { s,-s, s },  {-s,-s, s } 
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
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f}, 
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f}, 
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f},
			{0.0f, 0.0f},	{0.0f, 1.0f},	{1.0f, 0.0f},	{1.0f, 1.0f}
		};
		
		memcpy(m_vertices.Vertex.vertices,vertex,sizeof(vertex));
		memcpy(m_vertices.Normal.vertices,normals,sizeof(normals));
		memcpy(m_vertices.TexCoord.at(0).vertices,texCoord,sizeof(texCoord));

		RENDERER->initBufferObjects( m_vertices );
		
		m_vertices.clear();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		RENDERER->preDrawSimple(m_eDrawParam);

		RENDERER->bindShader( m_pShader->getShaderID() );
		for ( uint i = 0; i < 6; ++i )
		{
			RENDERER->bindTexture(m_pSkyBoxTexture[i]->getTextureID(),m_pSkyBoxTexture[i]->getSamplerID(),
				0,"skyBox",m_pSkyBoxTexture[i]->getTarget(),m_pSkyBoxTexture[i]->getScale());
			
			RENDERER->updateTransform(m_worldMatrix, m_offset);
			RENDERER->drawSimple( DM_TRIANGLE_STRIP, m_vertices, i*4, 4 );
		}
		RENDERER->postDrawSimple();
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CSkyBox::update( double _deltaTime )
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		if ( m_bNeedUpdate )
		{
			CNode::updateTransform( _deltaTime );
			m_bNeedUpdate = false;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}