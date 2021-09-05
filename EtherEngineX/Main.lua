Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")

local window1 = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local layer1 = window1:CreateLayer()

local window2 = EtherWindow.CreateWindow("test2", {x = 100, y = 100, w = 960, h = 640}, {})
local layer2 = window2:CreateLayer()

local window3 = EtherWindow.CreateWindow("test3", {x = 100, y = 100, w = 960, h = 640}, {})
local layer3 = window3:CreateLayer()

local testImage1 = EtherImage.LoadImageFromFile("testImage.png")
local testImage2 = EtherImage.LoadImageFromFile("testImage.png")
local testImage3 = EtherImage.LoadImageFromFile("testImage.png")
local rect = {x = 200, y = 40, w = 400, h = 500}

function Main.Init()
    print("Here are Main.Init()")
    testImage1:SetPosition(rect.x, rect.y)
    testImage1:SetSize(rect.w, rect.h)
    testImage2:SetPosition(rect.x, rect.y)
    testImage2:SetSize(rect.w, rect.h)
    testImage3:SetPosition(rect.x, rect.y)
    testImage3:SetSize(rect.w, rect.h)
    layer1:AddNode(testImage1)
    layer2:AddNode(testImage2)
    layer3:AddNode(testImage3)
    testImage1:CreateTexture()
    testImage2:CreateTexture()
    testImage3:CreateTexture()
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main