--Mesh
ModelPath = "mge/models/cube_flat.obj"		--Path to the model here

--Lighting
LightType = 0								--0 = Directional, 1 = Point, 2 = Spotlight
--Light Colour
Ambient = {red = 1, green = 1, blue = 1}	--The colour of the ambient light. (Uses rgb 0-1 values)
Diffuse = {red = 1, green = 1, blue = 1}	--The colour of the diffuse light. (Uses rgb 0-1 values)
Specular = {red = 1, green = 1, blue = 1}	--The colour of the specular light. (Uses rgb 0-1 values)
--Light Attentuation
Constant = 1.0								--The constant fall off. (Should probably always be 1)
Linear = 0.14								--The linear fall off.
Quadratic = 0.07							--The quadratic fall off.
--Spotlight specific
CutOff = 12.5								--Size of the inner cone.
OuterCutOff = 15.5							--Size of the outer cone.

--Material
DiffuseTexture = "mge/textures/container2.png"				--Path to the diffuse texture.
SpecularTexture = "mge/textures/container2_specular.png"	--Path to the specular texture. (not sure if working correctly atm)
ShininessFactor = 32										--How shiny the material is. (Use a power of 2)

--Camera
CameraDistance = 5
CameraMoveSpeed = 0.5