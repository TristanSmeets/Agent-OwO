require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 150, y = 1008, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 146
newUI0.Width = 380
newUI0.Type = 'BUTTON'
newUI0.ButtonType = 'RETURN'
newUI0.ImagePath = 'mge/UI/Back_Button.png'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 960, y = 540, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 1080
newUI1.Width = 1920
newUI1.Type = 'IMAGE'
newUI1.ImagePath = 'mge/UI/Credits_screen.png'
table.insert(Buttons, newUI1)

