OrganismDNA = {}

function OrganismDNA:base()
	local organismDNA = {}
	setmetatable(organismDNA, self)
	self.__index = self
	organismDNA.IsAlive = true
    organismDNA.Colour = {r = 1, g = 1, b = 1, a = 1}
	organismDNA.UnderPopulatedThresshold = 2
	organismDNA.OverPopulatedThresshold = 3
	organismDNA.Reproduction = 3
	return organismDNA
end

function OrganismDNA:NewColoured(red, green, blue)
	local colouredDNA = OrganismDNA:base()
	setmetatable(colouredDNA, self)
	self.__index = self
	colouredDNA.Colour = {r = red, g = green, b = blue, a = 1}
	return colouredDNA
end

function OrganismDNA:NewRandomColour()
	local randomDNA = OrganismDNA:NewColoured(math.random(), math.random(), math.random())
	setmetatable(randomDNA, self)
	self.__index = self
	return randomDNA
end


function OrganismDNA:NewPopulationThressholds(underPopulated, overPopulated, reproduction)
	local populateDNA = OrganismDNA:base()
	setmetatable(populateDNA, self)
	self.__index = self
	populateDNA.UnderPopulatedThresshold = underPopulated
	populateDNA.OverPopulatedThresshold = overPopulated
	populateDNA.Reproduction = reproduction
	return populateDNA
end
