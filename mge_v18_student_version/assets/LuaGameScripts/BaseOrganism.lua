BaseOrganism = {}

function BaseOrganism:new(x, y, squareSize, organismDNA)
  local baseOrganism = {}
  setmetatable(baseOrganism, self)
  self.__index = self
  baseOrganism.x = x
  baseOrganism.y = y
  baseOrganism.squareSize = squareSize
  baseOrganism.DNA = organismDNA
  --print(DrawRectangle)
  --baseOrganism.rectangle = DrawRectangle.New(x,y, squareSize, organismDNA.Colour);
  return baseOrganism
end

function BaseOrganism:Draw()
  if(self.DNA.IsAlive == true) then
    love.graphics.setColor(self.DNA.Colour.r,
      self.DNA.Colour.g,
      self.DNA.Colour.b,
      self.DNA.Colour.a)
  end
  love.graphics.rectangle("fill", self.x, self.y, self.squareSize - 1, self.squareSize - 1)
  love.graphics.setColor(0,0,0,1)
end
