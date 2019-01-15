GridChecker = {}

--Requires
require("GridGenerator")

--Local variables
local columns = nil
local rows = nil

--[[Counts the amount of organisms that are alive.
    Returns the amount of live organisms.]]
local function checkNeighbourOrganisms(gameGrid, x, y)
  local Sum = 0
  for RowIndex = -1, 1 do
    for ColumnIndex = -1, 1 do
      local column = (x - 1 + ColumnIndex + columns) % columns
      local row = (y - 1 + RowIndex + rows) % rows
      if(column + 1) == x and (row + 1) == y then
      elseif gameGrid[row + 1][column + 1].OrganismDNA.IsAlive == true then
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
function GridChecker:NewOrganismGrid(gameGrid, totalColumns, totalRows, Organism, OrganismDNA, squareSize)
  columns = totalColumns
  rows = totalRows

  local NewOrganismGrid = GridGenerator:CreateOrganismGrid(totalColumns, totalRows, Organism, OrganismDNA, squareSize)
  
  for i, Row in pairs(NewOrganismGrid) do
    for j, Column in pairs(Row) do
      local LiveNeighbours = checkNeighbourOrganisms(gameGrid, j, i)
      NewOrganismGrid[i][j].OrganismDNA.IsAlive = checkIsAlive(LiveNeighbours, gameGrid[i][j].OrganismDNA.IsAlive)
    end
  end
  return NewOrganismGrid
end
