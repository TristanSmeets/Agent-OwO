--Lua File with specific info for each level.

Levels = 6

--Table with the amount of steps per level.
AmountOfSteps = {
    Level_1 = -1,
    Level_2 = -1,
    Level_3 = 12,
    Level_4 = 43,
    Level_5 = 74,
    Level_6 = 85
}

--Table with the amount of switches in each level.
Switches = {
	Level_1 = 0,
	Level_2 = 1,
	Level_3 = 1,
	Level_4 = 1,
	Level_5 = 2,
	Level_6 = 3 }

--Table with background props
BackgroundMesh = {
    Level_1 = "mge/models/LVL2.obj",
    Level_2 = "mge/models/LVL2.obj",
    Level_3 = "mge/models/LVL2.obj",
    Level_4 = "mge/models/LVL2.obj",
    Level_5 = "mge/models/LVL2.obj",
    Level_6 = "mge/models/LVL2.obj"
}

BackgroundTexture = {
    Level_1 = "mge/textures/Level_2_BG.png",
    Level_2 = "mge/textures/Level_2_BG.png",
    Level_3 = "mge/textures/Level_2_BG.png",
    Level_4 = "mge/textures/Level_2_BG.png",
    Level_5 = "mge/textures/Level_2_BG.png",
    Level_6 = "mge/textures/Level_2_BG.png",
}

SkyBoxMesh = "mge/models/BG.obj"

SkyBoxTexture = {
	Level_1 = "mge/textures/Box.png",
	Level_2 = "mge/textures/Exit.png",
	Level_3 = "mge/textures/GenTile-Darker.png",
	Level_4 = "mge/textures/Player.png",
	Level_5 = "mge/textures/Start.png",
	Level_6 = "mge/textures/Level_2_BG.png"
}