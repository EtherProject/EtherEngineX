Main = {}
EtherGraphic = UsingModule("EtherGraphic")
EtherWindow = UsingModule("EtherWindow")
EtherSprite = UsingModule("EtherSprite")
EtherAction = UsingModule("EtherAction")
EtherEvent = UsingModule("EtherEvent")
EtherMedia = UsingModule("EtherMedia")

local window = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local font = EtherGraphic.LoadFontFromFile("msyh.ttf", 50)

local sprite1 = EtherSprite.CreateSprite()
local sprite2 = EtherSprite.CreateSprite()
local sprite3 = EtherSprite.CreateSprite()

local image1 = EtherGraphic.LoadImageFromFile("test.png")
local image2 = EtherGraphic.LoadImageFromFile("testImage.png")
local words1 = EtherGraphic.CreateTextImage(font, "English", {r = 255, g = 0, b = 0, a = 255}, EtherGraphic.TEXT_PATTERN_BLENDED, EtherGraphic.CODE_FORMAT_UTF8)

local action1 = EtherAction.CreateSpinBy(-3600.0, 4)
local action2 = EtherAction.CreateMoveBy({x = 500, y = 500}, 2)
local action3 = EtherAction.CreateMoveTo({x = 50, y = 50}, 2)
local action5 = EtherAction.CreateScaleTo(400, 400, 4)

local listener = EtherEvent.CreateWindowListener("sakuya")

local music = EtherMedia.LoadMusic("test.mp3")

local returnValue = 0

action1:SetCallback(function()
    print("test")
end)

function Main.Init()
    print("Here are Main.Init()")

    listener:SetWindowEnter(function()
        print("Oh! You're back~ A.A")
    end)

    listener:SetWindowLeave(function()
        print("Don't leave me QAQ")
    end)

    window:AddNode(sprite1)
    sprite1:AddChild(sprite2)
    window:AddNode(sprite3)

    sprite1:AddImage(image1)
    sprite2:AddImage(image2)
    sprite3:AddImage(words1)

    image1:SetImageDynamic(true, 4, 100, 100)
    image1:SetPlaySpeed(5)

    sprite1:SetCopyRect({x = 100, y = 100, w = 200, h = 200})
    sprite2:SetCopyRect({x = 50, y = 50, w = 150, h = 200})
    sprite3:SetCopyRect({x = 200, y = 200, w = 200, h = 50})

    sprite1:RunAction(action2, action3)
    sprite1:RunAction(action1)
    sprite1:RunAction(action5)
    sprite2:RunAction(action1)

    music:PlayWithFadeIn(-1, 2000)
end

function Main.Update()
    return returnValue
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main