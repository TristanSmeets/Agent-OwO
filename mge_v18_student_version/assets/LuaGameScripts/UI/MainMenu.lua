require('LuaGameScripts\\UIObject')

Buttons = {}
local newUI0 = UIObject:new()
newUI0.Position = { x = 394.7, y = 560.7, z = 0 }
newUI0.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI0.Scale = { x = 1, y = 1, z = 1 }
newUI0.Height = 24
newUI0.Width = 221
newUI0.Type = 'BUTTON'
newUI0.ButtonType = 'CONTROLS'
newUI0.ImagePath = 'mge/UI/MainMenu_controls_button.png'
table.insert(Buttons, newUI0)

local newUI1 = UIObject:new()
newUI1.Position = { x = 526.4, y = 734.8, z = 0 }
newUI1.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI1.Scale = { x = 1, y = 1, z = 1 }
newUI1.Height = 22
newUI1.Width = 90
newUI1.Type = 'BUTTON'
newUI1.ButtonType = 'EXIT'
newUI1.ImagePath = 'mge/UI/MainMenu_exit_button.png'
table.insert(Buttons, newUI1)

local newUI2 = UIObject:new()
newUI2.Position = { x = 298.2, y = 485.8, z = 0 }
newUI2.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI2.Scale = { x = 1, y = 1, z = 1 }
newUI2.Height = 26
newUI2.Width = 318
newUI2.Type = 'BUTTON'
newUI2.ButtonType = 'START'
newUI2.ImagePath = 'mge/UI/MainMenu_start_button.png'
table.insert(Buttons, newUI2)

local newUI3 = UIObject:new()
newUI3.Position = { x = 960, y = 540, z = 0 }
newUI3.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI3.Scale = { x = 1, y = 1, z = 1 }
newUI3.Height = 1080
newUI3.Width = 1920
newUI3.Type = 'BACKGROUND'
newUI3.ImagePath = 'mge/UI/MainMenu_background.png'
table.insert(Buttons, newUI3)

local newUI4 = UIObject:new()
newUI4.Position = { x = 439.3, y = 648.8, z = 0 }
newUI4.Rotation = { x = 0, y = 0, z = 0, w = 1 }
newUI4.Scale = { x = 1, y = 1, z = 1 }
newUI4.Height = 22
newUI4.Width = 177
newUI4.Type = 'BUTTON'
newUI4.ButtonType = 'CREDIT'
newUI4.ImagePath = 'mge/UI/MainMenu_credits_button.png'
table.insert(Buttons, newUI4)

