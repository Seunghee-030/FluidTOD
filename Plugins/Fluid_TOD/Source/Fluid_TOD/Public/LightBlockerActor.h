#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightBlockerActor.generated.h"

// 선택 가능한 StaticMesh 형태
UENUM(BlueprintType)
enum class ELightBlockerShape : uint8
{
    Cube        UMETA(DisplayName = "Cube"),
    Sphere      UMETA(DisplayName = "Sphere"),
    Plane       UMETA(DisplayName = "Plane"),
    Cylinder    UMETA(DisplayName = "Cylinder"),
    Custom      UMETA(DisplayName = "Custom Mesh")
};

UENUM(BlueprintType)
enum class ELightBlockerMaterialType : uint8
{
    MatteBlack  UMETA(DisplayName = "Matte Black (Absorb Light)"),
    Mirror      UMETA(DisplayName = "Mirror (Reflect Light)")
};

UCLASS(Blueprintable, hidecategories = (Input, Actor, LOD, Cooking, Replication))
class FLUID_TOD_API ALightBlockerActor : public AActor
{
    GENERATED_BODY()

public:
    ALightBlockerActor();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
    UPROPERTY()
    USceneComponent* RootComp;

    UPROPERTY()
    UStaticMeshComponent* BlockerMesh;

    // --- Shape Settings ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Settings", meta = (AllowPrivateAccess = "true"))
    ELightBlockerShape BlockerShape;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Settings", meta = (EditCondition = "BlockerShape == ELightBlockerShape::Custom", AllowPrivateAccess = "true"))
    class UStaticMesh* CustomMesh;

    // --- Material Settings ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Settings", meta = (AllowPrivateAccess = "true"))
    ELightBlockerMaterialType MaterialType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Materials", meta = (AllowPrivateAccess = "true"))
    class UMaterialInterface* MatteBlackMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Materials", meta = (AllowPrivateAccess = "true"))
    class UMaterialInterface* MirrorMaterial;

    // --- Default Meshes ---
    class UStaticMesh* DefaultCube;
    class UStaticMesh* DefaultSphere;
    class UStaticMesh* DefaultPlane;
    class UStaticMesh* DefaultCylinder;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Channels", meta = (AllowPrivateAccess = "true"))
    bool bBlockChannel0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Channels", meta = (AllowPrivateAccess = "true"))
    bool bBlockChannel1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Blocker|Channels", meta = (AllowPrivateAccess = "true"))
    bool bBlockChannel2;

    void UpdateMeshShape();
    void ApplyOptimizationSettings();
    void UpdateMaterial();
    void UpdateLightingChannels();
};