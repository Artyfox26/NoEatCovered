class CfgPatches
{
	class NoEatCovered
	{
		units[]=
		{
			""
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class NoEatCovered
	{
		
		author="Artyfox";
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"NoEatCovered/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"NoEatCovered/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"NoEatCovered/Scripts/5_Mission"
				};
			};
		};
	};
};
