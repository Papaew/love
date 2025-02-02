R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.
local callback_cls = require('limb.common.callback')

local _M = {}

function _M.init()
	for _,name in ipairs {
		'on_key_down',
		'on_key_up',
		'on_text_input',
		'on_text_edited',
		'on_mouse_move',
		'on_mouse_down',
		'on_mouse_up',
		'on_mouse_wheel',
		'on_touch_move',
		'on_touch_down',
		'on_touch_up',
	} do
		limb.app.handlers[name] = {}
	end
end

function _M.attachEventListener(handler, state, object, cb)
	local cb_name = 'on_' .. handler .. '_' .. state
	if not limb.app.handlers[cb_name] then
		limb.app.handlers[cb_name] = {}
	end
	limb.app.handlers[cb_name][object] = callback_cls(object, cb)
end

function _M.detachEventListener(handler, state, object)
	local cb_name = 'on_' .. handler .. '_' .. state
	if limb.app.handlers[cb_name] then
		limb.app.handlers[cb_name][object] = nil
	end
end

function _M.getEventListener(handler, state, object)
	local cb_name = 'on_' .. handler .. '_' .. state
	return limb.app.handlers[cb_name][object]
end

limb.keypressed = function(key, scancode, isrepeat)
	if key == 'escape' and love.system.getOS() ~= 'Web' then love.event.quit() end

	for _,cb in pairs(limb.app.handlers['on_key_down']) do
		cb:call(key, scancode, isrepeat)
	end
end

limb.keyreleased = function(key, scancode)
	for _,cb in pairs(limb.app.handlers['on_key_up']) do
		cb:call(key, scancode)
	end
end

limb.textinput = function(text)
	for _,cb in pairs(limb.app.handlers['on_text_input']) do
		cb:call(text)
	end
end

limb.textedited = function(text, start, length)
	for _,cb in pairs(limb.app.handlers['on_text_edited']) do
		cb:call(text, start, length)
	end
end

limb.mousemoved = function(x, y, dx, dy, istouch)
	for _,cb in pairs(limb.app.handlers['on_mouse_move']) do
		cb:call(dx, dy, x, y, istouch)
	end
end

limb.mousepressed = function(x, y, key, istouch, presses)
	for _,cb in pairs(limb.app.handlers['on_mouse_down']) do
		cb:call(key, x, y, presses, istouch)
	end
end

limb.mousereleased = function(x, y, key, istouch, presses)
	for _,cb in pairs(limb.app.handlers['on_mouse_up']) do
		cb:call(key, x, y, presses, istouch)
	end
end

limb.wheelmoved = function(x, y, px, py, dir)
	for _,cb in pairs(limb.app.handlers['on_mouse_wheel']) do
		cb:call(x, y, px, py, dir)
	end
end

limb.touchpressed = function(id, x, y, dx, dy, pressure)
	for _,cb in pairs(limb.app.handlers['on_touch_down']) do
		cb:call(id, x, y, dx, dy, pressure)
	end
end

limb.touchreleased = function(id, x, y, dx, dy, pressure)
	for _,cb in pairs(limb.app.handlers['on_touch_up']) do
		cb:call(id, x, y, dx, dy, pressure)
	end
end

limb.touchmoved = function(id, x, y, dx, dy, pressure)
	for _,cb in pairs(limb.app.handlers['on_touch_move']) do
		cb:call(id, x, y, dx, dy, pressure)
	end
end

limb.joystickpressed = function(j, b)
end

limb.joystickreleased = function(j, b)
end

limb.joystickaxis = function(j, a, v)
end

limb.joystickhat = function(j, h, v)
end

limb.gamepadpressed = function(j, b)
end

limb.gamepadreleased = function(j, b)
end

limb.gamepadaxis = function(j, a, v)
end

limb.joystickadded = function(j)
end

limb.joystickremoved = function(j)
end

limb.joysticksensorupdated = function(j, sensorType, x, y, z)
end

limb.focus = function(f)
end

limb.mousefocus = function(f)
end

limb.visible = function(v)
end

limb.exposed = function()
end

limb.occluded = function()
end

limb.quit = function()
	return
end

limb.threaderror = function(t, err)
end

limb.resize = function(w, h)
end

limb.filedropped = function(f, x, y)
end

limb.directorydropped = function(dir, x, y)
end

limb.dropbegan = function()
end

limb.dropmoved = function(x, y)
end

limb.dropcompleted = function(x, y)
end

limb.lowmemory = function()
	if love.lowmemory then love.lowmemory() end
	collectgarbage()
	collectgarbage()
end

limb.displayrotated = function(display, orient)
end

limb.localechanged = function()
end

limb.audiodisconnected = function(sources)
	if not love.audiodisconnected or not love.audiodisconnected(sources) then
		love.audio.setPlaybackDevice()
	end
end

limb.sensorupdated = function(sensorType, x, y, z)
	if love.sensorupdated then return love.sensorupdated(sensorType, x, y, z) end
end

return _M
-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
