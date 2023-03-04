// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownRpg : ModuleRules
{
	public TopDownRpg(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "UMG", "GameplayTasks"});
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags" });
    }
}
