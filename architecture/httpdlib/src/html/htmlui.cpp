/*

  Copyright (C) 2012 Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include "htmlui.h"
#include "htmlfactory.h"

htmlui::htmlui(const char *name, const char* address, int port) 
					: fFactory(0) { fFactory = new httpdfaust::htmlfactory(name, address, port); }
htmlui::~htmlui() { delete fFactory; }

void htmlui::openFrameBox(const char* label)		{ fFactory->opengroup( "framebox", label); }
void htmlui::openTabBox(const char* label)			{ fFactory->opengroup( "tabbox", label); }
void htmlui::openHorizontalBox(const char* label)	{ fFactory->opengroup( "horizontalbox", label); }
void htmlui::openVerticalBox(const char* label)		{ fFactory->opengroup( "verticalbox", label); }
void htmlui::closeBox()								{ fFactory->closegroup(); }

void htmlui::addButton(const char* label, float*)
					{ fFactory->addnode( "button", label); }
void htmlui::addToggleButton(const char* label, float*)
					{ fFactory->addnode( "togglebutton", label); }
void htmlui::addCheckButton(const char* label, float*)
					{ fFactory->addnode( "checkbutton", label); }

void htmlui::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "verticalslider", label, init, min, max, step); }
void htmlui::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "horizontalslider", label, init, min, max, step); }
void htmlui::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
					{ fFactory->addnode( "numentry", label, init, min, max, step); }

void htmlui::addNumDisplay(const char* label, float* zone, int precision) {}
void htmlui::addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {}
void htmlui::addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
void htmlui::addVerticalBargraph(const char* label, float* zone, float min, float max) {}
