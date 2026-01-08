using UnrealBuildTool;

public class RTXNSUnreal : ModuleRules
{
    public RTXNSUnreal(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RHI",
                "RenderCore"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Projects"
            });

        PublicIncludePaths.AddRange(
            new string[]
            {
                "$(ModuleDir)/Public",
                "$(ProjectDir)/src/NeuralShading"
            });
    }
}
