--Requires
require("LuaGameScripts\\OrganismDNA")
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\RuleChecker")

local width = 0
local height = 0
local squareSize = 0

function Start(pScreenWidth, pScreenHeight, pSquareSize)
    print("Called the start function in Main.lua")
	width = pScreenWidth
	height = pScreenHeight
	squareSize = pSquareSize

	columns = math.floor( width / squareSize )
	rows = math.floor( height / squareSize )
	
	RectangleGrid = GridGenerator:CreateRectangleShapeGrid(columns, rows, squareSize) 

	local DNATable = {}
	
	--Create 5 OrganismDNAs with random colour values.
	for i = 1, 5 do
		local randomDNA = OrganismDNA:NewRandomColour()
		table.insert(DNATable, randomDNA)
	end

	--Create an OrganismDNA that is red
	local DNA2 = OrganismDNA:NewColoured(1, 0, 0)
	table.insert(DNATable, DNA2)
	
	--Create an OrganismDNA that is green
	local DNA3 = OrganismDNA:NewColoured(0, 1, 0)
	table.insert(DNATable, DNA3)
	
	--Create an OrganismDNA that is blue
	local DNA4 = OrganismDNA:NewColoured(0, 0, 1)
	table.insert(DNATable, DNA4)
	
	--Create an Organism with adjusted population thressholds
	local DNA5 = OrganismDNA:NewPopulationThressholds(1, 2, 2)
	table.insert(DNATable, DNA5)

	GameGrid = GridGenerator:CreateNewOrganismGrid(columns, rows, DNATable)
end

function Update()
   	local NewGameGrid = RuleChecker:UpdateGrid(GameGrid, columns, rows)
	GameGrid = NewGameGrid
end

function Draw()
    for rowIndex, rows in pairs(GameGrid) do
        for columnIndex, columns in pairs(rows) do
			GameGrid[rowIndex][columnIndex]:Draw(RectangleGrid[rowIndex][columnIndex])
        end
    end
end
