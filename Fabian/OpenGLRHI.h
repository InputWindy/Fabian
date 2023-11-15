#pragma once
#include "RHI.h"
class FOpenGLRHI:public FRHI
{
public:
	FOpenGLRHI() = default;
	virtual ~FOpenGLRHI() = default;

public:
	/*
		Resource
	*/
	virtual ERHIType GetRHIType() override;

	virtual shared_ptr<FRHIResource> GenericRHIResource(const FRHIResource::GenericDesc& InDesc) override;
public:
	/*
		Operation
	*/
};