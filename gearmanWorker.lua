#! /usr/bin/env lua
local worker = require("worker")
local io = require("io")
local print, setmetatable = print, setmetatable
local type = type

module "gearmanWorker"

gearmanWorker = {host="127.0.0.1", port=4730, ssl=false, timeout= 0}

function gearmanWorker:new(host, port, ssl, timeout, func)
    print(host, port, ssl, timeout, func)
    local gworker,ret = worker.initialize(host, port, ssl, timeout, func)
    if(ret ~= true) then
        io.stderr:write("initialize worker context failed\n")
        return false
    end

    o = {}
    o.gworker = gworker
    setmetatable(o, self)
    self.__index = self
    return o
end

function gearmanWorker:registerFunc(cb)
    self.callback = cb
end

function gearmanWorker:work()
    worker.loop(self.gworker, self.callback)
end
