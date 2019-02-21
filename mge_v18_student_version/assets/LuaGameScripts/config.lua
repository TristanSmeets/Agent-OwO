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
Box = "LuaGameScripts/Box.lua"
Exit = "LuaGameScripts/Exit.lua"
Player = "LuaGameScripts/Player.lua"
Start = "LuaGameScripts/Start.lua"
Switch = "LuaGameScripts/Switch.lua"
Tile = "LuaGameScripts/Tile.lua"

LevelToLoad = 4
