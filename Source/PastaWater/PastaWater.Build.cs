// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PastaWater : ModuleRules
{
	public PastaWater(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystem", "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull", "OnlineSubsystemSteam", "MLAdapter" });

		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = true;
	}
}
