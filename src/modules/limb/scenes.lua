R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local scene_cls = require('limb.common.scene')

local _M = {}

function _M.newScene(name)
	local sc = scene_cls(name)
	limb.app.scenes.cached[name] = sc
	return sc
end

function _M.pushActive(scene)
	local name = scene:getName()
	for _, v in ipairs(limb.app.scenes.active) do
		if v:getName() == name then
			error("Attempt to move scene duplicate to active stack", 2)
		end
	end
	table.insert(limb.app.scenes.active, scene)
end

function _M.popActive(scene)
	local name = scene:getName()
	for i, v in ipairs(limb.app.scenes.active) do
		if v:getName() == name then
			return table.remove(limb.app.scenes.active, i)
		end
	end
end

function _M.presentScene(name)
	local scene = _M.findScene(name) or error('Not found scene ' .. name, 2)
	_M.pushActive(scene)
	if not scene._loaded then
		scene:boot(true)
	end
	scene:present()
	limb.renderer.getLayer('scene'):addObject(scene)
end

function _M:destroyScene(scene)
	_M.popActive(scene)
	limb.app.scenes.cached[scene:getName()] = nil
end

function _M.render()
	for i, v in ipairs(limb.app.scenes.active) do
		v:render()
	end
end

function _M.resize(w, h)
	for _, v in ipairs(limb.app.scenes.active) do
		v:resize(w, h)
	end
end

function _M.findScene(name)
	return limb.app.scenes.cached[name]
end

return _M
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
