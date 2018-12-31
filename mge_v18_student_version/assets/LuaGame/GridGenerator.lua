function Create2DGrid(columns, rows)
   grid = {}
   for row = 1, rows do
        grid[row] = {}    
        for column = 1, columns do
            grid[row] [column] = math.random( 2 ) - 1
        end
    end
   return grid
end
--[[ 
Gameboard = Create2DGrid(5, 4)
for row, rows in pairs(Gameboard) do
    rowValues = ""
    --print("Row: " .. row)
    for column, columns in pairs(rows) do
        rowValues = rowValues .. " " .. columns
        --print("Column: " .. column .. " Value: " .. columns)
    end
    print("Row #" .. row .. " " .. rowValues)
end ]]