class NoEatConfig
{
    private static const string FILE_PATH = "$profile:zombicide_mods\\NoEat\\AllowedItems.json";
    private ref array<string> AllowedHelmets;
    private int ConfigUpdateRate;

    void NoEatConfig()
{
    if (!FileExist(FILE_PATH))
    {
        CreateDefaultConfig();
        Print("[NoEatConfig] Default config created.");
    }

    if (!LoadConfig())
    {
        Print("[NoEatConfig] ERROR: Failed to load config even after creation!");
        return;
    }

    Print("[NoEatConfig] Loaded Config:");
    Print(GenerateConfigJson());

    StartPeriodicUpdate();
}


    private bool LoadConfig()
    {
        if (FileExist(FILE_PATH))
        {
            ref map<string, ref array<string>> ConfigData;
            JsonFileLoader<map<string, ref array<string>>>.JsonLoadFile(FILE_PATH, ConfigData);
            
            AllowedHelmets = ConfigData.Get("AllowedHelmets");
            ConfigUpdateRate = ConfigData.Get("ConfigUpdateRate").Get(0).ToInt();

            return true;
        }
        return false;
    }

    private void CreateDefaultConfig()
    {
        AllowedHelmets = {
            "DarkMotoHelmet_Black",
            "DarkMotoHelmet_Blue",
            "DarkMotoHelmet_Green",
            "DarkMotoHelmet_Grey",
            "DarkMotoHelmet_Lime",    
            "DarkMotoHelmet_Red",
            "DarkMotoHelmet_White",
            "DarkMotoHelmet_Yellow",
            "MotoHelmet_Black",
            "MotoHelmet_Blue",
            "MotoHelmet_Green",
            "MotoHelmet_Grey",
            "MotoHelmet_Lime",
            "MotoHelmet_Red",
            "MotoHelmet_White",
            "MotoHelmet_Yellow"
        };

        ConfigUpdateRate = 10; // Default update rate (seconds)

        ref map<string, ref array<string>> ConfigData = new map<string, ref array<string>>();
        ConfigData.Set("ConfigUpdateRate", {ConfigUpdateRate.ToString()});
        ConfigData.Set("AllowedHelmets", AllowedHelmets);

        JsonFileLoader<map<string, ref array<string>>>.JsonSaveFile(FILE_PATH, ConfigData);
    }

    void StartPeriodicUpdate()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ReloadConfig, ConfigUpdateRate * 1000, true);
        Print("[NoEatConfig] Scheduled config reload every " + ConfigUpdateRate.ToString() + " seconds.");
    }

    void ReloadConfig()
	{
		int oldRate = ConfigUpdateRate;

		if (LoadConfig())
		{
			Print("[NoEatConfig] Config successfully reloaded.");

			if (ConfigUpdateRate != oldRate)
			{
				Print("[NoEatConfig] ConfigUpdateRate changed. Restarting update schedule...");

				// Stop and reschedule
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.ReloadConfig);
				StartPeriodicUpdate(); // Reschedule with the new rate
			}
		}
		else
		{
			Print("[NoEatConfig] Failed to reload config, file missing?");
		}
	}


    bool IsHelmetBlocked(ItemBase hg)
    {
        foreach (string helmet : AllowedHelmets)
        {
            if (hg.IsKindOf(helmet))
                return true;
        }
        return false;
    }

  string GenerateConfigJson()
{
    StringBuilder output = new StringBuilder();
    output.Append("{ \"ConfigUpdateRate\": ").Append(ConfigUpdateRate.ToString()).Append(", \"AllowedHelmets\": [");

    for (int i = 0; i < AllowedHelmets.Count(); i++)
    {
        output.Append("\"").Append(AllowedHelmets.Get(i)).Append("\"");
        if (i < AllowedHelmets.Count() - 1)
        {
            output.Append(", ");
        }
    }

    output.Append("] }");
    return output.ToString();
}

}
