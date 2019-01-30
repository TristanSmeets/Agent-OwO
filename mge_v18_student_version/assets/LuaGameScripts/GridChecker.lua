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
local function checkIsAlive(aliveNeighbours, state)
  if state then
    if (aliveNeighbours == 2 or aliveNeighbours == 3) then
      return true
    else
      return false
    end
  else
    if aliveNeighbours == 3 then
      return true
    end
  end
end


--[[Loops over all the Organisms in the passed in grid.
    For each Organism it checks how many live neighbours it has.
    Checks if the Organism should be alive in the next generation and sets it's status.
    Returns the grid with updated values]]
function GridChecker:UpdateOrganismGrid(gameGrid, totalColumns, totalRows, DNA)
  columns = totalColumns
  rows = totalRows

  local NewOrganismGrid = GridGenerator:CreateNewOrganismGrid(totalColumns, totalRows, DNA)
  
  for i, Row in pairs(NewOrganismGrid) do
    for j, Column in pairs(Row) do
      local LiveNeighbours = numberAliveNeighbours(gameGrid, j, i)
      NewOrganismGrid[i][j].DNA.IsAlive = checkIsAlive(LiveNeighbours, gameGrid[i][j].DNA.IsAlive)
    end
  end
  return NewOrganismGrid
end

function GridChecker:UpdateGrid(gameGrid, totalColumns, totalRows)
  columns = totalColumns
  rows = totalRows

  local UpdatedGrid = GridGenerator:Create2DGrid(columns, rows)

  for i, Row in pairs(UpdatedGrid) do
    for j, Column in pairs(Row) do

		local LiveNeighbours = numberAliveNeighbours(gameGrid, j, i)

		if checkIsAlive(LiveNeighbours,gameGrid[i][j].DNA.IsAlive) then
			local newDNA = CreateNewDna(gameGrid, j, i)
			newDNA.IsAlive = true
			UpdatedGrid[i][j] = BaseOrganism:new(newDNA)
		else
			local newDNA = OrganismDNA:New(0, 0, 0)
			newDNA.IsAlive = false
			UpdatedGrid[i][j] = BaseOrganism:new(newDNA)
		end
		

		--UpdatedGrid[i][j] = BaseOrganism:new(NewDna)
    end
  end
  return UpdatedGrid
end

function CreateNewDna(Grid, x, y)
	local CreatedDNA = OrganismDNA:new()
	local livingNeighbours = 0
	local newColour = {maxRed = 0, maxGreen = 0, maxBlue = 0}

	local Colours = {}

	for rowIndex = -1, 1 do
		for columnIndex = -1, 1 do
			local column = (x - 1 + columnIndex + columns) % columns
			local row = (y - 1 + rowIndex + rows) % rows
			if (column + 1) == x and (row + 1) == y then
			elseif Grid[row + 1][column + 1].DNA.IsAlive == true then
				
				table.insert(Colours, Grid[row + 1][column + 1].DNA.Colour)

				--[[local CurrentDNAColour = Grid[row + 1][column + 1].DNA.Colour
				livingNeighbours = livingNeighbours + 1
				newColour.maxRed = newColour.maxRed + CurrentDNAColour.r
				newColour.maxGreen = newColour.maxGreen + CurrentDNAColour.g
				newColour.maxBlue = newColour.maxBlue + CurrentDNAColour.b]]--
			end
		end
	end

	local newColour = { r = Colours[math.random(#Colours)].r, g = Colours[math.random(#Colours)].g, b = Colours[math.random(#Colours)].b}

	local averageColour = { r = newColour.r, g = newColour.g, b = newColour.b, a = 1}
	
	CreatedDNA.Colour = averageColour

	return CreatedDNA
end
