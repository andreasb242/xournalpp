/*
 * Xournal++
 *
 * Configuration for Mouse Buttons, Eraser and default configuration
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "control/Tool.h"

#include <StringUtils.h>
#include <XournalType.h>

enum DrawingType
{
	DRAWING_TYPE_DONT_CHANGE = 0,
	DRAWING_TYPE_RULER,
	DRAWING_TYPE_RECTANGLE,
	DRAWING_TYPE_CIRCLE,
	DRAWING_TYPE_ARROW,
	DRAWING_TYPE_STROKE_RECOGNIZER,
	DRAWING_TYPE_NONE
};

class ToolHandler;

class ButtonConfig
{
public:
	ButtonConfig(ToolType action, int color, ToolSize size, DrawingType drawingType, EraserType eraserMode);
	virtual ~ButtonConfig();

public:
	void acceptActions(ToolHandler* toolHandler);
	ToolType getAction();
	bool getDisableDrawing();
	bool getDisableTouchDeviceOnPenContact();
	DrawingType getDrawingType();

private:
	XOJ_TYPE_ATTRIB;


	ToolType action;
	int color;
	ToolSize size;
	EraserType eraserMode;
	DrawingType drawingType;

	bool disableDrawing;
	bool disableTouchDeviceOnPenContact;

public:
	string device;

	friend class Settings;
	friend class ButtonConfigGui;
};
