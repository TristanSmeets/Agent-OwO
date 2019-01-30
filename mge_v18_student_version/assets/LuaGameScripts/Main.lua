--Requires
require("LuaGameScripts\\OrganismDNA")
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\GridChecker")

local width = 0
local height = 0
local squareSize = 0

local counter = 0
math.randomseed(os.time())

function Start(pScreenWidth, pScreenHeight, pSquareSize)
    print("Called the start function in Main.lua")
	width = pScreenWidth
	height = pScreenHeight
	squareSize = pSquareSize

	columns = math.floor( width / squareSize )
	rows = math.floor( height / squareSize )
	
	print("Creating GameGrid")
	RectangleGrid = GridGenerator:Create2DGrid(columns, rows);

	for RowIndex, Row in pairs(RectangleGrid) do
		for ColumnIndex, Column in pairs(Row) do
			RectangleGrid[RowIndex][ColumnIndex] = DrawRectangle:New()
			RectangleGrid[RowIndex][ColumnIndex]:SetSquareSize(squareSize - 1)
			RectangleGrid[RowIndex][ColumnIndex]:SetPosition((ColumnIndex - 1) * squareSize, (RowIndex - 1) * squareSize)
			RectangleGrid[RowIndex][ColumnIndex]:SetColour(0,0,0,1)
		end
	end

	local DNATable = {}

	local DNA = OrganismDNA:new()
	table.insert(DNATable, DNA)
	
	local DNA2 = OrganismDNA:NewColoured(1, 0, 0)
	table.insert(DNATable, DNA2)
	
	local DNA3 = OrganismDNA:NewColoured(0, 1, 0)
	table.insert(DNATable, DNA3)
	
	local DNA4 = OrganismDNA:NewColoured(0, 0, 1)
	table.insert(DNATable, DNA4)
	
	local DNA5 = OrganismDNA:NewPopulation(1,2,2)
	table.insert(DNATable, DNA5)
	
	GameGrid = GridGenerator:CreateNewOrganismGrid(columns, rows, DNATable)
end

function Update()
   	local NewGameGrid = GridChecker:UpdateGrid(GameGrid, columns, rows)
	GameGrid = NewGameGrid
end

function Draw()
    for rowIndex, rows in pairs(GameGrid) do
        for columnIndex, columns in pairs(rows) do
			GameGrid[rowIndex][columnIndex]:Draw(RectangleGrid[rowIndex][columnIndex])
        end
    end
end
