/*
	BulkData:Data loaded from disk and cached in cpu memory.
*/
#pragma once
#include "pch.h"
#include "Template.h"

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

class FImageBulkData :public IBulkData
{
public:
	friend class FBulkDataSystem;
	struct LoadDesc
	{
		string FileName;
		string Description;

		int Channels = 0;

		bool bHdr = false;
	};
public:
	FImageBulkData() {};
	virtual ~FImageBulkData() {};

	virtual EBulkDataType GetType() override;
	virtual string GetTypeString() override;

	inline int GetW()const { return Width; };
	inline int GetH()const { return Height; };
	inline int GetComponents()const { return Components; };
protected:
	LoadDesc Desc;

	void* pData = nullptr;

	int Width = 0;
	int Height = 0;
	int Components = 0;
};

class FModelBulkData:public IBulkData
{
public:
	friend class FBulkDataSystem;
	struct LoadDesc
	{
		string FileName;
		string Description;

		unsigned int ImportFlags = 0;
	};
public:
	FModelBulkData() {};
	virtual ~FModelBulkData() {};

	virtual EBulkDataType GetType() override;
	virtual string GetTypeString() override;

protected:
	LoadDesc Desc;
	
	Assimp::Importer* Holder = nullptr;
	const aiScene* pData = nullptr;
};

class FStringBulkData :public IBulkData
{
public:
	friend class FBulkDataSystem;
	struct LoadDesc
	{
		string FileName;
		string Description;
	};
public:
	FStringBulkData() {};
	virtual ~FStringBulkData() {};

	virtual EBulkDataType GetType() override;
	virtual string GetTypeString() override;

protected:
	LoadDesc Desc;

	string pData;
};

class FBulkDataSystem
{
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

	using TBulkDataTraverseFunc = TCallbackFunc<void, class IBulkData*>;

	template<typename LAMBDA>
	void ForEach(LAMBDA&& Lambda)
	{
		ForEachInternal(forward<TBulkDataTraverseFunc&&>(TBulkDataTraverseFunc(Lambda)));
	};

	template<typename LAMBDA>
	void ForEach(LAMBDA& Lambda)
	{
		ForEachInternal(forward<TBulkDataTraverseFunc&>(TBulkDataTraverseFunc(Lambda)));
	};
public:
	//============//
	//   Queries  //
	//============//
	template<typename TData>
	bool IsEmpty(TData& InData)
	{
		return GetBulkData(InData) == nullptr;
	};

	template<typename TData>
	auto& GetLoadDesc(TData& InData)
	{
		return InData.Desc;
	}

	template<typename TData>
	const auto GetBulkData(TData& InData)const
	{
		return InData.pData;
	}

public:
	void Register(IBulkData* InData);
	void ReleaseAll();
private:
	template<typename LAMBDA>
	void ForEachInternal(LAMBDA&& Lambda);

	template<typename LAMBDA>
	void ForEachInternal(LAMBDA& Lambda);
};


