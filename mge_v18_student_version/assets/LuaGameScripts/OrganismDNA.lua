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
	local randomDNA = OrganismDNA:new()
	setmetatable(randomDNA, self)
	self.__index = self
	randomDNA.Colour = { r = math.random(), g = math.random(), b = math.random(), a = 1}
	return randomDNA
end

function OrganismDNA:NewColoured(red, green, blue)
	local colouredDNA = OrganismDNA:new()
	setmetatable(colouredDNA, self)
	self.__index = self
	colouredDNA.Colour = {r = red, g = green, b = blue, a = 1}
	return colouredDNA
end

function OrganismDNA:NewPopulation(underPopulated, overPopulated, reproduction)
	local populateDNA = OrganismDNA:new()
	setmetatable(populateDNA, self)
	self.__index = self
	populateDNA.UnderPopulatedThresshold = underPopulated
	populateDNA.OverPopulatedThresshold = overPopulated
	populateDNA.Reproduction = reproduction
	return populateDNA
end
