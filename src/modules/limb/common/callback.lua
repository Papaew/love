R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local class = require('class')

local Callback = class()

function Callback:init(parent, body)
	self._parent = parent
	self._body = body
end

function Callback:release()
	self._parent = nil
	self._body = nil
	self = nil
end

function Callback:call(...)
	if not self._parent.isEnabled or self._parent:isEnabled() then
		self._body(self._parent, ...)
	end
end

return Callback
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
