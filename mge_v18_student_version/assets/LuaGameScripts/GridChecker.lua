local gridChecker = {}

--[[Functions that are going to do stuff with the given grid]]
local columns = nil
local rows = nil
local newGrid = nil

--[[Loops over all the cells in the passed in grid.
    For each cell it checks how many live neighbours it has.
    Checks if the cell should be alive and puts the value in the cell.
    Returns the grid with updated values]]
function NewGameGrid(gameGrid,totalColumns, totalRows)
    columns = totalColumns
    rows = totalRows
    local GridCreator = require("GridGenerator")
    newGrid = GridCreator.Create2DGrid(totalColumns, totalRows)

    for i, Row in pairs(newGrid) do
        for j, Column in pairs(Row) do
            newGrid[Row] [Column] = checkIsAlive(checkLiveNeighbours(Column, Row))
        end
    end
    return newGrid
end

--[[Count the amount of neighbours that are alive.
    Returns the amount of live neighbours.]]
local function checkLiveNeighbours(x,y)
   local Sum = 0
    for RowIndex = -1, RowIndex < 2, RowIndex + 1 do
        for ColumnIndex = -1, ColumnIndex < 2, ColumnIndex + 1 do
            local column = (x + ColumnIndex + columns) % columns
            local row = (x + RowIndex + rows) % rows
            if not gameGrid[column] == x and gameGrid[row] == y then
                if gameGrid[row] [column] == true then
                    Sum = Sum + 1
                end
            end
        end
    end
    return Sum
end

--[[Checks if the amount of aliveNeighbours makes it viable to live.
    Returns true or false depending on if it should be alive]]
local function checkIsAlive(aliveNeighbours)
    if aliveNeighbours < 2 or aliveNeighbours > 3 then
        return false
    else
        return true
    end
end

return gridChecker
