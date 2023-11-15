#pragma once
#include <vector>
#include <memory>
#include <string.h>
#include <map>

#include "Common.h"
#include "RHIType.h"

using std::vector;
using std::shared_ptr;
using std::string;
using std::map;

//CPU


//GPU
class FRHIResource:public INoneCopyable
{
protected:
	FRHIResource() = default;
public:
	virtual ~FRHIResource() = default;

	/*
		Query
	*/
	virtual bool IsValid() = 0;
	virtual ERHIResourceType GetResourceType()const = 0;

	/*
		Resource interface
	*/
	virtual bool InitRHI() = 0;
	virtual bool ReleaseRHI() = 0;
};

class FRHIVertexArray : public FRHIResource
{
protected:
	FRHIVertexArray() = default;
public:
	virtual ~FRHIVertexArray() = default;
public:
	virtual void Bind()   const = 0;
	virtual void UnBind() const = 0;
	
	/*
		Vertex attribute
	*/
	virtual void EnableAttribute(uint8_t InIdx)  const = 0;
	virtual void DisableAttribute(uint8_t InIdx) const = 0;

	virtual void SetAttributeFormat(uint32_t InAttribIdx, int InCompNum, EDataType InType, bool bNormalized, uint32_t InOffset) const = 0;
	virtual void SetAttributeBinding(uint32_t InAttribIdx, uint32_t InBindingIdx) const = 0;
	virtual void SetVertexBindingDivisor(uint32_t InDivisor) const = 0;

	/*
		Set data
	*/
	virtual void BindVertexBuffer(uint32_t InBindingIdx, uint32_t InBuffer, size_t InOffset, int InStride) const = 0;
	virtual void SetAttributePointer(uint32_t InAttribIdx, int InCompNum, EDataType InType, bool bNormalized, int InStride, size_t InOffset) const = 0;

	virtual ERHIResourceType GetResourceType()const final { return E_GPU_Vertex_Array; };
};

class FRHIShader : public FRHIResource
{
protected:
	FRHIShader() = default;
public:
	virtual ~FRHIShader() = default;

	/*
		Operation
	*/
	virtual void SetShaderSourceCode(const string&) = 0;
	virtual void GetShaderSourceCode(string&) = 0;
	virtual void GetShaderInfoLog(string&) = 0;
	virtual EShaderType GetShaderType()const = 0;

	virtual bool Compile()const = 0;
	virtual bool IsCompiled()const = 0;

	/*
		Get & Set
	*/
	virtual ERHIResourceType GetResourceType()const final { return E_GPU_RT_Shader; };
};

class FRHIShaderProgram : public FRHIResource
{
public:
	struct FShaderParameter
	{
		struct 
		{

		}Attributes;

		struct
		{

		}Varyings;

		struct
		{

		}Uniforms;

		struct
		{

		}UniformBlocks;

		struct
		{

		}SSBOs;

		struct
		{

		}Subroutines;

		struct
		{

		}AtomicCounters;

		struct
		{

		}TransformFeedbacks;
	};
protected:
	FRHIShaderProgram() = default;
public:
	virtual ~FRHIShaderProgram() = default;

	/*
		Operation
	*/
	virtual bool Link() const = 0;
	virtual void Use()  const = 0;
	virtual void AttachShader(shared_ptr<FRHIShader> InShader) const = 0;
	virtual void GetShaderProgramInfoLog(string& InOutInfoLog) const = 0;

	/*
		Reflection
	*/
	virtual void GetActiveShaderParameters(FShaderParameter&) const = 0;
	
	
	/*
		Set uniform
	*/
	virtual void SetSubroutine(EShaderType, uint32_t, vector<uint32_t>&)const = 0;
	virtual void SetShaderBuffer(const char*, shared_ptr<FRHIShaderBuffer>) = 0; // ubo holds its binding point id
	virtual void SetSampler(const char*,shared_ptr<FRHITexture>) = 0;
	virtual void SetTextureImage(const char*, shared_ptr<FRHITextureImage>) = 0;

	virtual void SetBool1(const char*, bool) = 0;
	virtual void SetBool2(const char*, bool, bool) = 0;
	virtual void SetBool3(const char*, bool, bool, bool) = 0;
	virtual void SetBool4(const char*, bool, bool, bool, bool) = 0;

	virtual void SetFloat1(const char*, float) = 0;
	virtual void SetFloat2(const char*, float, float) = 0;
	virtual void SetFloat3(const char*, float, float, float) = 0;
	virtual void SetFloat4(const char*, float, float, float, float) = 0;

