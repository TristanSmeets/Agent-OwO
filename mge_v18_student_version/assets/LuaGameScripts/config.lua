--Window properties
AspectRatio = 16/9
ForceAspectRatio = true
ScreenWidth = 1280

--Screen Height
if(ForceAspectRatio) then
    ScreenHeight = math.floor( ScreenWidth / AspectRatio )
else
    ScreenHeight = 600
end

--Window Title
Title = "Pjauna Gryba uwu"

--Cpp project lua file paths
Tile = "LuaGameScripts/Tile.lua"
Player = "LuaGameScripts/Player.lua"
Exit = "LuaGameScripts/Exit.lua"
Box = "LuaGameScripts/Box.lua"
Switch = "LuaGameScripts/Switch.lua"

LevelToLoad = "LuaGameScripts/TestLevel.lua"
