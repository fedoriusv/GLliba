#include "CCubeShape.h"
#include "CMaterial.h"
#include "CRender.h"

namespace glliba
{
	//////////////////////////////////////////////////////////////////////////////////////////////

	CCubeShape::CCubeShape( CNode* _parent )
		: CShape(_parent)
	{
		m_eTypeShape = OST_CUBE;
		CCubeShape::init();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	CCubeShape::~CCubeShape()
	{
		m_vertices.clear();
		RENDERER->deleteBufferObjects( m_vertices );
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCubeShape::render()
	{
		if ( !m_bIsVisible )
		{
			return;
		}

		m_pMaterial->bind();

		RENDERER->updateTransform(m_worldMatrix, m_offset);
		RENDERER->drawSimple( DM_TRIANGLES, m_vertices );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCubeShape::update( double _deltaTime )
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

	//////////////////////////////////////////////////////////////////////////////////////////////

	void CCubeShape::init()
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

		RENDERER->initBufferObjects( m_vertices );

#ifndef _DEBUG
		m_vertices.clear();
#endif
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

} //glliba

