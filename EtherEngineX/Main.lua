Main = {}
EtherNode = UsingModule("EtherNode")

local Anode = EtherNode.CreateNode();
local Bnode = EtherNode.CreateNode();
local position = {}
local _position = {x = 10, y = 10}

function Main.init()
    CreateWindow("Test", {x = 100, y = 100, w = 400, h = 400}, {})
    print("Here are Main.init")
    Anode:SetPosition(_position)
    position = Anode:GetPosition()
    Anode:SetParent(Bnode)
    Anode:SetDepth(3)
end

function Main.update()
    print("Here are Main.update")
    print(position.x, position.y);
    local tempNode = Anode:GetParent();
    local __position = tempNode:GetPosition();
    print(__position.x, __position.y)
    print(Anode:GetDepth())
    return 1
end

function Main.unload()
    print("Here are Main.unload")
    Anode:Release()
end

return Main