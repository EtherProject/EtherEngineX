Main = {}
EtherNode = UsingModule("EtherNode")
EtherWindow = UsingModule("EtherWindow")

local window = EtherWindow.CreateWindow("test", {x = 100, y = 100, w = 400, h = 400}, {})
local Anode = EtherNode.CreateNode()
local Bnode = EtherNode.CreateNode()
local position = {}
local _position = {x = 10, y = 10}

function Main.Init()
    print("Here are Main.Init()")
    Anode:SetPosition(_position)
    position = Anode:GetPosition()
    Anode:SetParent(Bnode)
    Anode:SetDepth(3)
end

function Main.Update()
    print("Here are Main.Update()")
    print(position.x, position.y)
    local tempNode = Anode:GetParent()
    local __position = tempNode:GetPosition()
    print(__position.x, __position.y)
    print(Anode:GetDepth())
    return 1
end

function Main.Unload()
    print("Here are Main.Unload()")
end

return Main