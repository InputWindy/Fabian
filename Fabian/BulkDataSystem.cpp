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
bool FBulkDataSystem::LoadFromFile(const FStringBulkData::LoadDesc& Desc, FStringBulkData& OutModelBulkData)
{
	if (Desc.FileName.empty())return false;

	FBulkDataSystem System;
	System.GetLoadDesc(OutModelBulkData) = Desc;

	{
		std::ifstream File;
		File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			File.open(Desc.FileName.c_str());
			std::stringstream Stream;
			Stream << File.rdbuf();

			OutModelBulkData.pData = Stream.str();
			File.close();
		}
		catch (std::ifstream::failure& e)
		{
			assert(0, "Fail to read file %s \n", e.what());
		}
	}

	return true;
}

FBulkDataSystem& FBulkDataSystem::Get()
{
	static FBulkDataSystem msSystem;
	return msSystem;
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

template<>
void FBulkDataSystem::ReleaseData(FStringBulkData& InData)
{
	InData.pData.clear();
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

	void Push(IBulkData*& Item)
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
					System.ReleaseData(*(FStringBulkData*)Item);
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
		LoadedList.clear();
	};
private:
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


EBulkDataType FStringBulkData::GetType()
{
	return EBulkDataType::BDT_String;
}

string FStringBulkData::GetTypeString()
{
	return "String";
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

	auto Iter = List.LoadedList.begin();
	while (Iter != List.LoadedList.end())
	{
		if (*Iter == InData) return;
		++Iter;
	}

	List.Push(InData);
}

void FBulkDataSystem::ReleaseAll()
{
	FBulkDataList::Get().ReleaseAll();
}

template<>
void FBulkDataSystem::ForEachInternal(TBulkDataTraverseFunc&& Lambda)
{
	FBulkDataList& List = FBulkDataList::Get();
	List.ForEach(forward<decltype(Lambda)>(Lambda));
}

template<>
void FBulkDataSystem::ForEachInternal(TBulkDataTraverseFunc& Lambda)
{
	FBulkDataList& List = FBulkDataList::Get();
	List.ForEach(forward<decltype(Lambda)>(Lambda));
}
