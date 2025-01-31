R"luastring"--(
-- DO NOT REMOVE THE ABOVE LINE. It is used to load this file as a C++ string.
-- There is a matching delimiter at the bottom of the file.

local class = require('class')

local Drawable = class()

function Drawable:init()
	self._visible = true
	self._drawable = true
end

function Drawable:setVisible(state)
	self._visible = state
end

function Drawable:isVisible() return self._visible end
function Drawable:isDrawable() return self._drawable end

return Drawable

-- DO NOT REMOVE THE NEXT LINE. It is used to load this file as a C++ string.
--)luastring"--"
