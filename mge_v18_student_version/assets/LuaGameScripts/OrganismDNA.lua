OrganismDNA = {}

function OrganismDNA:new()
	local organismDNA = {}
	setmetatable(organismDNA, self)
	self.__index = self
	organismDNA.IsAlive = false
    organismDNA.Colour = {r = 1, g = 1, b = 1, a = 1}
	organismDNA.UnderPopulatedThresshold = 2
	organismDNA.OverPopulatedThresshold = 3
	organismDNA.Reproduction = 3
	return organismDNA
end

function OrganismDNA:newRandomColour()
    local randomDNA = {}
    setmetatable(randomDNA, self)
    self.__index = self
    randomDNA.IsAlive = false
    randomDNA.Colour = {r = math.random(), g = math.random(), b = math.random(), a = 1}
	randomDNA.UnderPopulatedThresshold = 2
	randomDNA.OverPopulatedThresshold = 3
	randomDNA.Reproduction = 3
    return randomDNA
end

function OrganismDNA:NewColoured(red, green, blue)
	local ColouredDNA = {}
	setmetatable(ColouredDNA, self)
	self.__index = self
	ColouredDNA.IsAlive = false
	ColouredDNA.Colour = {r = red, g = green, b = blue, a = 1}
	ColouredDNA.UnderPopulatedThresshold = 2
	ColouredDNA.OverPopulatedThresshold = 3
	ColouredDNA.Reproduction = 3
	return ColouredDNA
end

function OrganismDNA:NewPopulation(underPopulated, overPopulated, reproduction)
	local PopulatedDNA = {}
	setmetatable(PopulatedDNA, self)
	self.__index = self
	PopulatedDNA.IsAlive = false
	PopulatedDNA.Colour = {r = 1, g = 1, b = 1, a = 1}
	PopulatedDNA.UnderPopulatedThresshold = underPopulated
	PopulatedDNA.OverPopulatedThresshold = overPopulated
	PopulatedDNA.Reproduction = reproduction
	return PopulatedDNA
end