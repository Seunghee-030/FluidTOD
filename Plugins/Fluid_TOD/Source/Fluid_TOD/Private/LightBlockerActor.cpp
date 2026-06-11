#include "LightBlockerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/CollisionProfile.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"

ALightBlockerActor::ALightBlockerActor()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComp->SetMobility(EComponentMobility::Static);
    SetRootComponent(RootComp);

    BlockerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockerMesh"));
    BlockerMesh->SetupAttachment(RootComp);

    // 기본 메쉬 로드
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("/Engine/BasicShapes/Plane.Plane"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    DefaultCube = CubeAsset.Succeeded() ? CubeAsset.Object : nullptr;
    DefaultSphere = SphereAsset.Succeeded() ? SphereAsset.Object : nullptr;
    DefaultPlane = PlaneAsset.Succeeded() ? PlaneAsset.Object : nullptr;
    DefaultCylinder = CylinderAsset.Succeeded() ? CylinderAsset.Object : nullptr;

    BlockerShape = ELightBlockerShape::Plane;
    CustomMesh = nullptr;

    MaterialType = ELightBlockerMaterialType::MatteBlack;

    bBlockChannel0 = false;
    bBlockChannel1 = true;
    bBlockChannel2 = false;

    ApplyOptimizationSettings();
}

void ALightBlockerActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    UpdateMeshShape();
    UpdateMaterial();
    UpdateLightingChannels();
}

#if WITH_EDITOR
void ALightBlockerActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, BlockerShape) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, CustomMesh))
    {
        UpdateMeshShape();
    }

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, MaterialType) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, MatteBlackMaterial) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, MirrorMaterial))
    {
        UpdateMaterial();
    }
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, bBlockChannel0) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, bBlockChannel1) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ALightBlockerActor, bBlockChannel2))
    {
        UpdateLightingChannels();
    }
}
#endif

void ALightBlockerActor::UpdateLightingChannels()
{
    if (!BlockerMesh) return;

    BlockerMesh->LightingChannels.bChannel0 = bBlockChannel0;
    BlockerMesh->LightingChannels.bChannel1 = bBlockChannel1;
    BlockerMesh->LightingChannels.bChannel2 = bBlockChannel2;
}

void ALightBlockerActor::UpdateMeshShape()
{
    if (!BlockerMesh) return;

    UStaticMesh* MeshToUse = nullptr;

    switch (BlockerShape)
    {
    case ELightBlockerShape::Cube:      MeshToUse = DefaultCube; break;
    case ELightBlockerShape::Sphere:    MeshToUse = DefaultSphere; break;
    case ELightBlockerShape::Plane:     MeshToUse = DefaultPlane; break;
    case ELightBlockerShape::Cylinder:  MeshToUse = DefaultCylinder; break;
    case ELightBlockerShape::Custom:    MeshToUse = CustomMesh; break;
    }

    if (BlockerMesh->GetStaticMesh() != MeshToUse)
    {
        BlockerMesh->SetStaticMesh(MeshToUse);
        UpdateMaterial();
    }
}

void ALightBlockerActor::UpdateMaterial()
{
    if (!BlockerMesh) return;

    UMaterialInterface* MatToUse = nullptr;

    if (MaterialType == ELightBlockerMaterialType::MatteBlack)
    {
        MatToUse = MatteBlackMaterial;
    }
    else if (MaterialType == ELightBlockerMaterialType::Mirror)
    {
        MatToUse = MirrorMaterial;
    }

    if (MatToUse)
    {
        int32 NumMaterials = BlockerMesh->GetNumMaterials();
        for (int32 i = 0; i < NumMaterials; ++i)
        {
            BlockerMesh->SetMaterial(i, MatToUse);
        }
    }
}

void ALightBlockerActor::ApplyOptimizationSettings()
{
    if (!BlockerMesh) return;

    // Rendering
    BlockerMesh->SetHiddenInGame(true);
    BlockerMesh->SetRenderInMainPass(false);
    BlockerMesh->SetRenderCustomDepth(false);
    BlockerMesh->SetReceivesDecals(false);

    // Shadow / Light Blocking
    BlockerMesh->SetCastShadow(true);
    BlockerMesh->bCastHiddenShadow = true;
    BlockerMesh->bCastDynamicShadow = true;
    BlockerMesh->bAffectDistanceFieldLighting = false;

    // Collision
    BlockerMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    BlockerMesh->SetGenerateOverlapEvents(false);
    BlockerMesh->CanCharacterStepUpOn = ECB_No;

    // Navigation
    BlockerMesh->SetCanEverAffectNavigation(false);

    // Performance
    BlockerMesh->SetMobility(EComponentMobility::Static);
}