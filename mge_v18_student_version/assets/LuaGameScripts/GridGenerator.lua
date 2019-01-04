local gridModule = {};

math.randomseed(os.time())

--[[Creates a "2D" array with the specified columns and rows.
    Fills the array with the value 0.]]
function gridModule.Create2DGrid(columns, rows)
   Grid = {}
   for row = 1, rows do
        Grid[row] = {}    
        for column = 1, columns do
            Grid[row] [column] = 0;
        end
    end
   return Grid
end

--[[Fills the given "2D" array with true or false values]]
function gridModule.RandomBoolFill2DGrid(columnAmount, rowAmount)
  newGrid = gridModule.Create2DGrid(columnAmount, rowAmount)
    for RowIndex, Row in pairs(newGrid) do
        for  ColumnIndex, Column in pairs(Row) do
            local BoolValue = math.random( 2 ) - 1
            if BoolValue == 1 then
              newGrid[RowIndex] [ColumnIndex] = true
            else
              newGrid[RowIndex] [ColumnIndex] = false
            end
        end
    end
    return newGrid
end

return gridModule;
