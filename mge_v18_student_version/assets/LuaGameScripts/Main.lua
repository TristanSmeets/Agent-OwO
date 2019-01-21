--Requires
--[[
require("LuaGameScripts\config")
require("LuaGameScripts\OrganismDNA")
require("LuaGameScripts\GridGenerator")
require("LuaGameScripts\OrganismDNA")

width, height = 100
squareSize = 10
local counter = 0
columns = math.floor( width / squareSize )
rows = math.floor( width / squareSize )
--]]

function Start()
    print("Called the start function in Main.lua")
	--GameGrid = GridGenerator:CreateOrganismGrid(columns, rows, OrganismDNA)
end

function Update()
	print("Called Update() in Main.lua")
    --counter = counter + 1
    --[[if counter > 5 then
       local NewGameGrid = GridChecker:NewOrganismGrid(GameGrid, columns, rows, squareSize, OrganismDNA)
       GameGrid = NewGameGrid
       counter = 0
    end]]--
end

function Draw()
	print("Called Draw() in Main.Lua")
    --[[for rowIndex, rows in pairs(GameGrid) do
        for columnIndex, columns in pairs(rows) do
            GameGrid[rowIndex][columnIndex]:Draw()
        end
    end]]--
end


--[[ --Requires
require("GridChecker")
require("GridGenerator")
require("BaseOrganism")
require("OrganismDNA")

squareSize = 20
local counter = 0
width, height = love.graphics.getDimensions()
columns = math.floor(width / squareSize)
rows = math.floor(height / squareSize)

function love.load()
  Cellboard = GridGenerator:CreateOrganismGrid(columns, rows, squareSize, OrganismDNA)
end

function love.update()
  counter = counter + 1
  if counter > 5 then
    NewCellboard = GridChecker:NewOrganismGrid(Cellboard, columns, rows, squareSize, OrganismDNA)
    Cellboard = NewCellboard
    counter = 0
  end
end

function love.draw()
  love.graphics.clear(0, 0, 0, 1)
  DrawOrganismGrid(Cellboard)
end

function DrawOrganismGrid(cellGrid)
  for rowIndex, rows in pairs(cellGrid) do
    for columnIndex, columns in pairs(rows) do
      cellGrid[rowIndex][columnIndex]:Draw()
    end
  end
end
 ]]
