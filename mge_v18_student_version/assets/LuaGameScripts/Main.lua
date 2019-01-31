--Requires
require("LuaGameScripts\\OrganismDNA")
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\RuleChecker")

local width = 0
local height = 0
local squareSize = 0

math.randomseed(os.time())

function Start(pScreenWidth, pScreenHeight, pSquareSize)
    print("Called the start function in Main.lua")
	width = pScreenWidth
	height = pScreenHeight
	squareSize = pSquareSize

	columns = math.floor( width / squareSize )
	rows = math.floor( height / squareSize )
	
	RectangleGrid = GridGenerator:CreateDrawRectangleGrid(columns, rows, squareSize) 

	local DNATable = {}

	local randomDNA = OrganismDNA:newRandomColour()
	table.insert(DNATable, randomDNA)

	local randomDNA2 = OrganismDNA:newRandomColour()
	table.insert(DNATable, randomDNA2)
	
	local DNA2 = OrganismDNA:NewColoured(1, 0, 0)
	table.insert(DNATable, DNA2)
	
	local DNA3 = OrganismDNA:NewColoured(0, 1, 0)
	table.insert(DNATable, DNA3)
	
	local DNA4 = OrganismDNA:NewColoured(0, 0, 1)
	table.insert(DNATable, DNA4)
	
	local DNA5 = OrganismDNA:NewPopulation(1, 2, 2)
	table.insert(DNATable, DNA5)
	
	print("Creating GameGrid")
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
