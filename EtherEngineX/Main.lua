Main = {}

function Main.init()
    CreateWindow("Test", {x = 100, y = 100, w = 100, h = 100}, {})
    print("Here are Main.init")
end

function Main.update()
    print("Here are Main.update")
    return 1
end

function Main.unload()
    print("Here are Main.unload")
end

return Main