	virtual void SetInt1(const char*, int) = 0;
	virtual void SetInt2(const char*, int, int) = 0;
	virtual void SetInt3(const char*, int, int, int) = 0;
	virtual void SetInt4(const char*, int, int, int, int) = 0;

	virtual void SetUInt1(const char*, uint32_t) = 0;
	virtual void SetUInt2(const char*, uint32_t, uint32_t) = 0;
	virtual void SetUInt3(const char*, uint32_t, uint32_t, uint32_t) = 0;
	virtual void SetUInt4(const char*, uint32_t, uint32_t, uint32_t, uint32_t) = 0;

	virtual void SetFloat1(const char*, float) = 0;
	virtual void SetFloat2(const char*, float, float) = 0;
	virtual void SetFloat3(const char*, float, float, float) = 0;
	virtual void SetFloat4(const char*, float, float, float, float) = 0;

	virtual void SetFloat1Array(const char*, size_t, float*) = 0;
	virtual void SetFloat2Array(const char*, size_t, float*) = 0;
	virtual void SetFloat3Array(const char*, size_t, float*) = 0;
	virtual void SetFloat4Array(const char*, size_t, float*) = 0;

	virtual void SetInt1Array(const char*, size_t, int*) = 0;
	virtual void SetInt2Array(const char*, size_t, int*) = 0;
	virtual void SetInt3Array(const char*, size_t, int*) = 0;
	virtual void SetInt4Array(const char*, size_t, int*) = 0;

	virtual void SetUInt1Array(const char*, size_t, uint32_t*) = 0;
	virtual void SetUInt2Array(const char*, size_t, uint32_t*) = 0;
	virtual void SetUInt3Array(const char*, size_t, uint32_t*) = 0;
	virtual void SetUInt4Array(const char*, size_t, uint32_t*) = 0;

	virtual void SetMatrixFloat2x2Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat3x3Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat4x4Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat2x3Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat3x2Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat2x4Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat4x2Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat3x4Array(const char*, size_t, bool, float*) = 0;
	virtual void SetMatrixFloat4x3Array(const char*, size_t, bool, float*) = 0;

	/*
		Get & Set
	*/
	EShaderProgramUsage GetShaderProgramType()const { return ShaderProgramType; };
	virtual ERHIResourceType GetResourceType()const final { return E_GPU_RT_Shader_Program; };

protected:
	EShaderProgramUsage ShaderProgramType = E_SU_None;
};

class FRHIBuffer : public FRHIResource
{
protected:
	FRHIBuffer() = default;
public:
	virtual ~FRHIBuffer() = default;

	/*
		Operation
	*/
	virtual void SetBufferStorage(size_t, const void*, EBufferStorageFlag = E_BSF_Map_Read_Bit | E_BSF_Map_Write_Bit | E_BSF_Map_Persistent_Bit | E_BSF_Map_Coherent_Bit)const = 0;
	virtual void SetBufferData(size_t,const void*,EBufferDataUsage = E_BDU_Static_Draw) const = 0;//dynamic buffer size
	virtual void ClearBufferData(ETextureInternalFormat,ETextureFormat,EDataType,const void*)const = 0;//used for texture buffer object
	
	virtual void* MapBufferData(EBufferDataAccessPolicy = E_BDAP_Read_Write)const = 0;
	virtual bool UnmapBufferData()const = 0;
	virtual bool IsMapped()const = 0;
	
	virtual size_t GetBufferSize()const = 0;
	virtual EBufferDataAccessPolicy GetBufferDataAccessPolicy()const = 0;
	virtual EBufferStorageFlag GetBufferStorageFlag()const = 0;

	virtual void CopyFrom(shared_ptr<FRHIBuffer>)const = 0;

	/*
		Get & Set
	*/
	virtual EBufferUsage GetBufferUsage()const = 0;
	virtual ERHIResourceType GetResourceType()const final { return E_GPU_RT_Buffer; };
};

class FRHIVertexBuffer : public FRHIBuffer
{
protected:
	FRHIVertexBuffer() = default;
public:
	virtual ~FRHIVertexBuffer() = default;

	/*
		Operation
	*/
	virtual void Bind()const = 0;
	virtual void UnBind()const = 0;

	virtual EBufferUsage GetBufferUsage()const final { return E_BU_Vertex_Buffer; };
};

class FRHIIndexBuffer : public FRHIBuffer
{
protected:
	FRHIIndexBuffer() = default;
public:
	virtual ~FRHIIndexBuffer() = default;

	/*
		Operation
	*/
	virtual void Bind()const = 0;
	virtual void UnBind()const = 0;

	virtual EBufferUsage GetBufferUsage()const final { return E_BU_Index_Buffer; };
};

