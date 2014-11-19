#! /usr/bin/env lua
local worker = require("worker")
local io = require("io")
local print, setmetatable = print, setmetatable

module "gearmanWorker"

gearmanWorker = {host="127.0.0.1", port=4730, ssl=false, timeout= 0}

function gearmanWorker:new(host, port, ssl, timeout)
	print(host, port, ssl, timeout)
	local gworker,ret = worker.initialize(host, port, ssl, timeout)
 	if(ret ~= true) then
		io.stderr:write("initialize worker context failed\t")
		return false
	end

	o = {}
	o.gworker = gworker
	setmetatable(o, self)
	self.__index = self
	return o
end

function gearmanWorker:registerFunc(func)
	self.callback = func
end

function gearmanWorker:work()
	worker.loop(self.gworker, self.callback)
end
