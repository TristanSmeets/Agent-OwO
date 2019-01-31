GridChecker = {}

--Requires
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\BaseOrganism")
require("LuaGameScripts\\OrganismDNA")

--Local variables
local columns = nil
local rows = nil

--[[Loops over all the Organisms in the passed in grid.
    For each Organism it checks how many live neighbours it has.
    Checks if the Organism should be alive in the next generation and sets it's status.
    Returns a grid with updated values]]
function GridChecker:UpdateGrid(gameGrid, totalColumns, totalRows)
  columns = totalColumns
  rows = totalRows

  local UpdatedGrid = GridGenerator:Create2DGrid(columns, rows)

  for i, Row in pairs(UpdatedGrid) do
    for j, Column in pairs(Row) do

		local LiveNeighbours = numberAliveNeighbours(gameGrid, j, i)

		if checkIsAlive(LiveNeighbours,gameGrid[i][j].DNA) then
			local newDNA = CreateInheritedDNA(gameGrid, j, i)
			newDNA.IsAlive = true
			UpdatedGrid[i][j] = BaseOrganism:new(newDNA)
		else
			local deadDNA = OrganismDNA:NewColoured(0, 0, 0)
			UpdatedGrid[i][j] = BaseOrganism:new(deadDNA)
		end
    end
  end
  return UpdatedGrid
end

--[[Counts the amount of organisms that are alive.
    Returns the amount of live organisms.]]
local function numberAliveNeighbours(gameGrid, x, y)
  local Sum = 0
  for RowIndex = -1, 1 do
    for ColumnIndex = -1, 1 do
      local column = (x - 1 + ColumnIndex + columns) % columns
      local row = (y - 1 + RowIndex + rows) % rows
      if(column + 1) == x and (row + 1) == y then
      elseif gameGrid[row + 1][column + 1].DNA.IsAlive == true then
        Sum = Sum + 1
      end
    end
  end
  return Sum
end

--[[Checks if the amount of aliveNeighbours makes it viable to live.
    Returns true or false depending on if it should be alive]]
local function checkIsAlive(aliveNeighbours, DNA)
  if DNA.IsAlive then
    if (aliveNeighbours == DNA.UnderPopulatedThresshold or aliveNeighbours == DNA.OverPopulatedThresshold) then
      return true
    else
      return false
    end
  else
    if aliveNeighbours == DNA.Reproduction then
      return true
    end
  end
end

--[[Creates a new OrganismDNA that inherits values from surrounding alive Organisms
	Returns a the new OrganismDNA]]
function CreateInheritedDNA(Grid, x, y)
	local CreatedDNA = OrganismDNA:new()
	local DnaSamples = GetNeighboursDNA(Grid, x, y)
	
	local inheritedColour = { r = DnaSamples[math.random(#DnaSamples)].Colour.r, g = DnaSamples[math.random(#DnaSamples)].Colour.g, b = DnaSamples[math.random(#DnaSamples)].Colour.b}
	
	--Check if the new inherited colour isn't black. If it is black create a new random colour.
	if inheritedColour.r == 0 and inheritedColour.g == 0 and inheritedColour.b == 0 then
		inheritedColour.r = math.random()
		inheritedColour.g = math.random()
		inheritedColour.b = math.random()
	end

	local newUnderPop = DnaSamples[math.random(#DnaSamples)].UnderPopulatedThresshold
	local newOverPop = DnaSamples[math.random(#DnaSamples)].OverPopulatedThresshold
	local newRepro = DnaSamples[math.random(#DnaSamples)].Reproduction

	local averageColour = { r = inheritedColour.r, g = inheritedColour.g, b = inheritedColour.b, a = 1}
	CreatedDNA.Colour = averageColour
	CreatedDNA.UnderPopulatedThresshold = newUnderPop
	CreatedDNA.OverPopulatedThresshold = newOverPop
	CreatedDNA.Reproduction = newRepro

	return CreatedDNA
end

--[[Loops through the neighbours of the passed in position.
	Returns a table of OrganismDNA from all the neighbours that are alive.]]
function GetNeighboursDNA(grid, x, y)
	local NeighbourDNAs = {}
	for rowIndex = -1, 1 do
		for columnIndex = -1, 1 do
			local column = (x - 1 + columnIndex + columns) % columns
			local row = (y - 1 + rowIndex + rows) % rows
			if (column + 1) == x and (row + 1) == y then
			elseif grid[row + 1][column + 1].DNA.IsAlive == true then
				table.insert(NeighbourDNAs, grid[row + 1][column + 1].DNA)
			end
		end
	end
	return NeighbourDNAs
end
