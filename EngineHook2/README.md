# EngineHook2

This project adds some hooks to run functions from the Hitman 2015 Alpha code.

*Note: This project is a work in progress. It is a tool simplify experimenting with the Alpha code with the goal of understanding how to generate the reasoning grid, and learn more about how the Alpha code works. It currently does not successfully generate a reasoning grid, it just calls the GenerateGrid function. More research will need to be done to know how to set the needed parameters and variables.*

## Usage and Debugging
1. Open the solution in Visual Studio.
1. Build this lib and put it in the Hitman Alpha folder.
1. Open the Solution Explorer
1. In the EngineHook2 Project settings, on the debugging tab, set the Command to the Hitman IO engine exe, (e.g. D:\HitmanAlpha\Hitman IO\engine.exe) and the Working Directory to the Hitman IO folder (e.g. D:\HitmanAlpha\Hitman IO\)
1. Set the SCENE_FILE in the engine.ini to a scene (for instance "SCENE_FILE=assembly:/_PRO/Scenes/Missions/Bangkok/_Scene_Mission_Tiger.entity")
1. Put a breakpoint where you'd like, for instance in the FastCall function
1. Click the Play button for Local Windows Debugger
1. Press F3 to run the hook.
1. Press Step Into until it hits the library code
1. When it asks for the source code file, click cancel
1. When it says Source Not Found, in the Options, under View Dissassembly, click View

## License info
Uses and modifies code from https://github.com/OrfeasZ/ZHMTools

## Credits:
* Orfeaz aka NoFaTe - ZHMTools & ResourceLib & NavWeakness lib - https://github.com/OrfeasZ
* Anthony Fuller - NavWeakness lib - https://github.com/AnthonyFuller
* Pavle - Hook projects - https://github.com/pavledev
* Notex - ResourceLib - https://github.com/Notexe
* IOI - https://ioi.dk/