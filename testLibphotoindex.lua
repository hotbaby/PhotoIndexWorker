#! /usr/bin/env lua

local photoindex = require('libphotoindex')

local cursor = photoindex.initialize()
cursor:meta_func("hello world.")
