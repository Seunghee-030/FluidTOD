#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "LightBlockerActor.h" 
#include "LightBlockerManager.generated.h"

USTRUCT(BlueprintType)
struct FLightBlockerInstanceKey
{
    GENERATED_BODY()

    UPROPERTY()
    UStaticMesh* Mesh = nullptr;

    UPROPERTY()
    UMaterialInterface* Material = nullptr;

    bool operator==(const FLightBlockerInstanceKey& Other) const
    {
        return Mesh == Other.Mesh && Material == Other.Material;
    }

    friend uint32 GetTypeHash(const FLightBlockerInstanceKey& Key)
    {
        return HashCombine(GetTypeHash(Key.Mesh), GetTypeHash(Key.Material));
    }
};

UCLASS(Blueprintable)
class FLUID_TOD_API ALightBlockerManager : public AActor
{
    GENERATED_BODY()

public:
    ALightBlockerManager();

    UFUNCTION(BlueprintCallable, Category = "Light Blocker")
    void AddBlockerInstance(ELightBlockerShape Shape, ELightBlockerMaterialType MaterialType, UStaticMesh* CustomMesh, const FTransform& Transform);

    void AddBlockerInstances(ELightBlockerShape Shape, ELightBlockerMaterialType MaterialType, UStaticMesh* CustomMesh, const TArray<FTransform>& Transforms);

    UFUNCTION(BlueprintCallable, Category = "Light Blocker")
    void ClearAllInstances();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USceneComponent* RootComp;

    // 조합별 HISM 관리 맵
    UPROPERTY()
    TMap<FLightBlockerInstanceKey, UHierarchicalInstancedStaticMeshComponent*> HISMComponents;

    // 기본 메쉬
    UPROPERTY() UStaticMesh* DefaultCube;
    UPROPERTY() UStaticMesh* DefaultSphere;
    UPROPERTY() UStaticMesh* DefaultPlane;
    UPROPERTY() UStaticMesh* DefaultCylinder;

    // 마스터 머티리얼
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Materials", meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* MatteBlackMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Materials", meta = (AllowPrivateAccess = "true"))
    UMaterialInterface* MirrorMaterial;

    // 내부 헬퍼
    UStaticMesh* GetMeshFromShape(ELightBlockerShape Shape, UStaticMesh* CustomMesh) const;
    UMaterialInterface* GetMaterialFromType(ELightBlockerMaterialType MaterialType) const;

    UHierarchicalInstancedStaticMeshComponent* GetOrCreateHISMComponent(UStaticMesh* Mesh, UMaterialInterface* Material);
    void ApplyOptimizationToHISM(UHierarchicalInstancedStaticMeshComponent* HISMComp);
};