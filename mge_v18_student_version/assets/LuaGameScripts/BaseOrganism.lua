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
  if(self.DNA.IsAlive == true) then
	drawRectangle:SetColour(self.DNA.Colour)
  else
	drawRectangle:SetColour({r = 0, g = 0, b = 0, a = 1})
  end
end