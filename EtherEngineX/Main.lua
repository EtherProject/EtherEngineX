Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")

local window = EtherWindow.CreateWindow("test", {x = 100, y = 100, w = 960, h = 640}, {})
local layer = window:CreateLayer()
local testImage = EtherImage.LoadImageFromFile("testImage.png")
local rect = {x = 10, y = 10, w = 200, h = 500}

function Main.Init()
    print("Here are Main.Init()")
    testImage:CreateTexture(layer)
    testImage:SetCopyRect(rect)
end

function Main.Update()
    print("Here are Main.Update()")
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
    testImage:ReleaseTexture()
end

return Main