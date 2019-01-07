GridGenerator = {};

--Requires

--Give the time as a seed to math.random
math.randomseed(os.time())

--[[Creates a "2D" array with the specified columns and rows.
    Fills the array with the value 0.]]
function GridGenerator:Create2DGrid(columns, rows)
  local grid = {}
  for row = 1, rows do
    grid[row] = {}    
    for column = 1, columns do
      grid[row] [column] = 0;
      end
  end
  return grid
end

--[[Fills the given "2D" array with true or false values]]
function GridGenerator:RandomBoolFill2DGrid(columnAmount, rowAmount)
  local newGrid = GridGenerator:Create2DGrid(columnAmount, rowAmount)
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

function GridGenerator:CreateOrganismGrid(columns, rows, Organism)
  local newCellGrid = GridGenerator:Create2DGrid(columns, rows)
  for RowIndex, Row in pairs(newCellGrid) do
    for ColumnIndex, Column in pairs(Row) do
      local isAlive = math.random(2) - 1
      if isAlive == 1 then
        newCellGrid[RowIndex][ColumnIndex] = Organism:new(true)
      else
        newCellGrid[RowIndex][ColumnIndex] = Organism:new(false)
      end
    end
  end
  return newCellGrid
end
