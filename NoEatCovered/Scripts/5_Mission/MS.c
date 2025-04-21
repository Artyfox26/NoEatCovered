modded class MissionServer
{
    private static ref NoEatConfig Config;

    void MissionServer()
    {
        Print("�-    NoEatCovered MOD LOADED   -�");

        // Initialize and check NoEatConfig
        Config = new NoEatConfig();
        if (Config.Initialize())
        {
            Print("[MissionServer] NoEatConfig successfully loaded and initialized.");
        }
        else
        {
            Print("[MissionServer] Failed to initialize NoEatConfig. Default config created.");
        }
    }

    static ref NoEatConfig GetConfig()
    {
        return Config;
    }
}
