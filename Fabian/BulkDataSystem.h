#pragma once
#include "pch.h"

enum class EBulkDataType
{
	BDT_Image,
	BDT_Model,
	BDT_String,

	BDT_Invalid
};

class IBulkData 
{
protected:
	IBulkData() {};
public:
	virtual~IBulkData() {};

	virtual EBulkDataType GetType() = 0;
	virtual string GetTypeString() = 0;
};

struct FImageBulkData:public IBulkData
{
	struct LoadDesc
	{
		string FileName;
		int Channels = 0;

		bool bHdr = false;
	};

	void* pData = nullptr;

	int Width = 0;
	int Height = 0;
	int Components = 0;

public:
	virtual EBulkDataType GetType() override;
	virtual string GetTypeString() override;
public:
	LoadDesc Desc;
};

struct FModelBulkData :public IBulkData
{
	struct LoadDesc
	{
		string FileName;
		unsigned int ImportFlags = 0;
	};

	const aiScene* pData = nullptr;
public:
	virtual EBulkDataType GetType() override;
	virtual string GetTypeString() override;

	LoadDesc Desc;
protected:
	Assimp::Importer* Holder = nullptr;
};


class FBulkDataSystem
{
	using TBulkDataTraverseFunc = decltype ([](IBulkData*) {});
public:
	template<typename TDesc, typename TData>
	bool LoadFromFile(const TDesc& InDesc, TData& InData);

	template<typename TData>
	void ReleaseData(TData& InData);

	template<typename TData>
	bool ReloadFile(TData& InData)
	{
		ReleaseData(InData);
		return LoadFromFile(InData.Desc, InData);
	};
public:
	//============//
	//    Gets    //
	//============//
	template<typename TData,typename TDesc = TData::LoadDesc>
	TDesc& GetLoadDesc(TData& InData)
	{
		return InData.Desc;
	};

	template<typename TData>
	EBulkDataType GetBulkDataType()
	{
		if (is_same_v<TData, FImageBulkData>)return EBulkDataType::BDT_Image;
		else if (is_same_v<TData, FModelBulkData>)return EBulkDataType::BDT_Model;
		else assert(0, "Invalid BulkDataType");

		return EBulkDataType::BDT_Invalid;
	};

	template<typename TData>
	string GetBulkDataTypeString(TData& InData)
	{
		if (is_same_v<TData, FImageBulkData>)return "Image";
		else if (is_same_v<TData, FModelBulkData>)return "Model";
		else assert(0, "Invalid BulkDataType");

		return "Invalid";
	};
public:
	//============//
	//   Queries  //
	//============//
	template<typename TData>
	bool IsEmpty(TData& InData)
	{
		return InData.pData != nullptr;
	};

	template<typename LAMBDA>
	void ForEach(LAMBDA&& Lambda);


public:
	void Register(IBulkData* InData);
	void ReleaseAll();
};