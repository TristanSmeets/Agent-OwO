BaseOrganism = {}
BaseOrganism.__index = BaseOrganism

function BaseOrganism:new(isAlive)
  local baseOrganism = {}
  setmetatable(baseOrganism, BaseOrganism)
  baseOrganism.isAlive = (isAlive or false)
  return baseOrganism
end

function BaseOrganism:GetIsAlive()
  return self.isAlive
end

function BaseOrganism:SetIsAlive(value)
  self.isAlive = value
end