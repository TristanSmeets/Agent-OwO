GameObject = {}

function GameObject:new()
    local gameObject = {}
    setmetatable(gameObject, self)
    self.__index = self
    gameObject.Position = { x = 0, y = 0, z = 0 }
    gameObject.Rotation = { x = 0, y = 0, z = 0, w = 0 }
    gameObject.Scale = { x = 0, y = 0, z = 0 }
    gameObject.Type = TILE
    return gameObject
end