class FRHIShaderBuffer : public FRHIBuffer
{
protected:
	FRHIShaderBuffer() = default;
public:
	virtual ~FRHIShaderBuffer() = default;

	/*
		Operation
	*/
	virtual void Bind(uint32_t)const = 0;//binding point
	virtual void Bind(uint32_t,size_t,size_t)const = 0;//binding point,offset,size
	virtual void UnBind()const = 0;

	virtual uint32_t GetBindingPoint()const = 0;
};

class FRHIShaderUniformBlockBuffer : public FRHIShaderBuffer
{
protected:
	FRHIShaderUniformBlockBuffer() = default;
public:
	virtual ~FRHIShaderUniformBlockBuffer() = default;

	virtual EBufferUsage GetBufferUsage()const final{ return E_BU_Uniform_Buffer; };
};

class FRHIShaderStorageBuffer : public FRHIShaderBuffer
{
protected:
	FRHIShaderStorageBuffer() = default;
public:
	virtual ~FRHIShaderStorageBuffer() = default;

	virtual EBufferUsage GetBufferUsage()const final { return E_BU_Shader_Storage_Buffer; };
};

class FRHIShaderTransformFeedbackBuffer : public FRHIShaderBuffer
{
protected:
	FRHIShaderTransformFeedbackBuffer() = default;
public:
	virtual ~FRHIShaderTransformFeedbackBuffer() = default;

	virtual EBufferUsage GetBufferUsage()const final { return E_BU_Transform_Feedback_Buffer; };
};

class FRHIShaderAtomicCounterBuffer : public FRHIShaderBuffer
{
protected:
	FRHIShaderAtomicCounterBuffer() = default;
public:
	virtual ~FRHIShaderAtomicCounterBuffer() = default;

	virtual EBufferUsage GetBufferUsage()const final { return E_BU_Atomic_Counter_Buffer; };
};

class FRHISampler : public FRHIResource
{
protected:
	FRHISampler() = default;
public:
	virtual ~FRHISampler() = default;

	virtual ERHIResourceType GetResourceType()const final { return E_GPU_RT_Sampler; };
public:
	EWrapMode WrapR = EWrapMode_::E_WP_None;
	EWrapMode WrapS = EWrapMode_::E_WP_None;
	EWrapMode WrapT = EWrapMode_::E_WP_None;

	EFilterMode MinFilter = EFilterMode_::E_FM_None;
	EFilterMode MagFilter = EFilterMode_::E_FM_None;

	uint8_t MinMipLevel = 0;
	uint8_t MaxMipLevel = 0;

	vector<float> BorderColor = { 0,0,0,0 };

	ECompareMode CompareMode = ECompareMode_::E_CM_None;
	ECompareFunc CompareFunc = ECompareFunc_::E_CF_None;
};

//============================================//




class FRHIPipeline : public FRHIResource
{
protected:
	FRHIPipeline() = default;
public:
	virtual ~FRHIPipeline() = default;
public:
	virtual ERHIResourceType GetResourceType()const final { return E_GPU_RT_Pipeline; };

};



class FRHITexture :  public FRHIResource
{
protected:
	FRHITexture() = default;
public:
	virtual ~FRHITexture() = default;
public:
	ETextureType Type	  = ETextureType_::E_TT_None;

	uint32_t     Width    = 0;
	uint32_t     Height   = 0;
	uint32_t     Depth    = 0;

	ETextureInternalFormat InternalFormat = ETextureInternalFormat_::E_TIF_None;

	shared_ptr<FRHISampler> Sampler = nullptr;
};

class FRHIRenderBuffer : public FRHIResource
{
protected:
	FRHIRenderBuffer() = default;
public:
	virtual ~FRHIRenderBuffer() = default;
public:
	virtual ERHIResourceType GetResourceType()const { return E_GPU_RT_RenderBuffer; };

};

class FRHITextureImage : public FRHIResource
{
protected:
	FRHITextureImage() = default;
public:
	virtual ~FRHITextureImage() = default;

};

class FRHIFrameBuffer :  public FRHIResource
{
protected:
	FRHIFrameBuffer() = default;
public:
	virtual ~FRHIFrameBuffer() = default;
public:
	EFrameBufferUsage Usage = EFrameBufferUsage_::E_FBU_None;

	vector<shared_ptr<FRHITexture>> ColorAttachments;
	shared_ptr<FRHIBuffer> DepthStencilAttachment;

	uint32_t Width  = 0;
	uint32_t Height = 0;
};

class FRHIQuery :  public FRHIResource
{
protected:
	FRHIQuery() = default;
public:
	virtual ~FRHIQuery() = default;
public:

};

