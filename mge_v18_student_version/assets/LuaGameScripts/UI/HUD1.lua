require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 189.5, y = 821.3, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 51.6
newUI0.Width = 67.9
newUI0.Type = 'TEXT'
newUI0.FontPath = 'mge/UI/Futura_ICG'
newUI0.FontSize = 36
newUI0.Text = '72'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 58, y = 773.9, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 87
newUI1.Width = 156
newUI1.Type = 'IMAGE'
newUI1.ImagePath = 'mge/UI/HUD_footsteps.png'
table.insert(Buttons, newUI1)

local newUI2 = UIObject:new()
newUI2.Position = { x = 58, y = 874.8, z = 0 }
newUI2.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI2.Scale = { x = 1, y = 1, z = 1 }
newUI2.Height = 156
newUI2.Width = 156
newUI2.Type = 'IMAGE'
newUI2.ImagePath = 'mge/UI/HUD_portrait.png'
table.insert(Buttons, newUI2)

