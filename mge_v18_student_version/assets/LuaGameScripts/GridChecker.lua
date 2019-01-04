local gridChecker = {}

local GridCreator = require("GridGenerator")

--[[Functions that are going to do stuff with the given grid]]
local columns = nil
local rows = nil
local newGrid = nil


--[[Count the amount of neighbours that are alive.
    Returns the amount of live neighbours.]]
local function checkLiveNeighbours(gameGrid, x,y)
  local Sum = 0
  for RowIndex = -1, 1 do
    for ColumnIndex = -1, 1 do
      local column = (x -1 + ColumnIndex + columns) % columns
      local row = (y - 1 + RowIndex + rows) % rows
        if(column + 1) == x and (row + 1) == y then
        elseif gameGrid[row + 1 ] [column + 1] == true then
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

--[[Loops over all the cells in the passed in grid.
    For each cell it checks how many live neighbours it has.
    Checks if the cell should be alive and puts the value in the cell.
    Returns the grid with updated values]]
function gridChecker.NewGameGrid(gameGrid,totalColumns, totalRows)
    columns = totalColumns
    rows = totalRows
    newGrid = GridCreator.Create2DGrid(totalColumns, totalRows)
    for i, Row in pairs(newGrid) do
        for j, Column in pairs(Row) do
            local LiveNeighbours = checkLiveNeighbours(gameGrid,j,i)
            newGrid[i][j] = checkIsAlive(LiveNeighbours, gameGrid[i][j])
        end
    end
    return newGrid
end

return gridChecker
