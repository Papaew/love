R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.

local class = require('class')
local g = love.graphics

local layer = class()

function layer:init(name, usedepth)
	self._name = name
	self._canvas = {}
	self._objects = {}
	self._usedepth = usedepth or false
	self._transform = love.math.newTransform()
	self._drawable = true
	self._visible = true
	self._opacity = 1.0

	self:resize(g.getDimensions())
end

function layer:release()
	self._drawable = false
	self._visible = false
	self._transform:release()
	for _,obj in pairs(self._objects) do
		obj:release()
	end
	for _,canvas in pairs(self._canvas) do
		canvas:release()
	end
	if self._usedepth then
		self._canvas.depthstencil:release()
	end
	self._objects = nil
	self = nil
end

function layer:addObject(object)
	if object.layer then
		error("Object already added to layer '"..self:getName().."'", 2)
		return false
	end

	rawset(self._objects, object, object)
	object.layer = self
	return true
end

function layer:removeObject(object)
	object.layer = nil
	rawset(self._objects, object, nil)
	return type(self._objects[object]) ~= 'nil'
end

function layer:render()
	g.push('all')
		g.setCanvas(self._canvas)
			if self._usedepth then
				g.clear(true, false, 0)
				g.setDepthMode("greater", true)
			else
				g.clear(true, false, false)
				g.setDepthMode("always", false)
				g.setBlendMode('alpha')
			end
			g.origin()
			g.applyTransform(self._transform)
			for _,obj in pairs(self._objects) do
				if obj._visible and obj._drawable then
					obj:render()
				end
			end
		g.setCanvas()
	g.pop()

	g.push('all')
		g.setColor(1,1,1, self._opacity)
		g.setBlendMode('alpha', 'premultiplied')
		g.draw(self._canvas[1])
	g.pop()
end

function layer:resize(w, h)
	self._canvas[1] = g.newCanvas(w, h, { format = "normal" })

	if self._usedepth then
		self._canvas.depthstencil = g.newCanvas(w, h, {format = "depth16"})
	end
end

function layer:setTransform(t)
	self._transform = t
end

function layer:setVisible(state)
	self._visible = state
end

function layer:setOpacity(value)
	self._opacity = value
end

function layer:getTransform()
	return self._transform
end

function layer:getOpacity()
	return self._opacity
end

function layer:getName() return self._name end
function layer:isUseDepth() return self._usedepth end

return layer

-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
