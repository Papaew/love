R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.

return function(baseclass)
	-- "Class" is the new class
	local Class = {}
	local base = baseclass or {}
	-- copy base class contents into the new class
	for key, value in pairs(base) do
		Class[key] = value
	end

	Class.__index = Class
	Class.baseclass = base

	setmetatable(Class, {
		__call = function(c, ...)
			local instance = setmetatable({}, c)
			local init = instance.init
			if init then init(instance, ...) end
			return instance
		end
	})

	return Class
end

-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
