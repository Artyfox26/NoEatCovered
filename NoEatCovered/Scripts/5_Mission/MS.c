modded class MissionServer
{
    private static ref NoEatConfig Config;

    void MissionServer()
    {
        Print("•-    NoEatCovered MOD LOADED   -•");

        // Initialize the NoEatConfig instance
        Config = new NoEatConfig();
        Print("[NoEatConfig] Initialized on server startup.");
    }
}