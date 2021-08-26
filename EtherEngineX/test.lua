test = {}

function test.init()
    print("Here are test.init")
end

function test.update()
    print("Here are test.update")
    return -1
end

function test.unload()
    print("Here are test.unload")
end

return test