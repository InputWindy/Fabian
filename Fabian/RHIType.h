#pragma once
#include <stdint.h>
#include <assert.h>

typedef uint32_t ERHIType;
typedef uint32_t ETextureType;
typedef uint32_t EShaderProgramUsage;
typedef uint32_t ERHIResourceType;
typedef uint32_t ESemantic;

/*
	CPU
*/
enum ERHIType_ :uint32_t
{
	E_RHI_T_None,
	 	 
	E_RHI_T_OpenglES,
	E_RHI_T_Vulkan,
	E_RHI_T_DX_12,
	E_RHI_T_Metal,
	 
	E_RHI_T_Max_Count
};

enum ETextureType_ : uint32_t
{
	E_TT_None,

	E_TT_1D,
	E_TT_2D,
	E_TT_3D,
	E_TT_1D_Array,
	E_TT_2D_Array,
	E_TT_Rectangle,
	E_TT_Cubemap,
	E_TT_Cubemap_Array,
	E_TT_Texture_Buffer,
	E_TT_2D_Multisample,
	E_TT_2D_Multisample_Array,

	E_TT_Max_Count
};

enum EShaderProgramUsage_ :uint32_t
{
	E_SU_None,
	 
	E_SU_Graphic,
	E_SU_Compute,
	 
	E_SU_Max_Count
};

enum ERHIResourceType_ :uint32_t
{
	E_GPU_RT_None,

	E_GPU_Vertex_Array,//vao
	E_GPU_RT_Buffer,
	E_GPU_RT_Texture,
	E_GPU_RT_Sampler,
	E_GPU_RT_FrameBuffer,
	E_GPU_RT_Query,
	E_GPU_RT_Shader,
	E_GPU_RT_Shader_Program,
	E_GPU_RT_RenderBuffer,
	E_GPU_RT_Pipeline,

	E_GPU_RT_Max_Count
};

enum ESemantic_ :uint32_t
{
	E_S_None,

	E_S_Attribute,//attrib (location)
	E_S_Varying,//in\out
	E_S_Uniform,//uniform image2d\sampler2d\int\vec\mat\ (location)
	E_S_Buffer_Block,//uniform myBufferBlock(binding)
	E_S_Shader_Storage_Buffer,//buffer xxx(bingding)
	E_S_Subroutines,//Subroutine xxx(bingding)
	E_S_Atomic_Counter,//atomic counter buffer(bingding)
	E_S_Transform_Feedbacks,//atomic counter buffer(bingding)
	
	E_S_Max_Count
};

/*
	GPU
*/
typedef uint32_t EBufferUsage;
typedef uint32_t EBufferDataUsage;
typedef uint32_t EBufferDataAccessPolicy;
typedef uint32_t EBufferStorageFlag;
typedef uint32_t ETextureInternalFormat;
typedef uint32_t ETextureFormat;
typedef uint32_t EDataType;
typedef uint32_t EWrapMode;
typedef uint32_t EFilterMode;
typedef uint32_t ECompareMode;
typedef uint32_t ECompareFunc;
typedef uint32_t EFrameBufferUsage;
typedef uint32_t EShaderType;
typedef uint32_t EShaderProgramInterface;


enum EBufferUsage_ :uint32_t
{
	E_BU_None, 
	
	E_BU_Vertex_Buffer				,//vbo
	E_BU_Atomic_Counter_Buffer		,//shader resource
	E_BU_Copy_Read_Buffer			,//buffer source
	E_BU_Copy_Write_Buffer			,//buffer dest
	E_BU_Dispatch_Indirect_Buffer	,
	E_BU_Draw_Indirect_Buffer		,
	E_BU_Index_Buffer				,//ibo
	E_BU_Pixel_Pack_Buffer			,
	E_BU_Pixel_Unpack_Buffer		,
	E_BU_Query_Buffer				,
	E_BU_Shader_Storage_Buffer		,//shader shared data
	E_BU_Texture_Buffer				,//tbo
	E_BU_Transform_Feedback_Buffer	,//shader resource
	E_BU_Uniform_Buffer				,//ubo
	 
	E_BU_Max_Count
};

enum EBufferDataUsage_ :uint32_t
{
	E_BDU_None,

	E_BDU_Stream_Draw	,
	E_BDU_Stream_Read 	,
	E_BDU_Stream_Copy 	,
	E_BDU_Static_Draw 	,
	E_BDU_Static_Read 	,
	E_BDU_Static_Copy 	,
	E_BDU_Dynamic_Draw 	,
	E_BDU_Dynamic_Read 	,
	E_BDU_Dynamic_Copy	,

	E_BDU_Max_Count
};

enum EBufferDataAccessPolicy_ :uint32_t
{
	E_BDAP_None ,
		 
	E_BDAP_Read_Only,
	E_BDAP_Write_Only,
	E_BDAP_Read_Write,
		 
	E_BDAP_Max_Count
};

enum EBufferStorageFlag_ : uint32_t
{
	E_BSF_None = 0,

	E_BSF_Dynamic_Storage_Bit		= 1 << 0,
	E_BSF_Map_Read_Bit				= 1 << 1,
	E_BSF_Map_Write_Bit				= 1 << 2,
	E_BSF_Map_Persistent_Bit		= 1 << 3,
	E_BSF_Map_Coherent_Bit			= 1 << 4,
	E_BSF_Client_Storage_Bit		= 1 << 5,

	E_BSF_Max_Count = 7
};

