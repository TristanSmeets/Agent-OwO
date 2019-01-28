--Requires
require("LuaGameScripts\\OrganismDNA")
require("LuaGameScripts\\GridGenerator")
require("LuaGameScripts\\GridChecker")


local width = 0
local height = 0
local squareSize = 0

local counter = 0


function Start(pScreenWidth, pScreenHeight, pSquareSize)
    print("Called the start function in Main.lua")
	width = pScreenWidth
	height = pScreenHeight
	squareSize = pSquareSize

	columns = math.floor( width / squareSize )
	rows = math.floor( width / squareSize )
	print("Creating GameGrid")

	RectangleGrid = GridGenerator:Create2DGrid(columns, rows);

	for RowIndex, Row in pairs(RectangleGrid) do
		for ColumnIndex, Column in pairs(Row) do
			RectangleGrid[RowIndex][ColumnIndex] = DrawRectangle:New()
			RectangleGrid[RowIndex][ColumnIndex]:SetSquareSize(squareSize - 1)
			RectangleGrid[RowIndex][ColumnIndex]:SetPosition((ColumnIndex - 1) * squareSize, (RowIndex - 1) * squareSize)
		end
	end

	GameGrid = GridGenerator:CreateOrganismGrid(columns, rows, squareSize, OrganismDNA)
end

function Update()
    counter = counter + 1
    if counter > 1 then
		local NewGameGrid = GridChecker:UpdatedOrganismGrid(GameGrid, columns, rows, squareSize, OrganismDNA)
		GameGrid = NewGameGrid
		counter = 0
    end
end

function Draw()
	--print("Called Draw() in Main.Lua")
    for rowIndex, rows in pairs(GameGrid) do
        for columnIndex, columns in pairs(rows) do
			GameGrid[rowIndex][columnIndex]:Draw(RectangleGrid[rowIndex][columnIndex])
        end
    end
end
