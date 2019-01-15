BaseOrganism = {}

function BaseOrganism:new(organismDNA)
  local baseOrganism = {}
  setmetatable(baseOrganism, self)
  self.__index = self
  baseOrganism.OrganismDNA = organismDNA
  return baseOrganism
end

function BaseOrganism:Draw()
  if(self.OrganismDNA.IsAlive == true) then
    love.graphics.setColor(self.OrganismDNA.Colour.r,
      self.OrganismDNA.Colour.g,
      self.OrganismDNA.Colour.b,
      self.OrganismDNA.Colour.a)
  end
  love.graphics.rectangle("fill", self.OrganismDNA.x, self.OrganismDNA.y, self.OrganismDNA.SquareSize - 1, self.OrganismDNA.SquareSize - 1)
  love.graphics.setColor(0,0,0,1)
end

function BaseOrganism:SetDNAProperty(property, value)
  self.OrganismDNA.property = value
end
