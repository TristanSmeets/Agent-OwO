require('LuaGameScripts\\GameObject')

GameObjects = {}
local newGameObject0 = GameObject:new()
newGameObject0.Position = { x = 0, y = 0, z = 6.3 }
newGameObject0.Rotation = { x = -0.2302404, y = 0.160571, z = 0.03854968, w = 0.9590205 }
newGameObject0.Scale = { x = 1, y = 1, z = 1 }
newGameObject0.Type = 'SWITCH'
table.insert(GameObjects, newGameObject0)

local newGameObject1 = GameObject:new()
newGameObject1.Position = { x = 0, y = 0, z = 0 }
newGameObject1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newGameObject1.Scale = { x = 1, y = 1, z = 1 }
newGameObject1.Type = 'TILE'
table.insert(GameObjects, newGameObject1)

local newGameObject2 = GameObject:new()
newGameObject2.Position = { x = 0, y = 0, z = 2.43 }
newGameObject2.Rotation = { x = 0, y = -0.3826834, z = 0, w = 0.9238796 }
newGameObject2.Scale = { x = 1, y = 1, z = 1 }
newGameObject2.Type = 'BOX'
table.insert(GameObjects, newGameObject2)

local newGameObject3 = GameObject:new()
newGameObject3.Position = { x = -2.32, y = 0.04, z = 4.43 }
newGameObject3.Rotation = { x = 0, y = 0.1495353, z = 0, w = 0.9887564 }
newGameObject3.Scale = { x = 1, y = 1, z = 1 }
newGameObject3.Type = 'PLAYER'
table.insert(GameObjects, newGameObject3)

local newGameObject4 = GameObject:new()
newGameObject4.Position = { x = 0, y = 4.63, z = -2.78 }
newGameObject4.Rotation = { x = -0.8191521, y = 0, z = 0, w = -0.5735764 }
newGameObject4.Scale = { x = 1, y = 1, z = 1 }
newGameObject4.Type = 'TILE'
table.insert(GameObjects, newGameObject4)

local newGameObject5 = GameObject:new()
newGameObject5.Position = { x = 2.07, y = 0, z = 3.3 }
newGameObject5.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newGameObject5.Scale = { x = 1, y = 1, z = 1 }
newGameObject5.Type = 'TILE'
table.insert(GameObjects, newGameObject5)

local newGameObject6 = GameObject:new()
newGameObject6.Position = { x = -2.09, y = 0, z = 1.92 }
newGameObject6.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newGameObject6.Scale = { x = 1, y = 1, z = 1 }
newGameObject6.Type = 'TILE'
table.insert(GameObjects, newGameObject6)

local newGameObject7 = GameObject:new()
newGameObject7.Position = { x = 0, y = 5, z = -1.88 }
newGameObject7.Rotation = { x = 0.3826834, y = 0, z = 0, w = 0.9238796 }
newGameObject7.Scale = { x = 1, y = 1, z = 1 }
newGameObject7.Type = 'CAMERA'
table.insert(GameObjects, newGameObject7)

