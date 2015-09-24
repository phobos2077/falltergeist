--
-- Copyright 2012-2015 Falltergeist Developers.
--
-- This file is part of Falltergeist.
--
-- Falltergeist is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- Falltergeist is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
-- 
-- You should have received a copy of the GNU General Public License
-- along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
--

local ImageButton = class "ImageButton"

ImageButton:wrapEngineClass(game.ui.ImageButton)

---
-- @param state A state instance table
-- @param ... Constructor arguments for this control
--
function ImageButton:initialize(state, options)
    if options.position then
        options.x, options.y  = options.position.x, options.position.y
    end
    self.obj = game.ui.ImageButton.new(state.obj, options.upImg or "", options.downImg or "", options.upSfx or "", options.downSfx or "", options.x or "", options.y or "")
end

local function _buttonType(name, params)
    ImageButton.static[name] = class("ImageButton." .. name, ImageButton)
    ImageButton.static[name].initialize = function(self, state, x, y)
        params.x = x
        params.y = y
        ImageButton.initialize(self, state, params)
    end
end

_buttonType("BigRed", {
    upImg = "art/intrface/bigredup.frm",
    downImg = "art/intrface/bigreddn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm"
})

_buttonType("LittleRed", {
    upImg = "art/intrface/lilredup.frm",
    downImg = "art/intrface/lilreddn.frm",
    downSfx = "sound/sfx/ib1p1xx1.acm",
    upSfx = "sound/sfx/ib1lu1x1.acm"
})

_buttonType("Menu", {
    upImg = "art/intrface/menuup.frm",
    downImg = "art/intrface/menudown.frm",
    downSfx = "sound/sfx/nmselec0.acm",
    upSfx = "sound/sfx/nmselec1.acm"
})

_buttonType("ToggleSkill", {
    upImg = "art/intrface/tgskloff.frm",
    downImg = "art/intrface/tgsklon.frm"
})

_buttonType("Plus", {
    upImg = "art/intrface/splsoff.frm",
    downImg = "art/intrface/splson.frm"
})

_buttonType("Minus", {
    upImg = "art/intrface/snegoff.frm",
    downImg = "aart/intrface/snegoff.frm"
})

_buttonType("LeftArrow", {
    upImg = "art/intrface/slu.frm",
    downImg = "art/intrface/slu.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm"
})

_buttonType("RightArrow", {
    upImg = "art/intrface/sru.frm",
    downImg = "art/intrface/srd.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm"
})

-- TODO: move checkbox to separate C++ control?
_buttonType("Checkbox", {
    upImg = "art/intrface/prfxout.frm",
    downImg = "art/intrface/prfxout.frm",
    upSfx = "sound/sfx/ib2p1xx1.acm",
    checkbox = true
})

_buttonType("Name", {
    upImg = "art/intrface/nameoff.frm",
    downImg = "art/intrface/nameon.frm"
})

_buttonType("Age", {
    upImg = "art/intrface/nameoff.frm",
    downImg = "art/intrface/nameon.frm"
})

_buttonType("Gender", {
    upImg = "art/intrface/nameoff.frm",
    downImg = "art/intrface/nameon.frm"
})

_buttonType("Inventory", {
	upImg = "art/intrface/invbutup.frm",
	downImg = "art/intrface/invbutdn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm",
})

_buttonType("Options", {
	upImg = "art/intrface/optiup.frm",
	downImg = "art/intrface/optidn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm",
})

_buttonType("Attack", {
	upImg = "art/intrface/sattkbup.frm",
	downImg = "art/intrface/sattkbdn.frm",
    downSfx = "sound/sfx/ib3p1xx1.acm",
    upSfx = "sound/sfx/ib3lu1x1.acm",
})

_buttonType("Map", {
	upImg = "art/intrface/mapup.frm",
	downImg = "art/intrface/mapdn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm",
})

_buttonType("Cha", {
	upImg = "art/intrface/chaup.frm",
	downImg = "art/intrface/chadn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm",
})

_buttonType("Pip", {
	upImg = "art/intrface/pipup.frm",
	downImg = "art/intrface/pipdn.frm",
    downSfx = "sound/sfx/ib2p1xx1.acm",
    upSfx = "sound/sfx/ib2lu1x1.acm",
})

_buttonType("OptionsBtn", {
	upImg = "art/intrface/opbtnoff.frm",
	downImg = "art/intrface/opbtnon.frm",
    downSfx = "sound/sfx/ib3p1xx1.acm",
    upSfx = "sound/sfx/ib3lu1x1.acm",
})

_buttonType("Skilldex", {
	upImg = "art/intrface/skldxoff.frm",
	downImg = "art/intrface/skldxon.frm",
    downSfx = "sound/sfx/ib2lu1x1.acm",
    upSfx = "sound/sfx/ib1p1xx1.acm",
})

_buttonType("INVENTORY_UP_ARROW", {
	upImg = "art/intrface/invupout.frm",
	downImg = "art/intrface/invupin.frm"
})

_buttonType("INVENTORY_DOWN_ARROW", {
	upImg = "art/intrface/invdnout.frm",
	downImg = "art/intrface/invdnin.frm"
})

_buttonType("PIPBOY_ALARM_BUTTON", {
	upImg = "art/intrface/alarmout.frm",
	downImg = "art/intrface/alarmin.frm"
})

_buttonType("DIALOG_RED_BUTTON", {
	upImg = "art/intrface/di_rdbt2.frm",
	downImg = "art/intrface/di_rdbt1.frm"
})

_buttonType("DIALOG_REVIEW_BUTTON", {
	upImg = "art/intrface/di_rest1.frm",
	downImg = "art/intrface/di_rest2.frm"
})

_buttonType("DIALOG_DONE_BUTTON", {
	upImg = "art/intrface/di_done1.frm",
	downImg = "art/intrface/di_done2.frm"
})

_buttonType("DIALOG_BIG_UP_ARROW", {
	upImg = "art/intrface/di_bgup1.frm",
	downImg = "art/intrface/di_bgup2.frm"
})

_buttonType("DIALOG_BIG_DOWN_ARROW", {
	upImg = "art/intrface/di_bgdn1.frm",
	downImg = "art/intrface/di_bgdn2.frm"
})

_buttonType("DIALOG_UP_ARROW", {
	upImg = "art/intrface/di_up1.frm",
	downImg = "art/intrface/di_up2.frm"
})

_buttonType("DIALOG_DOWN_ARROW", {
	upImg = "art/intrface/di_down1.frm",
	downImg = "art/intrface/di_down2.frm"
})

_buttonType("SMALL_UP_ARROW", {
	upImg = "art/intrface/uparwoff.frm",
	downImg = "art/intrface/uparwon.frm"
})

_buttonType("SMALL_DOWN_ARROW", {
	upImg = "art/intrface/dnarwoff.frm",
	downImg = "art/intrface/dnarwon.frm"
})

_buttonType("MAP_HOTSPOT", {
	upImg = "art/intrface/hotspot1.frm",
	downImg = "art/intrface/hotspot2.frm"
})


return ImageButton
