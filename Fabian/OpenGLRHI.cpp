#include "OpenGLRHI.h"
#include "OpenGLRHIStruct.h"
#include <glad.h>

ERHIType FOpenGLRHI::GetRHIType()
{
    return ERHIType::E_RHI_T_OpenglES;
}

//shared_ptr<FRHIResource> FOpenGLRHI::GenericRHIResource(const FRHIResource::GenericDesc& InDesc)
//{
//	switch (InDesc.ResourceType)
//	{
//	case E_GPU_RT_None:return nullptr;
//	case E_GPU_RT_Buffer:return std::make_shared<FOpenGLRHIBuffer>();
//	case E_GPU_RT_Texture:return std::make_shared<FOpenGLRHITexture>();
//	case E_GPU_RT_Sampler:return std::make_shared<FOpenGLRHISampler>();
//	case E_GPU_RT_FrameBuffer:return std::make_shared<FOpenGLRHIFrameBuffer>();
//	case E_GPU_RT_Query:return std::make_shared<FOpenGLRHIQuery>();
//	case E_GPU_RT_Shader:return std::make_shared<FOpenGLRHIShader>();
//	case E_GPU_RT_Max_Count:
//	default:
//		break;
//	}
//    return nullptr;
//}
