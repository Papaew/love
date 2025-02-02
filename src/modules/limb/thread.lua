R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local thread_cls = require('limb.common.luathread')

local _M = {}

function _M.update(dt)
	local list = limb.app.threads
	local process = 1
	local put = 1
	while true do
		local element = list[process]
		if not element then return end
		list[process] = nil
		if element:isAlive() then
			element:process(dt)
			list[put] = element
			put = put + 1
		else
			element:destroy()
		end
		process = process + 1
	end
end

function _M.newThread(f)
	local th = thread_cls(f)
	table.insert(limb.app.threads, th)
	return th
end

return _M
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
