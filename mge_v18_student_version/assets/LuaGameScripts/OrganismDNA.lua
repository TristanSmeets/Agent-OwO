OrganismDNA = {}

function OrganismDNA:new()
    local organismDNA = {}
    setmetatable(organismDNA, self)
    self.__index = self
    organismDNA.IsAlive = false
    organismDNA.Colour = {r = math.random(), g = math.random(), b = math.random(), a = math.random()}
    return organismDNA
end

function OrganismDNA:SetIsAlive(value)
  self.IsAlive = value
end

function OrganismDNA:SetColour(red, green, blue, alpha)
  local newColour = { r = red, g = green, b = blue, a = alpha}
  self.Colour = newColour
end
