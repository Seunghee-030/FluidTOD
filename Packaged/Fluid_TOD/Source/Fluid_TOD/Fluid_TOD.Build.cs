// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fluid_TOD : ModuleRules
{
    public Fluid_TOD(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        // LevelSequence / MovieScene 은 .cpp 에서만 사용된다.
        // Public 에 두면 이 모듈에 의존하는 모든 모듈이 불필요하게 링크하게 된다.
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "LevelSequence",
                "MovieScene"
            }
            );

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd",
                    "AssetTools",
                    "ContentBrowser",
                    "ToolMenus",
                    "UMG",
                    "UMGEditor",
                    "Blutility"
                }
            );
        }

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}