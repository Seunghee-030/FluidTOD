#include "LightBlockerManager.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"

ALightBlockerManager::ALightBlockerManager()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(RootComp);

    // 엔진 기본 메쉬 에셋 로드
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("/Engine/BasicShapes/Plane.Plane"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));

    DefaultCube = CubeAsset.Succeeded() ? CubeAsset.Object : nullptr;
    DefaultSphere = SphereAsset.Succeeded() ? SphereAsset.Object : nullptr;
    DefaultPlane = PlaneAsset.Succeeded() ? PlaneAsset.Object : nullptr;
    DefaultCylinder = CylinderAsset.Succeeded() ? CylinderAsset.Object : nullptr;
}

void ALightBlockerManager::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

UStaticMesh* ALightBlockerManager::GetMeshFromShape(ELightBlockerShape Shape, UStaticMesh* CustomMesh) const
{
    switch (Shape)
    {
    case ELightBlockerShape::Cube:      return DefaultCube;
    case ELightBlockerShape::Sphere:    return DefaultSphere;
    case ELightBlockerShape::Plane:     return DefaultPlane;
    case ELightBlockerShape::Cylinder:  return DefaultCylinder;
    case ELightBlockerShape::Custom:    return CustomMesh;
    default:                            return nullptr;
    }
}

UMaterialInterface* ALightBlockerManager::GetMaterialFromType(ELightBlockerMaterialType MaterialType) const
{
    return (MaterialType == ELightBlockerMaterialType::MatteBlack) ? MatteBlackMaterial : MirrorMaterial;
}

UHierarchicalInstancedStaticMeshComponent* ALightBlockerManager::GetOrCreateHISMComponent(UStaticMesh* Mesh, UMaterialInterface* Material)
{
    if (!Mesh) return nullptr;

    FLightBlockerInstanceKey Key;
    Key.Mesh = Mesh;
    Key.Material = Material;

    if (HISMComponents.Contains(Key))
    {
        return HISMComponents[Key];
    }

    UHierarchicalInstancedStaticMeshComponent* NewHISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
    if (NewHISM)
    {
        NewHISM->SetupAttachment(RootComp);
        NewHISM->SetStaticMesh(Mesh);
        if (Material)
        {
            NewHISM->SetMaterial(0, Material);
        }

        NewHISM->RegisterComponent();
        ApplyOptimizationToHISM(NewHISM);

        HISMComponents.Add(Key, NewHISM);
    }

    return NewHISM;
}

void ALightBlockerManager::ApplyOptimizationToHISM(UHierarchicalInstancedStaticMeshComponent* HISMComp)
{
    if (!HISMComp) return;

    HISMComp->SetHiddenInGame(true);
    HISMComp->SetRenderInMainPass(false);
    HISMComp->SetRenderCustomDepth(false);
    HISMComp->SetReceivesDecals(false);

    HISMComp->SetCastShadow(true);
    HISMComp->bCastHiddenShadow = true;
    HISMComp->bCastDynamicShadow = true;
    HISMComp->bAffectDistanceFieldLighting = false;

    HISMComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    HISMComp->SetGenerateOverlapEvents(false);
    HISMComp->CanCharacterStepUpOn = ECB_No;

    HISMComp->SetCanEverAffectNavigation(false);
    HISMComp->SetMobility(EComponentMobility::Static);

    HISMComp->InstanceStartCullDistance = 10000.0f;
    HISMComp->InstanceEndCullDistance = 15000.0f;
}

void ALightBlockerManager::AddBlockerInstance(ELightBlockerShape Shape, ELightBlockerMaterialType MaterialType, UStaticMesh* CustomMesh, const FTransform& Transform)
{
    UStaticMesh* TargetMesh = GetMeshFromShape(Shape, CustomMesh);
    UMaterialInterface* TargetMat = GetMaterialFromType(MaterialType);

    if (UHierarchicalInstancedStaticMeshComponent* HISMComp = GetOrCreateHISMComponent(TargetMesh, TargetMat))
    {
        HISMComp->AddInstance(Transform);
    }
}

void ALightBlockerManager::AddBlockerInstances(ELightBlockerShape Shape, ELightBlockerMaterialType MaterialType, UStaticMesh* CustomMesh, const TArray<FTransform>& Transforms)
{
    UStaticMesh* TargetMesh = GetMeshFromShape(Shape, CustomMesh);
    UMaterialInterface* TargetMat = GetMaterialFromType(MaterialType);

    if (UHierarchicalInstancedStaticMeshComponent* HISMComp = GetOrCreateHISMComponent(TargetMesh, TargetMat))
    {
        HISMComp->AddInstances(Transforms, false);
    }
}

void ALightBlockerManager::ClearAllInstances()
{
    for (auto& Pair : HISMComponents)
    {
        if (Pair.Value)
        {
            Pair.Value->ClearInstances();
        }
    }
}

void ALightBlockerManager::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundBlockers;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        ALightBlockerActor::StaticClass(),
        FoundBlockers);

    for (AActor* Actor : FoundBlockers)
    {
        ALightBlockerActor* Blocker = Cast<ALightBlockerActor>(Actor);
        if (Blocker)
        {
            AddBlockerInstance(
                Blocker->GetBlockerShape(),
                Blocker->GetMaterialType(),
                Blocker->GetCustomMesh(),
                Blocker->GetActorTransform());

            Blocker->Destroy();
        }
    }
}