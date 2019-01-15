GridGenerator = {};

--Requires
require("BaseOrganism")

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

function GridGenerator:CreateOrganismGrid(columns, rows, Organism, OrganismDNA, squareSize)
  local newCellGrid = GridGenerator:Create2DGrid(columns, rows)
  for RowIndex, Row in pairs(newCellGrid) do
    for ColumnIndex, Column in pairs(Row) do
      local isAlive = math.random(2) - 1
      local DNA = OrganismDNA:new()
      DNA:SetPosition((ColumnIndex - 1) * squareSize, (RowIndex - 1)* squareSize)
      if isAlive == 1 then
        DNA:SetIsAlive(true)
        newCellGrid[RowIndex][ColumnIndex] = Organism:new(DNA)
      else
        DNA:SetIsAlive(false)
        newCellGrid[RowIndex][ColumnIndex] = Organism:new(DNA)
      end
    end
  end
  return newCellGrid
end
