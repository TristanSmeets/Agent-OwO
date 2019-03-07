require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 959.64, y = 607, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 146
newUI0.Width = 380
newUI0.Type = 'BUTTON'
newUI0.ButtonType = 'EXIT'
newUI0.ImagePath = 'mge/UI/Quit_button.png'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 959.9235, y = 540.043, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 1080
newUI1.Width = 1920
newUI1.Type = 'BACKGROUND'
newUI1.ImagePath = 'mge/UI/black_filter.png'
table.insert(Buttons, newUI1)

local newUI2 = UIObject:new()
newUI2.Position = { x = 959.7, y = 454, z = 0 }
newUI2.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI2.Scale = { x = 1, y = 1, z = 1 }
newUI2.Height = 146
newUI2.Width = 380
newUI2.Type = 'BUTTON'
newUI2.ButtonType = 'CONTINUE'
newUI2.ImagePath = 'mge/UI/Retry_button.png'
table.insert(Buttons, newUI2)

