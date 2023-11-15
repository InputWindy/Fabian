#pragma once
#include "RHIStruct.h"

class FRHI
{
public:
	static shared_ptr<FRHI> Generic(ERHIType InType);

public:
	/*
		Resource
	*/
	virtual ERHIType GetRHIType() = 0;

	//virtual shared_ptr<FRHIResource> GenericRHIResource(const FRHIResource::GenericDesc& InDesc) = 0;
public:
	/*
		Operation
	*/
};
