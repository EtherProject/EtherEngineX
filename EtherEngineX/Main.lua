Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")
EtherSprite = UsingModule("EtherSprite")
EtherAction = UsingModule("EtherAction")
EtherEvent = UsingModule("EtherEvent")

local window = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local sprite1 = EtherSprite.CreateSprite()
local sprite2 = EtherSprite.CreateSprite()
local image1 = EtherImage.LoadImageFromFile("test.png")
local image2 = EtherImage.LoadImageFromFile("testImage.png")
local action1 = EtherAction.CreateSpinBy(-3600.0, 4)
local action2 = EtherAction.CreateMoveBy({x = 500, y = 500}, 2)
local action3 = EtherAction.CreateMoveTo({x = 50, y = 50}, 2)
local action5 = EtherAction.CreateScaleTo(400, 400, 4)

local listener = EtherEvent.CreateKeyboardListener("sakuya")

listener:SetKeyDown(function()
    if listener:GetKeyType() == EtherEvent.KEY_H then
        print("H down")
    end
end)

listener:SetKeyUp(function()
    if listener:GetKeyType() == EtherEvent.KEY_H then
        print("H up")
    end
end)

action1:SetCallback(function()
    print("test")
end)

function Main.Init()
    print("Here are Main.Init()")

    window:AddNode(sprite1)
    sprite1:AddImage(image1)
    sprite1:AddChild(sprite2)
    sprite2:AddImage(image2)
    image1:SetImageDynamic(true, 4, 100, 100)
    image1:SetPlaySpeed(5)
    sprite1:SetCopyRect({x = 100, y = 100, w = 200, h = 200})
    sprite2:SetCopyRect({x = 50, y = 50, w = 150, h = 200})
    sprite1:RunAction(action2, action3)
    sprite1:RunAction(action1)
    sprite1:RunAction(action5)
    sprite2:RunAction(action1)
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main