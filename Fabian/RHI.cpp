#include "RHI.h"
#include "OpenGLRHI.h"

shared_ptr<FRHI> FRHI::Generic(ERHIType InType)
{
	switch (InType)
	{
	case E_RHI_T_None:return nullptr;
	case E_RHI_T_OpenglES:return std::make_shared<FOpenGLRHI>();
	case E_RHI_T_Vulkan:
	case E_RHI_T_DX_12:
	case E_RHI_T_Metal:
	case E_RHI_T_Max_Count:
	default:
		break;
	}
	return nullptr;
}
