class NoEatConfig
{
    private static const string FILE_PATH = "$profile:zombicide_mods\\NoEat\\AllowedItems.json";
    private ref array<string> AllowedHelmets;
    private int ConfigUpdateRate;

    void NoEatConfig()
    {
        // Constructor remains lightweight
    }

    bool Initialize()
    {
        if (!FileExist(FILE_PATH))
        {
            CreateDefaultConfig();
            Print("[NoEatConfig] Default config created.");
        }

        return LoadConfig();
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
            "MotoHelmet_Yellow"
        };

        ConfigUpdateRate = 10; // Default update rate

        ref map<string, ref array<string>> ConfigData = new map<string, ref array<string>>();
        ConfigData.Set("ConfigUpdateRate", {ConfigUpdateRate.ToString()});
        ConfigData.Set("AllowedHelmets", AllowedHelmets);

        JsonFileLoader<map<string, ref array<string>>>.JsonSaveFile(FILE_PATH, ConfigData);
    }
}
