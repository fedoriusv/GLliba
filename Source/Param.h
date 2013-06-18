#pragma once

#ifndef _PARAM_H_
#define _PARAM_H_

#ifdef WIN32
#	include <windows.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include "VectorMath\vectormath.h"

#ifdef _OPENGL
#	define GLEW_STATIC 
#	include "Glew\glew-1.9.0\include\GL\glew.h"
#	include "Glew\glew-1.9.0\include\GL\wglew.h"

#	ifdef _DEBUG
#		pragma comment(lib,"Glew\\glew-1.9.0\\lib\\glew32s.lib")
#	else
#		pragma comment(lib,"Glew\\glew-1.9.0\\lib\\glew32s.lib")
#	endif

#	include <gl/gl.h>
#	include <gl/glu.h>
#	pragma comment(lib,"OpenGL32.lib")
#	pragma comment(lib,"GLU32.lib")
#endif

#ifdef _USE_DEVIL
#	ifdef _OPENGL
#		define ILUT_USE_OPENGL
#	endif
#	include "DevIL-1.7.8\include\IL\il.h"
#	pragma comment(lib,"DevIL-1.7.8\\lib\\DevIL.lib")
#endif

namespace glliba
{

	///////////////////////////////////////////////////////////////////////////////////////

	enum FOG_MODE
	{
#if defined ( _OPENGL ) || defined ( _GLES )
		FM_LINEAR		=	GL_LINEAR,
		FM_EXP			=	GL_EXP,
		FM_EXP2			=	GL_EXP2,
#else
		FM_LINEAR		=	0,
		FM_EXP			=	1,
		FM_EXP2			=	2,
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum DRAW_MODE
	{
#if defined ( _OPENGL ) || defined ( _GLES )
		
		/*DM_QUADS			= GL_QUADS,
		DM_QUAD_STRIP		= GL_QUAD_STRIP,*/
		
		DM_TRIANGLE_STRIP	= GL_TRIANGLE_STRIP,
		DM_TRIANGLES		= GL_TRIANGLES,
		DM_TRIANGLE_FAN		= GL_TRIANGLE_FAN,
#else
		DM_QUARD			= 0,
		DM_QUAD_STRIP		= 1,
		DM_TRIANGLE_STRIP	= 2,
		DM_TRIANGLES		= 3,
		DM_TRIANGLE_FAN		= 4,
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum TEXTURE_TYPE
	{
		TD_INVALID			= 0,
#if defined ( _OPENGL ) || defined ( _GLES )
		TT_TEXTURE1D		= GL_TEXTURE_1D,
		TT_TEXTURE2D		= GL_TEXTURE_2D,
		TT_TEXTURE3D		= GL_TEXTURE_3D,
		TT_TEXTURE_CUBEMAP	= GL_TEXTURE_CUBE_MAP,
#else
		TD_TEXTURE1D		= 1,
		TD_TEXTURE2D		= 2,
		TD_TEXTURE3D		= 3,
		TD_TEXTURE_CUBEMAP	= 4,
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum IMAGE_FORMAT
	{
#ifdef _USE_DEVIL
		IF_COLOUR_INDEX		= IL_COLOUR_INDEX,
		IF_COLOR_INDEX		= IL_COLOR_INDEX,
		IF_ALPHA			= IL_ALPHA,
		IF_RGB				= IL_RGB,
		IF_RGBA				= IL_RGBA,
		IF_BGR				= IL_BGR,
		IF_BGRA				= IL_BGRA,
		IF_LUMINANCE		= IL_LUMINANCE,
		IF_LUMINANCE_ALPHA	= IL_LUMINANCE_ALPHA,

#else
		IF_COLOUR_INDEX,	
		IF_COLOR_INDEX,		
		IF_ALPHA,			
		IF_RGB,				
		IF_RGBA,			
		IF_BGR,				
		IF_BGRA	,			
		IF_LUMIANCE,		
		IF_LUMINANCE_ALPHA,	
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum IMAGE_TYPE
	{
#ifdef _USE_DEVIL
		IT_BYTE				= IL_BYTE,
		IT_UNSIGNED_BYTE	= IL_UNSIGNED_BYTE,
		IT_SHORT			= IL_SHORT,
		IT_UNSIGNED_SHORT	= IL_UNSIGNED_SHORT,
		IT_INT				= IL_INT,
		IT_UNSIGNED_INT		= IL_UNSIGNED_INT,
		IT_FLOAT			= IL_FLOAT,
		IT_DOUBLE			= IL_DOUBLE,
		IT_HALF				= IL_HALF,
#else
		IT_BYTE,			
		IT_UNSIGNED_BYTE,
		IT_SHORT,		
		IT_UNSIGNED_SHORT,
		IT_INT,			
		IT_UNSIGNED_INT,	
		IT_FLOAT,		
		IT_DOUBLE,		
		IT_HALF,			
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum FILTER_TYPE
	{
#if defined ( _OPENGL ) || defined ( _GLES )
		FT_NEAREST					= GL_NEAREST,
		FT_LINEAR					= GL_LINEAR,
		
		FT_NEAREST_MIPMAP_NEAREST	= GL_NEAREST_MIPMAP_NEAREST,
		FT_LINEAR_MIPMAP_NEAREST	= GL_LINEAR_MIPMAP_NEAREST,
		FT_NEAREST_MIPMAP_LINEAR	= GL_NEAREST_MIPMAP_LINEAR,
		FT_LINEAR_MIPMAP_LINEAR		= GL_LINEAR_MIPMAP_LINEAR,
#else	
		FT_NEAREST = 0,					
		FT_LINEAR,					
		
		FT_NEAREST_MIPMAP_NEAREST,	
		FT_LINEAR_MIPMAP_NEAREST,	
		FT_NEAREST_MIPMAP_LINEAR,	
		FT_LINEAR_MIPMAP_LINEAR,		
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////

	enum WRAP_TYPE
	{
#if defined ( _OPENGL ) || defined ( _GLES )
		WT_REPEAT			= GL_REPEAT,
		WT_CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
		WT_MIRRORED_REPEAT	= GL_MIRRORED_REPEAT,
		WT_CLAMP_TO_BORDER	= GL_CLAMP_TO_BORDER,
#else
		WT_REPEAT,			
		WT_CLAMP_TO_EDGE,
		WT_MIRRORED_REPEAT,
		WT_CLAMP_TO_BORDER,
#endif
	};
	
	///////////////////////////////////////////////////////////////////////////////////////

} //glliba

#endif