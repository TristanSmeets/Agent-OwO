local gridModule = {}

--[[Creates a "2D" array with the specified columns and rows.
    Fills the array with the value 0.]]
function Create2DGrid(columns, rows)
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
function RandomBoolFill2DGrid(grid)
    for RowIndex, Row in pairs(grid) do
        for  ColumnIndex, Column in pairs(Row) do
            local BoolValue = math.random( 2 ) - 1
            if BoolValue == 1 then
                grid[Row] [Column] = true
            else
                grid[Row] [Column] = false
            end
        end
    end
    return grid
end

return gridModule
