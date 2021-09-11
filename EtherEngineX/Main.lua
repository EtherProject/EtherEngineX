Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")
EtherSprite = UsingModule("EtherSprite")
EtherAction = UsingModule("EtherAction")

local window = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local layer = window:CreateLayer()
local sprite = EtherSprite.CreateSprite()
local image1 = EtherImage.LoadImageFromFile("test.png")
local image2 = EtherImage.LoadImageFromFile("testImage.png")
local action1 = EtherAction.CreateSpinBy(-3600.0, 4)
local action2 = EtherAction.CreateMoveBy({x = 500, y = 500}, 2)
local action3 = EtherAction.CreateMoveTo({x = 50, y = 50}, 2)

function Main.Init()
    print("Here are Main.Init()")
    layer:AddNode(sprite)
    sprite:AddImage(image1)
    sprite:AddImage(image2)
    image1:SetImageDynamic(true, 4, 100, 100)
    image1:SetCurrentFrame(2)
    image1:SetPlaySpeed(5)
    sprite:SetCopyRect({x = 100, y = 100, w = 200, h = 200})
    sprite:ChangeImage(1)
    sprite:RunAction(action1)
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main