enum ETextureInternalFormat_ :uint32_t
{
	E_TIF_None,
	 
	E_TIF_Depth,
	E_TIF_Depth_Stencil,
	 
	E_TIF_R8I,
	E_TIF_RG8I,
	E_TIF_RGB8I,
	E_TIF_RGBA8I,
	E_TIF_R8UI,
	E_TIF_RG8UI,
	E_TIF_RGB8UI,
	E_TIF_RGBA8UI,
	 
	E_TIF_R16I,
	E_TIF_RG16I,
	E_TIF_RGB16I,
	E_TIF_RGBA16I,
	E_TIF_R16UI,
	E_TIF_RG16UI,
	E_TIF_RGB16UI,
	E_TIF_RGBA16UI,
	E_TIF_R16F,
	E_TIF_RG16F,
	E_TIF_RGB16F,
	E_TIF_RGBA16F,
	 
	E_TIF_R32I,
	E_TIF_RG32I,
	E_TIF_RGB32I,
	E_TIF_RGBA32I,
	E_TIF_R32UI,
	E_TIF_RG32UI,
	E_TIF_RGB32UI,
	E_TIF_RGBA32UI,
	E_TIF_R32F,
	E_TIF_RG32F,
	E_TIF_RGB32F,
	E_TIF_RGBA32F,
	 
	E_TIF_Max_Count
};

enum ETextureFormat_ :uint32_t
{
	E_TF_None,

	E_TF_Red, 
	E_TF_RG, 
	E_TF_RGB, 
	E_TF_BGR, 
	E_TF_RGBA,
	E_TF_BGRA, 
	E_TF_Red_Integer, 
	E_TF_RG_Integer, 
	E_TF_RGB_Integer, 
	E_TF_BGR_Integer, 
	E_TF_RGBA_Integer, 
	E_TF_BGRA_Integer, 
	E_TF_Stencil_Index, 
	E_TF_Depth_Component, 
	E_TF_Depth_Stencil,

	E_TF_Max_Count
};

enum EDataType_ :uint32_t
{
	E_DT_None,

	E_DT_Byte,
	E_DT_Unsigned_Byte,
	E_DT_Short,
	E_DT_Unsigned_Short,
	E_DT_Int,
	E_DT_Unsigned_Int,
	E_DT_Half_Float,
	E_DT_Float,
	E_DT_Double,
	E_DT_Fixed,

	E_DT_Max_Count
};

enum EWrapMode_ :uint32_t
{
	E_WP_None,
	 
	E_WP_Clamp_To_Edge,
	E_WP_Clamp_To_Border,
	E_WP_Mirrored_Repeat,
	E_WP_Repeat,
	E_WP_Mirror_Clamp_To_Edge,
	 
	E_WP_Max_Count
};

enum EFilterMode_ : uint32_t
{
	E_FM_None,
	 
	E_FM_Nearest,
	E_FM_Linear,
	E_FM_Nearest_Mipmap_Nearest,
	E_FM_Nearest_Mipmap_Linear,
	E_FM_Linear_Mipmap_Nearest,
	E_FM_Linear_Mipmap_Linear,
	 
	E_FM_Max_Count
};

enum ECompareMode_ :uint32_t
{
	E_CM_None,
	 
	E_CM_Compare_Ref_To_Texture,
	E_CM_None_Compare,
	 
	E_CM_Max_Count
};

enum ECompareFunc_ :uint32_t
{
	E_CF_None,
	 
	E_CF_Less_Equal,
	E_CF_Less,
	E_CF_Greater,
	E_CF_Equal,
	E_CF_Not_Equal,
	E_CF_Always,
	E_CF_Never,
	 
	E_CF_Max_Count

};

enum EFrameBufferUsage_ :uint32_t
{
	E_FBU_None,
	 
	E_FBU_Read,
	E_FBU_Write,
	E_FBU_Read_Write,
	 
	E_FBU_Max_Count
};

enum EShaderType_ :uint32_t
{
	E_ST_None,
	  
	E_ST_Vertex_Shader,
	E_ST_Tessellation_Control_Shader,
	E_ST_Tessellation_Evaluation_Shader,
	E_ST_Geometry_Shader,
	E_ST_Fragment_Shader,

	E_ST_Compute_Shader,

	E_ST_Max_Count
};

enum EShaderProgramInterface :uint32_t
{
	E_SPI_None,

	E_SPI_Uniform,
	E_SPI_Uniform_Block,
	E_SPI_Atomic_Counter_Buffer,

	E_SPI_Program_Input,
	E_SPI_Program_Output,

	E_SPI_Vertex_Subroutine,
	E_SPI_Tess_Control_Subroutine,
	E_SPI_Tess_Eval_Subroutine,
	E_SPI_Geometry_Subroutine,
	E_SPI_Fragment_Subroutine,
	E_SPI_Compute_Subroutine,

	E_SPI_Vertex_Subroutine_Uniform,
	E_SPI_Tess_Control_Subroutine_Uniform,
	E_SPI_Tess_Eval_Subroutine_Uniform,
	E_SPI_Geometry_Subroutine_Uniform,
	E_SPI_Fragment_Subroutine_Uniform,
	E_SPI_Compute_Subroutine_Uniform,

	E_SPI_Transform_Feedback_Varying,
	E_SPI_Buffer_Variable,
	E_SPI_Shader_Storage_Block,
	E_SPI_Transform_Feedback_Buffer,

	E_SPI_Max_Count
};