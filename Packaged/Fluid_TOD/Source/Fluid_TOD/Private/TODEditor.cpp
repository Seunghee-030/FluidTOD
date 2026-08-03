#include "TODEditor.h"
#include "TODManager.h"

#if WITH_EDITOR
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Editor/EditorEngine.h"
#endif

void FTODEditor::SaveNewPreset(ATODManager* Owner)
{
#if WITH_EDITOR
	if (!Owner) return;

	FString Timestamp = FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S"));
	FString DefaultAssetName = FString::Printf(TEXT("TOD_Preset_%s"), *Timestamp);
	FString DefaultPath = TEXT("/Game/TOD_Presets");

	FSaveAssetDialogConfig SaveAssetDialogConfig;
	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString(TEXT("Save TOD Preset"));
	SaveAssetDialogConfig.DefaultPath = DefaultPath;
	SaveAssetDialogConfig.DefaultAssetName = DefaultAssetName;
	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;

	FContentBrowserModule& ContentBrowserModule =
		FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FString SaveObjectPath =
		ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);

	if (!SaveObjectPath.IsEmpty())
	{
		FString PackagePath = FPaths::GetPath(SaveObjectPath);
		FString AssetName = FPaths::GetBaseFilename(SaveObjectPath);

		IAssetTools& AssetTools =
			FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		UTODPresetData* NewAsset = Cast<UTODPresetData>(
			AssetTools.CreateAsset(
				AssetName,
				PackagePath,
				UTODPresetData::StaticClass(),
				nullptr));

		if (NewAsset)
		{
			NewAsset->TOD_DataArray = Owner->TOD_DataArray;

			for (FTODMasterData& Data : NewAsset->TOD_DataArray)
			{
				Data.PPV = nullptr;
			}

			NewAsset->MarkPackageDirty();
			FAssetRegistryModule::AssetCreated(NewAsset);

			Owner->LoadPreset = NewAsset;

			FNotificationInfo Info(
				FText::Format(
					FText::FromString(TEXT("Saved: {0}")),
					FText::FromString(AssetName)));

			Info.ExpireDuration = 3.0f;
			FSlateNotificationManager::Get().AddNotification(Info);
		}
	}
#endif
}

void FTODEditor::SaveCurrentPreset(ATODManager* Owner)
{
#if WITH_EDITOR
	if (!Owner || !Owner->LoadPreset) return;

	Owner->LoadPreset->TOD_DataArray = Owner->TOD_DataArray;

	for (FTODMasterData& Data : Owner->LoadPreset->TOD_DataArray)
	{
		Data.PPV = nullptr;
	}

	Owner->LoadPreset->MarkPackageDirty();

	FNotificationInfo Info(
		FText::Format(
			FText::FromString(TEXT("Overwrote: {0}")),
			FText::FromString(Owner->LoadPreset->GetName())));

	Info.ExpireDuration = 3.0f;
	FSlateNotificationManager::Get().AddNotification(Info);
#endif
}

void FTODEditor::OpenPresetDialog(ATODManager* Owner)
{
#if WITH_EDITOR
	if (!Owner) return;

	FOpenAssetDialogConfig OpenAssetDialogConfig;
	OpenAssetDialogConfig.DialogTitleOverride =
		FText::FromString(TEXT("Load TOD Preset"));

	OpenAssetDialogConfig.DefaultPath = TEXT("/Game/TOD_Presets");
	OpenAssetDialogConfig.bAllowMultipleSelection = false;

	OpenAssetDialogConfig.AssetClassNames.Add(
		UTODPresetData::StaticClass()->GetClassPathName());

	FContentBrowserModule& ContentBrowserModule =
		FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TArray<FAssetData> SelectedAssets =
		ContentBrowserModule.Get().CreateModalOpenAssetDialog(OpenAssetDialogConfig);

	if (SelectedAssets.Num() > 0)
	{
		UTODPresetData* SelectedPreset =
			Cast<UTODPresetData>(SelectedAssets[0].GetAsset());

		if (SelectedPreset)
		{
			Owner->LoadPreset = SelectedPreset;

			LoadSelectedPreset(Owner);

			Owner->BakeTODCurves();
			Owner->UpdateTOD(Owner->StartTime);
		}
	}
#endif
}

void FTODEditor::LoadSelectedPreset(ATODManager* Owner)
{
	if (!Owner || !Owner->LoadPreset) return;
	if (Owner->LoadPreset->TOD_DataArray.Num() == 0) return;

	Owner->TOD_DataArray = Owner->LoadPreset->TOD_DataArray;
	Owner->MarkPackageDirty();
}

void FTODEditor::ForceViewportRedraw(ATODManager* Owner)
{
#if WITH_EDITOR
	if (GEditor)
	{
		GEditor->RedrawLevelEditingViewports();
	}
#endif
}