R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
limb.renderer = require('limb.renderer')
limb.thread = require('limb.thread')
limb.scenes = require('limb.scenes')
limb.callbacks = require('limb.callbacks')
limb.app = {
	handlers = {},
	threads = {},
	scenes = {
		active = {},
		cached = {}
	},
	layers = {
		by_name = {},
		by_order = {}
	}
}

limb.boot = function(c)
	local g = love.graphics
	g.setLineWidth(1)
	g.setPointSize(1)
	g.setLineStyle('rough')
	g.setDefaultFilter('nearest', 'nearest', 16)
	g.setBackgroundColor(0, 0, 0, 1)

	love.setDeprecationOutput(c.showDeprecationOutput)
	love.filesystem.setIdentity(c.identity, c.appendToPath)
	love.keyboard.setKeyRepeat(c.keyRepeatEnabled)

	-- log:conf(c.logging)

	limb.callbacks.init()
	limb.renderer.addLayers(c.layers)
end
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
