// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PastaWater : ModuleRules
{
	public PastaWater(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "OnlineSubsystem", "UMG", "ApplicationCore"]);
		PrivateDependencyModuleNames.AddRange(["Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull", "OnlineSubsystemSteam", "MLAdapter", "OnlineServicesInterface"]);

		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = true;
	}
}
