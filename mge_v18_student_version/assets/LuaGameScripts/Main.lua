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
	print("Width: " .. width)
	print("Height: " .. height)
	print("SquareSize: " .. squareSize)

	columns = math.floor( width / squareSize )
	rows = math.floor( width / squareSize )
	print("Creating GameGrid")
	GameGrid = GridGenerator:CreateOrganismGrid(columns, rows, squareSize, OrganismDNA)
end

function Update()
    counter = counter + 1
    if counter > 5 then
		local NewGameGrid = GridChecker:UpdatedOrganismGrid(GameGrid, columns, rows, squareSize, OrganismDNA)
		GameGrid = NewGameGrid
		counter = 0
    end
end

function Draw()
	--print("Called Draw() in Main.Lua")
    --[[for rowIndex, rows in pairs(GameGrid) do
        for columnIndex, columns in pairs(rows) do
            GameGrid[rowIndex][columnIndex]:Draw()
        end
    end]]--
end
