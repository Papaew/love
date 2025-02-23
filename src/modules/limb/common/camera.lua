R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local class = require('class')

local Camera = class()

function Camera:init(x, y, zoom)
    self._transform = love.math.newTransform(x, y)
	self._attached = false
	self._zoom = zoom
end

function Camera:attach(object)
    if not object.getPosition or not object._x or not object._y then
		return false
	end

	self._thread = limb.thread.newThread(function()
		self._attached = true
		while true do
			local dt = love.timer.getDelta()
			self:update(dt)
			coroutine.yield()
		end
	end)
	self._thread:start()

	return true
end

function Camera:detach()
	if self._thread then
		self._thread:stop()
	end
	self._attached = false
end

function Camera:update(dt)
	-- @todo
end

return Camera
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"