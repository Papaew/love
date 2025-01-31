R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.

local layer_cls = require('limb.common.layer')

local _M = {}

function _M.process()
	local list = limb.app.layers.by_order
	local process = 1
	local put = 1

	while true do
		local element = list[process]
		if not element then return end
		list[process] = nil
		if element._visible and element._drawable then
			element:render()
			list[put] = element
			put = put + 1
		elseif not element._drawable then
			local name = element:getName()
			limb.app.layers.by_name[name] = nil
			element:release()
		end
		process = process + 1
	end
end

function _M.addLayer(index, name, usedepth)
	local l = layer_cls(name, usedepth)
	local pos = index or #limb.app.layers.by_order + 1
	limb.app.layers.by_name[name] = l
	table.insert(limb.app.layers.by_order, pos, l)
end

function _M.addLayers(list)
	for index, data in ipairs(list) do
		if type(data) == 'string' then
			_M.addLayer(index, data)
		elseif type(data) == 'table' then
			_M.addLayer(index, data[1], data.usedepth)
		end
	end
end

function _M.getLayer(name)
	return limb.app.layers.by_name[name] or error('Not found layer ' .. name, 2)
end

function _M.resize(w, h)
	for _, layer in pairs(limb.app.layers.by_name) do
		layer:resize(w, h)
	end
end

return _M

-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
