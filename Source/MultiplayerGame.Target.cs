// Multiplayer Game

using UnrealBuildTool;
using System.Collections.Generic;

public class MultiplayerGameTarget : TargetRules
{
	public MultiplayerGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;

		ExtraModuleNames.AddRange( new string[] { "MultiplayerGame" } );
	}
}
