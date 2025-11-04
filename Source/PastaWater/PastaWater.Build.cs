// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PastaWater : ModuleRules
{
	public PastaWater(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new []
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"UMG",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});

		PrivateDependencyModuleNames.AddRange(new []
		{
			"ApplicationCore",    // For Clipboard / FGenericPlatformApplicationMisc
			"OnlineSubsystemSteam",
		});
		
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = true;
	}
}
