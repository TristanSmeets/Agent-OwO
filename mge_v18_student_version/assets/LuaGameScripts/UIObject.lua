UIObject = {}

function UIObject:new()
    local uiObject = {}
    setmetatable(uiObject, self)
    self.__index = self
    uiObject.Position = { x = 0, y = 0, z = 0 }
    uiObject.Rotation = { x = 0, y = 0, z = 0, w = 0 }
    uiObject.Scale = { x = 0, y = 0, z = 0 }
    uiObject.Height = 0
    uiObject.Width = 0
    uiObject.Type = ''
    uiObject.ButtonType = ''
    uiObject.ImagePath = ''
    uiObject.FontPath = ''
    uiObject.FontSize = ''
    uiObject.Text = ''
    return uiObject
end