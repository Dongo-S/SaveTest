// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SaveTest : ModuleRules
{
	public SaveTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDefinitions.Add("platform_1=0");
        PublicDefinitions.Add("platform_2=1");
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Json", "JsonUtilities", "zlib", "ZipPlatformFile" });

	}
}
