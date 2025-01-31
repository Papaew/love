R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.

local class = require('class')

local luaThread = class()

function luaThread:init(body)
	self._alive = false
	self._paused = true
	self._time = 0
	self._co = coroutine.create(body)
end

function luaThread:type()
	return 'thread'
end

function luaThread:typeOf(name)
	return name == 'thread'
end

function luaThread:start(...)
	self._alive = true
	self._paused = false

	local success, err = coroutine.resume(self._co, ...)
	if not success then
		error(err, 2)
	end
	self._alive = coroutine.status(self._co) ~= 'dead'
end

function luaThread:process(dt)
	if not self._alive or self._paused then return end
	self._time = self._time + dt

	local success, err = coroutine.resume(self._co, self)
	self._alive = coroutine.status(self._co) ~= 'dead'

	if not success then
		error(err, 2)
		self:stop()
	end
end

function luaThread:stop()
	if not self._alive then return end
	self._paused = false
	self._alive = false
end

function luaThread:pause()
	if not self._alive then return end
	self._paused = true
end

function luaThread:resume()
	if not self._alive then return end
	self._paused = false
end

function luaThread:release()
	self:stop()
	self._co = nil
	self = nil
end

function luaThread:setTime(time)
	self._time = time
end

function luaThread:isAlive()
	return self._alive
end

function luaThread:getTime()
	return self._time
end

return luaThread

-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
