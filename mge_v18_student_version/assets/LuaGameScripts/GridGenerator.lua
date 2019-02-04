GridGenerator = {};

--Requires
require("LuaGameScripts\\BaseOrganism")

--Give the time as a seed to math.random
math.randomseed(os.time())

--[[Creates a 2D array with the specified columns and rows.
    Fills the array with the value 0.
	Returns the 2D array]]
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

--[[Creates a 2D grid with BaseOrganisms.
	Gets an OrganismDNA from random position passed in the table of OrganismDNAs. 
	Also randomly sets the organisms to alive or dead.
	Returns the Grid]]
function GridGenerator:CreateNewOrganismGrid(columns, rows, DNATable)
  local newCellGrid = GridGenerator:Create2DGrid(columns, rows)
  for RowIndex, Row in pairs(newCellGrid) do
    for ColumnIndex, Column in pairs(Row) do
      local aliveValue = math.random(2) - 1
      local DNA = OrganismDNA:base()
	  DNA.Colour = DNATable[math.random(#DNATable)].Colour
	  DNA.UnderPopulatedThresshold = DNATable[math.random(#DNATable)].UnderPopulatedThresshold
	  DNA.OverPopulatedThresshold = DNATable[math.random(#DNATable)].OverPopulatedThresshold
	  DNA.Reproduction = DNATable[math.random(#DNATable)].Reproduction

      if aliveValue == 1 then
        newCellGrid[RowIndex][ColumnIndex] = BaseOrganism:new(DNA)
      else
        DNA.IsAlive = false
		DNA.Colour = {r = 0, g = 0, b = 0, a = 0}
        newCellGrid[RowIndex][ColumnIndex] = BaseOrganism:new(DNA)
      end
    end
  end
  return newCellGrid
end

--[[Creates a 2D Grid of DrawRectangles.
	Should be called once at the start of the game.
	Returns the 2D Grid]]
function GridGenerator:CreateRectangleShapeGrid(columns, rows, squareSize)
	local newRectangleShapeGrid = GridGenerator:Create2DGrid(columns, rows)
	for RowIndex, Row in pairs(newRectangleShapeGrid) do
		for ColumnIndex, Column in pairs(Row) do
			newRectangleShapeGrid[RowIndex][ColumnIndex] = RectangleShape:New()
			newRectangleShapeGrid[RowIndex][ColumnIndex]:SetSquareSize(squareSize - 1)
			newRectangleShapeGrid[RowIndex][ColumnIndex]:SetPosition((ColumnIndex -1) * squareSize, (RowIndex - 1) * squareSize)
			newRectangleShapeGrid[RowIndex][ColumnIndex]:SetColour(1,1,1,1)
		end
	end
	return newRectangleShapeGrid
end
