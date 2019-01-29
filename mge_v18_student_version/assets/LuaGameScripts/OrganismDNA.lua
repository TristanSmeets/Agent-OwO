OrganismDNA = {}

function OrganismDNA:new()
    local organismDNA = {}
    setmetatable(organismDNA, self)
    self.__index = self
    organismDNA.SquareSize = 20
    organismDNA.IsAlive = false
    organismDNA.Colour = {r = math.random(), g = math.random(), b = math.random(), a = math.random()}
    return organismDNA
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
