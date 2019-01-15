OrganismDNA = {}

function OrganismDNA:new()
    local organismDNA = {}
    setmetatable(organismDNA, self)
    self.__index = self
    organismDNA.x = 0
    organismDNA.y = 0
    organismDNA.SquareSize = 20
    organismDNA.IsAlive = false
    organismDNA.Colour = {r = 1, g = 1, b = 1, a = 1}
    return organismDNA
end

function OrganismDNA:SetPosition(x,y)
  self.x = x
  self.y = y
end

function OrganismDNA:SetIsAlive(value)
  self.IsAlive = value
end

function OrganismDNA:SetColour(r,g,b,a)
  self.Colour.r = r
  self.Colour.g = g
  self.Colour.b = b
  self.Colour.a = a
end

function OrganismDNA:SetSquareSize(size)
  self.SquareSize = size
end
