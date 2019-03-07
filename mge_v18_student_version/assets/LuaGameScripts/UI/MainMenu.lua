require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 600, y = 665, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 25
newUI0.Width = 227
newUI0.Type = 'BUTTON'
newUI0.ButtonType = 'EXIT'
newUI0.ImagePath = 'mge/UI/MainMenu_exit_button.png'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 500, y = 500, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 30
newUI1.Width = 318
newUI1.Type = 'BUTTON'
newUI1.ButtonType = 'START'
newUI1.ImagePath = 'mge/UI/MainMenu_start_button.png'
table.insert(Buttons, newUI1)

local newUI2 = UIObject:new()
newUI2.Position = { x = 960, y = 540, z = 0 }
newUI2.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI2.Scale = { x = 1, y = 1, z = 1 }
newUI2.Height = 1080
newUI2.Width = 1920
newUI2.Type = 'BACKGROUND'
newUI2.ImagePath = 'mge/UI/'
table.insert(Buttons, newUI2)

local newUI3 = UIObject:new()
newUI3.Position = { x = 352.1, y = 600, z = 0 }
newUI3.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI3.Scale = { x = 1, y = 1, z = 1 }
newUI3.Height = 26
newUI3.Width = 179
newUI3.Type = 'BUTTON'
newUI3.ButtonType = 'CREDIT'
newUI3.ImagePath = 'mge/UI/MainMenu_credits_button.png'
table.insert(Buttons, newUI3)

