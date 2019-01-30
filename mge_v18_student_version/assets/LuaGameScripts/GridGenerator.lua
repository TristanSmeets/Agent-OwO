GridGenerator = {};

--Requires
require("LuaGameScripts\\BaseOrganism")

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

function GridGenerator:CreateNewOrganismGrid(columns, rows, DNATable)
  local newCellGrid = GridGenerator:Create2DGrid(columns, rows)
  for RowIndex, Row in pairs(newCellGrid) do
    for ColumnIndex, Column in pairs(Row) do
      local aliveValue = math.random(2) - 1
      local DNA = OrganismDNA:new()
	  DNA.Colour = DNATable[math.random(#DNATable)].Colour
	  DNA.UnderPopulatedThresshold = DNATable[math.random(#DNATable)].UnderPopulatedThresshold
	  DNA.OverPopulatedThresshold = DNATable[math.random(#DNATable)].OverPopulatedThresshold
	  DNA.Reproduction = DNATable[math.random(#DNATable)].Reproduction

      if aliveValue == 1 then
        DNA.IsAlive = true
        newCellGrid[RowIndex][ColumnIndex] = BaseOrganism:new(DNA)
      else
        DNA.IsAlive = false
        newCellGrid[RowIndex][ColumnIndex] = BaseOrganism:new(DNA)
      end
    end
  end
  return newCellGrid
end
