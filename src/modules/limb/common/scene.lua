R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local class = require('class')
local layer = require('limb.common.layer')

local g = love.graphics

local Scene = class(require 'limb.common.drawable')

function Scene:init(name)
	Scene.baseclass.init(self)
	self._name = name
	self._loaded = false
	self._enabled = true
	self._transform = love.math.newTransform()
	self._layers = {
		by_name = {},
		by_order = {}
	}

	self._thread = limb.thread.newThread(function()
		while true do
			local dt = love.timer.getDelta()
			self:update(dt)
			coroutine.yield()
		end
	end)
	self._thread:start()
	self._thread:pause()
end

function Scene:destroy()
	-- log.info('[destroy]', self._name)
	self:on_destroy()
	self._enabled = false
	self._loaded = false
	self._thread:release()
	self._transform:release()
	for i = #self._layers.by_order, 1, -1 do
		local l = table.remove(self._layers.by_order)
		self._layers.by_name[l:getName()] = nil
		l:release()
	end
	self._layers = nil
	limb.scenes.destroyScene(self)
	self = nil
end

function Scene:boot(present)
	-- log.info('[boot]', self._name)
	if self.conf then
		self:conf()
	end
	self:on_load()
	self:enable()
	self._loaded = true
end

function Scene:disable()
	-- log.info('[disable]', self._name)
	self._enabled = false
	self._thread:pause()
end

function Scene:enable()
	-- log.info('[enable]', self._name)
	self._enabled = true
	self._thread:resume()
end

function Scene:suspend()
	-- log.info('[suspend]', self._name)
	self:setVisible(false)
	self:disable()
	limb.scenes.popActive(self)
end

function Scene:awaken()
	-- log.info('[awaken]', self._name)
	self:setVisible(true)
	self:enable()
	limb.scenes.pushActive(self)
end

function Scene:update(dt)
	-- log.info(self:getName()..':update()', dt)
end

function Scene:render()
	if not self._visible then return end

	local list = self._layers.by_order
	local process = 1
	local put = 1

	g.push('all')
	g.applyTransform(self._transform)
	-- g.setColor(g.getBackgroundColor())
	-- g.rectangle('fill', 0,0, 1920, 1080)
	while true do
		local element = list[process]
		if not element then break end
		list[process] = nil
		if element._visible and element._drawable then
			element:render()
			list[put] = element
			put = put + 1
		elseif not element._drawable then
			local name = element:getName()
			self._layers.by_name[name] = nil
			element:release()
		end
		process = process + 1
	end
	g.pop()
end

function Scene:setVisible(state)
	self._visible = state
	if not self._presented and state then
		self:present()
		self._presented = true
	end
end

function Scene:addLayer(index, name, usedepth)
	local l = layer(name, usedepth)
	local pos = index or #self._layers.by_order + 1
	self._layers.by_name[name] = l
	table.insert(self._layers.by_order, pos, l)
end

function Scene:addLayers(list)
	for index, data in ipairs(list) do
		if type(data) == 'string' then
			self:addLayer(index, data)
		elseif type(data) == 'table' then
			self:addLayer(index, data[1], data.usedepth)
		end
	end
end

function Scene:getLayer(name)
	return self._layers.by_name[name] or error('Not found layer ' .. name, 2)
end

function Scene:getName()
	return self._name
end

function Scene:getTransform()
	return self._transform
end

function Scene:isEnabled()
	return self._enabled
end

function Scene:isLoaded()
	return self._loaded
end

function Scene:conf(t)
	-- implement
end

function Scene:present()
	-- implement
end

function Scene:on_destroy()
	-- implement
end

function Scene:resize(w, h)
	-- implement
end

return Scene
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
