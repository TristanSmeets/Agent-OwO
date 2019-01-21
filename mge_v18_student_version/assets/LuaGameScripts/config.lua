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

--Assignment 4 paths
ObjToLoad = "mge/models/plane_8192.obj"
diffuse1 = "mge/textures/diffuse1.jpg"
diffuse2 = "mge/textures/water.jpg"
diffuse3 = "mge/textures/diffuse3.jpg"
diffuse4 = "mge/textures/diffuse4.jpg"
heightMap = "mge/textures/heightmap.png"
splatMap = "mge/textures/splatmap.png"

--SquareSize
SquareSize = 10