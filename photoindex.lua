--photoindex config package

local photoindexLib = require("libphotoindex")
local photoindexCtx = photoindexLib.initialize()

PHOTOINDEX = {}
PHOTOINDEX.name = 'PHOTOINDEX'

function PHOTOINDEX.test(...)
    local errorCode = nil
    local result = nil
    arg = { ... }

    print('call function PHOTOINDEX.test.')
    photoindexLib.test_func(photoindexCtx, "hello world.")

    errorCode = nil
    result = '200 OK.'

    return errorCode, result
end

local mt = {
    __index = function(PHOTOINDEX, method)
        error('method:' .. method .. ' not exit.')
    end,
    __newindex = function(PHOTOINDEX, method, newFunc)
        error('update of table ' .. tostring(method) .. ' ' .. tostring(newFunc))
    end
}
setmetatable(PHOTOINDEX, mt)

return PHOTOINDEX
