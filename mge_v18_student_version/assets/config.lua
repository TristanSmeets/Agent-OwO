--Window properties
AspectRatio = 4/3
ForceAspectRatio = true
ScreenWidth = 800

--Screen Height
if(ForceAspectRatio) then
    ScreenHeight = math.floor( ScreenWidth / AspectRatio )
else
    ScreenHeight = 600
end

--Window Title
Title = "Lua Assignment"

--Assignment 2 paths
ModelToLoad = "mge/models/sphere2.obj"
TextureToLoad = "mge/textures/bricks.jpg"