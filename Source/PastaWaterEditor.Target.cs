// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PastaWaterEditorTarget : TargetRules
{
	public PastaWaterEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		ExtraModuleNames.AddRange( new string[] { "PastaWater" } );
	}
}
