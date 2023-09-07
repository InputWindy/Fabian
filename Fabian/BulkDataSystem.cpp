#include "BulkDataSystem.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
struct FBulkDataList;

struct FModelBulkDataImpl :public FModelBulkData
{
	Assimp::Importer*& GetImporter() { return Holder; };
	void ReleaseData() 
	{
		if (Holder)
		{
			Holder->~Importer();
			free(Holder);
			Holder = nullptr;
			pData = nullptr;
		}
	};
};

template<>
bool FBulkDataSystem::LoadFromFile(const FImageBulkData::LoadDesc& Desc, FImageBulkData& OutImage)
{
	if (Desc.FileName.empty())return false;

	FBulkDataSystem System;
	System.GetLoadDesc(OutImage) = Desc;

	if (Desc.bHdr)
	{
		OutImage.pData = stbi_loadf(Desc.FileName.c_str(),
			&OutImage.Width,
			&OutImage.Height,
			&OutImage.Components,
			Desc.Channels);
	}
	else
	{
		OutImage.pData = stbi_load(Desc.FileName.c_str(),
			&OutImage.Width,
			&OutImage.Height,
			&OutImage.Components,
			Desc.Channels);
	}

	return true;
};

template<>
bool FBulkDataSystem::LoadFromFile(const FModelBulkData::LoadDesc& Desc, FModelBulkData& OutModelBulkData)
{
	if (Desc.FileName.empty())return false;

	FBulkDataSystem System;
	System.GetLoadDesc(OutModelBulkData) = Desc;

	FModelBulkDataImpl* pOutModel = (FModelBulkDataImpl*)&OutModelBulkData;

	pOutModel->GetImporter() = new Assimp::Importer();

	OutModelBulkData.pData = pOutModel->GetImporter()->ReadFile(Desc.FileName.c_str(), Desc.ImportFlags);

	return true;
};

template<>
void FBulkDataSystem::ReleaseData(FImageBulkData& InData)
{
	if (InData.pData)
	{
		free(InData.pData);
		InData.pData = nullptr;
	}
};

template<>
void FBulkDataSystem::ReleaseData(FModelBulkData& InData)
{
	((FModelBulkDataImpl*)&InData)->ReleaseData();
};

struct FBulkDataList
{
	friend class FBulkDataSystem;
public:
	static FBulkDataList& Get();
public:
	template<typename LAMBDA>
	void ForEach(LAMBDA&& Func)
	{
		for (IBulkData* Item : LoadedList)
		{
			Func(Item);
		}
	};

	template<typename LAMBDA>
	void ForEach(LAMBDA& Func)
	{
		for (IBulkData* Item : LoadedList)
		{
			Func(Item);
		}
	};

	void Push(IBulkData* Item)
	{
		if (Item)
		{
			LoadedList.push_back(Item);
		}
	};

	void ReleaseAll()
	{
		auto ReleaseCallback = [](IBulkData* Item)
		{
			if (Item)
			{
				FBulkDataSystem System;
				switch (Item->GetType())
				{
				case EBulkDataType::BDT_Image:
				{
					System.ReleaseData(*(FImageBulkData*)Item);
					break;
				}
				case EBulkDataType::BDT_Model:
				{
					System.ReleaseData(*(FModelBulkData*)Item);
					break;
				}
				case EBulkDataType::BDT_String:
				{
					//System.ReleaseData(*(FImageBulkData*)Item);
					break;
				}
				case EBulkDataType::BDT_Invalid:
				{
					break;
				}
				default:
					break;
				}
			}
		};
		ForEach(ReleaseCallback);
	};
private:
	//list<IBulkData*> PendingReleaseList;
	list<IBulkData*> LoadedList;
};

FBulkDataList& FBulkDataList::Get()
{
	static FBulkDataList GBulkDataList;
	return GBulkDataList;
}

EBulkDataType FImageBulkData::GetType()
{
	return EBulkDataType::BDT_Image;
}

string FImageBulkData::GetTypeString()
{
	return "Image";
}

EBulkDataType FModelBulkData::GetType()
{
	return EBulkDataType::BDT_Model;
}

string FModelBulkData::GetTypeString()
{
	return "Model";
}

void FBulkDataSystem::Register(IBulkData* InData)
{
	FBulkDataList& List = FBulkDataList::Get();
	List.Push(InData);
}

void FBulkDataSystem::ReleaseAll()
{
	FBulkDataList::Get().ReleaseAll();
}

template<>
void FBulkDataSystem::ForEach(decltype ([](IBulkData*) {}) && Lambda)
{
	/*FBulkDataList& List = FBulkDataList::Get();
	List.ForEach(forward<TBulkDataTraverseFunc>(Func));*/
}