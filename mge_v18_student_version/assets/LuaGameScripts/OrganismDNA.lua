OrganismDNA = {}

function OrganismDNA:new()
    local organismDNA = {}
    setmetatable(organismDNA, self)
    self.__index = self
    organismDNA.IsAlive = false
    organismDNA.Colour = {r = math.random(), g = math.random(), b = math.random(), a = 1}
    return organismDNA
end

function OrganismDNA:New(red, green, blue)
	local DNA = {}
	setmetatable(DNA, self)
	self.__index = self
	DNA.IsAlive = false
	DNA.Colour = {r = red, g = green, b = blue, a = 1}
	return DNA
end