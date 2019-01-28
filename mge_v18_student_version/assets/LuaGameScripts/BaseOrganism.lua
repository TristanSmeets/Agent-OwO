BaseOrganism = {}

function BaseOrganism:new(x, y, squareSize, organismDNA)
  local baseOrganism = {}
  setmetatable(baseOrganism, self)
  self.__index = self
  baseOrganism.x = x
  baseOrganism.y = y
  baseOrganism.squareSize = squareSize
  baseOrganism.DNA = organismDNA
  return baseOrganism
end

function BaseOrganism:Draw(drawRectangle)
	if self.DNA.IsAlive == true then
		drawRectangle:SetColour(
			self.DNA.Colour.r, 
			self.DNA.Colour.g,
			self.DNA.Colour.b,
			self.DNA.Colour.a)
	else
		drawRectangle:SetColour(0,0,0,1)
	end
end