test = {}

function test.Init()
    print("Here are test.Init()")
end

function test.Update()
    print("Here are test.Update()")
    return -1
end

function test.Unload()
    print("Here are test.Unload()")
end

return test