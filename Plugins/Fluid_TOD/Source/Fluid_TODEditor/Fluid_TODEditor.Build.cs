using UnrealBuildTool;

public class Fluid_TODEditor : ModuleRules
{
    public Fluid_TODEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "UnrealEd",
            "Fluid_TOD"
        });
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",

            // UI
            "Slate",
            "SlateCore",

            // Editor
            "ContentBrowser",
            "EditorSubsystem",
            "AssetTools",
            "AssetRegistry",
        });
    }
}