Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")
EtherImage = UsingModule("EtherImage")

local window = EtherWindow.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local layer = window:CreateLayer()
local node = EtherNode.CreateNode()
local image = EtherImage.LoadImageFromFile("test.png")

function Main.Init()
    print("Here are Main.Init()")
    layer:AddNode(node)
    node:SetImage(image)
    node:SetCopyRect({x = 0, y = 0, w = 200, h = 200})
end

function Main.Update()
    return 0
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main