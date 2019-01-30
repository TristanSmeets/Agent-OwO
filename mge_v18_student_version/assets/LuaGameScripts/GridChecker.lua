GridChecker = {}

--Requires
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\BaseOrganism")
require("LuaGameScripts\\OrganismDNA")

--Local variables
local columns = nil
local rows = nil

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


--[[Loops over all the Organisms in the passed in grid.
    For each Organism it checks how many live neighbours it has.
    Checks if the Organism should be alive in the next generation and sets it's status.
    Returns the grid with updated values]]
function GridChecker:UpdateGrid(gameGrid, totalColumns, totalRows)
  columns = totalColumns
  rows = totalRows

  local UpdatedGrid = GridGenerator:Create2DGrid(columns, rows)

  for i, Row in pairs(UpdatedGrid) do
    for j, Column in pairs(Row) do

		local LiveNeighbours = numberAliveNeighbours(gameGrid, j, i)

		if checkIsAlive(LiveNeighbours,gameGrid[i][j].DNA) then
			local newDNA = CreateNewDna(gameGrid, j, i)
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

function CreateNewDna(Grid, x, y)
	local CreatedDNA = OrganismDNA:new()
	local livingNeighbours = 0
	local newColour = {maxRed = 0, maxGreen = 0, maxBlue = 0}

	local DnaSamples = {}

	for rowIndex = -1, 1 do
		for columnIndex = -1, 1 do
			local column = (x - 1 + columnIndex + columns) % columns
			local row = (y - 1 + rowIndex + rows) % rows
			if (column + 1) == x and (row + 1) == y then
			elseif Grid[row + 1][column + 1].DNA.IsAlive == true then
				table.insert(DnaSamples, Grid[row + 1][column + 1].DNA)
			end
		end
	end

	local newColour = { r = DnaSamples[math.random(#DnaSamples)].Colour.r, g = DnaSamples[math.random(#DnaSamples)].Colour.g, b = DnaSamples[math.random(#DnaSamples)].Colour.b}
	if newColour.r == 0 and newColour.g == 0 and newColour.b == 0 then
		newColour.r = math.random()
		newColour.g = math.random()
		newColour.b = math.random()
	end

	local newUnderPop = DnaSamples[math.random(#DnaSamples)].UnderPopulatedThresshold
	local newOverPop = DnaSamples[math.random(#DnaSamples)].OverPopulatedThresshold
	local newRepro = DnaSamples[math.random(#DnaSamples)].Reproduction

	local averageColour = { r = newColour.r, g = newColour.g, b = newColour.b, a = 1}
	CreatedDNA.Colour = averageColour
	CreatedDNA.UnderPopulatedThresshold = newUnderPop
	CreatedDNA.OverPopulatedThresshold = newOverPop
	CreatedDNA.Reproduction = newRepro

	return CreatedDNA
end
