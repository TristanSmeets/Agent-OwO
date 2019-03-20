require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 960, y = 540, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 1080
newUI0.Width = 1920
newUI0.Type = 'BACKGROUND'
newUI0.ImagePath = 'mge/UI/Control_screen.png'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 150, y = 1008, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 39
newUI1.Width = 178
newUI1.Type = 'BUTTON'
newUI1.ButtonType = 'RETURN'
newUI1.ImagePath = 'mge/UI/Back_Button.png'
table.insert(Buttons, newUI1)
