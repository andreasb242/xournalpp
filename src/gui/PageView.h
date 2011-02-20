/*
 * Xournal++
 *
 * Displays a single page
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __PAGEVIEW_H__
#define __PAGEVIEW_H__

#include <gtk/gtk.h>

#include "../model/Page.h"
#include "../model/Stroke.h"
#include "../model/Text.h"

#include "../control/settings/Settings.h"
#include "../control/SearchControl.h"
#include "../control/tools/VerticalToolHandler.h"
#include "../control/tools/EraseHandler.h"
#include "../control/tools/InputHandler.h"
#include "../view/DocumentView.h"
#include "../gui/TextEditor.h"
#include "../util/Util.h"

class XournalWidget;
class DeleteUndoAction;
class Selection;

class Rectangle;

class PageView: public Redrawable, public virtual MemoryCheckObject {
public:
	PageView(XournalWidget * xournal, XojPage * page);
	virtual ~PageView();

	double getHeight();
	double getWidth();

	int getDisplayWidth();
	int getDisplayHeight();

	void updatePageSize(double width, double height);

	void firstPaint();
	bool paintPage(GtkWidget *widget, GdkEventExpose *event, double zoom);
	void repaintRectangle(Rectangle * rect, double zoom);

	void repaint();
	void repaint(Element * e);
	void repaint(Range & r);
	void repaint(double x, double y, double width, double heigth);

	void redraw();

	void updateSize();

	XojPage * getPage();

	GtkWidget * getWidget();

	XournalWidget * getXournal();

	void setSelected(bool selected);
	void updateXEvents();

	virtual void deleteViewBuffer();

	void setIsVisibel(bool visibel);

	bool isSelected();

	void endText();

	bool searchTextOnPage(const char * text, int * occures, double * top);

	bool onKeyPressEvent(GdkEventKey *event);
	bool onKeyReleaseEvent(GdkEventKey *event);

	bool cut();
	bool copy();
	bool paste();

	bool actionDelete();

	int getLastVisibelTime();

	int getBufferPixels();

	TextEditor * getTextEditor();

	void resetShapeRecognizer();

public:
	// Redrawable
	void redrawDocumentRegion(double x1, double y1, double x2, double y2);
	GdkColor getSelectionColor();
private:
	static gboolean exposeEventCallback(GtkWidget * widget, GdkEventExpose * event, PageView * page);
	static gboolean onButtonPressEventCallback(GtkWidget * widget, GdkEventButton * event, PageView * view);
	void onButtonPressEvent(GtkWidget * widget, GdkEventButton * event);
	static bool onButtonReleaseEventCallback(GtkWidget * widget, GdkEventButton * event, PageView * view);
	bool onButtonReleaseEvent(GtkWidget * widget, GdkEventButton * event);
	static gboolean onMotionNotifyEventCallback(GtkWidget * widget, GdkEventMotion * event, PageView * view);
	gboolean onMotionNotifyEvent(GtkWidget * widget, GdkEventMotion * event);

	static gboolean onMouseEnterNotifyEvent(GtkWidget * widget, GdkEventCrossing * event, gpointer user_data);
	static gboolean onMouseLeaveNotifyEvent(GtkWidget * widget, GdkEventCrossing * event, gpointer user_data);

	void handleScrollEvent(GdkEventButton * event);

	void startText(double x, double y);
	void selectObjectAt(double x, double y);

	void doScroll(GdkEventMotion * event);
	static bool scrollCallback(PageView * view);

	void repaintLater();
	static bool repaintCallback(PageView * view);

	void insertImage(double x, double y);

	void fixXInputCoords(GdkEvent * event);

	void addRepaintRect(double x, double y, double width, double height);
private:
	XojPage * page;
	GtkWidget * widget;
	XournalWidget * xournal;
	Settings * settings;
	EraseHandler * eraser;
	InputHandler * inputHandler;

	/**
	 * The selected (while selection)
	 */
	Selection * selectionEdit;

	/**
	 * The last Mouse Position, for scrolling
	 */
	int lastMousePositionX;
	int lastMousePositionY;

	int scrollOffsetX;
	int scrollOffsetY;

	bool inScrolling;

	/**
	 * The View to draw the page
	 */
	DocumentView * view;

	/**
	 * The text editor View
	 */
	TextEditor * textEditor;

	bool firstPainted;
	bool selected;

	cairo_surface_t * crBuffer;
	int idleRepaintId;

	bool inEraser;

	bool extendedWarningDisplayd;

	// Vertical Space
	VerticalToolHandler * verticalSpace;

	/**
	 * Search handling
	 */
	SearchControl * search;

	/**
	 * Unixtimestam when the page was last time in the visibel area
	 */
	int lastVisibelTime;

	GList * repaintRect;

	friend class InsertImageRunnable;
};

class Rectangle {
public:
	Rectangle();
	Rectangle(double x, double y, double width, double height);
public:

	/**
	 * @src1: a #Rectangle
	 * @src2: a #Rectangle
	 * @dest: return location for the intersection of @src1 and @src2, or %NULL
	 *
	 * Calculates the intersection of two rectangles. It is allowed for
	 * @dest to be the same as either @src1 or @src2. If the rectangles
	 * do not intersect, @dest's width and height is set to 0 and its x
	 * and y values are undefined. If you are only interested in whether
	 * the rectangles intersect, but not in the intersecting area itself,
	 * pass %NULL for @dest.
	 *
	 * Returns: %TRUE if the rectangles intersect.
	 */
	bool intersect(const Rectangle * src, Rectangle * dest);

public:
	double x;
	double y;
	double width;
	double height;
};

#endif /* __PAGEVIEW_H__ */
