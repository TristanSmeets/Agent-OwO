BaseOrganism = {}

function BaseOrganism:new(organismDNA)
  local baseOrganism = {}
  setmetatable(baseOrganism, self)
  self.__index = self
  baseOrganism.DNA = organismDNA
  return baseOrganism
end

function BaseOrganism:Draw(drawRectangle)
	drawRectangle:SetColour(
		self.DNA.Colour.r,
		self.DNA.Colour.g,
		self.DNA.Colour.b,
		self.DNA.Colour.a
	)
end