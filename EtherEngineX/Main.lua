Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")
EtherSprite = UsingModule("EtherSprite")

local window = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local layer = window:CreateLayer()
local sprite = EtherSprite.CreateSprite()
local image1 = EtherImage.LoadImageFromFile("test.png")
local image2 = EtherImage.LoadImageFromFile("testImage.png")

function Main.Init()
    print("Here are Main.Init()")
    layer:AddNode(sprite)
    sprite:AddImage(image1)
    sprite:AddImage(image2)
    image1:SetImageDynamic(true, 4, 100, 100)
    image1:SetCurrentFrame(2)
    sprite:SetCopyRect({x = 0, y = 0, w = 200, h = 200})
    sprite:ChangeImage(1)
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main