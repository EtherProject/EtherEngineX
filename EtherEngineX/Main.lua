Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")

local window1 = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local layer1 = window1:CreateLayer()

local testImage1 = EtherImage.LoadImageFromFile("test.png")
local rect = {x = 200, y = 40, w = 400, h = 500}

function Main.Init()
    print("Here are Main.Init()")
    testImage1:SetPosition(rect.x, rect.y)
    testImage1:SetSize(rect.w, rect.h)
    testImage1:SetImageRect({x = 0, y = 0, w = 100, h = 100})
    testImage1:SetImageType(1, 4)
    testImage1:SetPlaySpeed(5)
    layer1:AddNode(testImage1)
    testImage1:CreateTexture()
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main