
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::tablelayout;

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::invalidate ();

abstract public void invalidateHierarchy ();

/** The position within it's parent and size of the widget that will be laid out. Must be set before layout. */
public void setLayoutSize (int tableLayoutX, int tableLayoutY, int tableLayoutWidth, int tableLayoutHeight) {
    this.layoutX = tableLayoutX;
    this.layoutY = tableLayoutY;
    this.layoutWidth = tableLayoutWidth;
    this.layoutHeight = tableLayoutHeight;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::invalidateHierarchy ();

/** The position within it's parent and size of the widget that will be laid out. Must be set before layout. */
public void setLayoutSize (int tableLayoutX, int tableLayoutY, int tableLayoutWidth, int tableLayoutHeight) {
    this.layoutX = tableLayoutX;
    this.layoutY = tableLayoutY;
    this.layoutWidth = tableLayoutWidth;
    this.layoutHeight = tableLayoutHeight;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::setLayoutSize (int tableLayoutX,int tableLayoutY,int tableLayoutWidth,int tableLayoutHeight) {
    this.layoutX = tableLayoutX;
    this.layoutY = tableLayoutY;
    this.layoutWidth = tableLayoutWidth;
    this.layoutHeight = tableLayoutHeight;
}

C& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::register (const std::string& name,const C& widget) {
    name = name.toLowerCase();
    if (nameToWidget.containsKey(name)) throw new IllegalArgumentException("Name is already used: " + name);
    nameToWidget.put(name, widget);
    return widget;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::parse (const std::string& tableDescription) {
    TableLayoutParser.parse(this, tableDescription);
}

Cell<C>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::add (const C& widget) { // BOZO - Add column description parsing.
    Cell cell = new Cell(this);
    cell.widget = widget;

    // BOZO - Fix widget being null!

    widgetToCell.put(widget, cell);

for (Entry<String, C> entry : nameToWidget.entrySet()) {
        if (widget == entry.getValue()) {
            cell.name = entry.getKey();
            break;
        }
    }

    if (cells.size() > 0) {
        // Set cell x and y.
        Cell lastCell = cells.get(cells.size() - 1);
        if (!lastCell.endRow) {
            cell.column = lastCell.column + lastCell.colspan;
            cell.row = lastCell.row;
        } else
            cell.row = lastCell.row + 1;
        // Set the index of the cell above.
        if (cell.row > 0) {
outer:
            for (int i = cells.size() - 1; i >= 0; i--) {
                Cell other = cells.get(i);
                for (int column = other.column, nn = column + other.colspan; column < nn; column++) {
                    if (other.column == cell.column) {
                        cell.cellAboveIndex = i;
                        break outer;
                    }
                }
            }
        }
    }
    cells.add(cell);

    if (cell.column < columnDefaults.size()) {
        Cell columnDefaults = this.columnDefaults.get(cell.column);
        cell.set(columnDefaults != null ? columnDefaults : cellDefaults);
    } else
        cell.set(cellDefaults);
    cell.merge(rowDefaults);

    toolkit.addChild(table, widget, null);

    return cell;
}

Cell& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::row () {
    if (cells.size() > 0) endRow();
    rowDefaults = new Cell(this);
    return rowDefaults;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::endRow () {
    int rowColumns = 0;
    for (int i = cells.size() - 1; i >= 0; i--) {
        Cell cell = cells.get(i);
        if (cell.endRow) break;
        rowColumns += cell.colspan;
    }
    columns = Math.max(columns, rowColumns);
    rows++;
    cells.get(cells.size() - 1).endRow = true;
}

Cell& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::columnDefaults (int column) {
    Cell cell = columnDefaults.size() > column ? columnDefaults.get(column) : null;
    if (cell == null) {
        cell = new Cell(this);
        cell.set(cellDefaults);
        if (column <= columnDefaults.size()) {
            for (int i = columnDefaults.size(); i < column; i++)
                columnDefaults.add(null);
            columnDefaults.add(cell);
        } else
            columnDefaults.set(column, cell);
    }
    return cell;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::reset () {
    clear();
    padTop = null;
    padLeft = null;
    padBottom = null;
    padRight = null;
    align = CENTER;
    if (debug != DEBUG_NONE) toolkit.clearDebugRectangles(this);
    debug = DEBUG_NONE;
    cellDefaults.set(Cell.defaults(this));
    columnDefaults.clear();
    rowDefaults = null;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::clear () {
    for (int i = cells.size() - 1; i >= 0; i--)
        toolkit.removeChild(table, (C)cells.get(i).widget);
    cells.clear();
    nameToWidget.clear();
    widgetToCell.clear();
    rows = 0;
    columns = 0;
}

C& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getWidget (const std::string& name) {
    return nameToWidget.get(name.toLowerCase());
}

std::list<C>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getWidgets () {
    return new ArrayList(nameToWidget.values());
}

std::list<C>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getWidgets (const std::string& namePrefix) {
    ArrayList<C> widgets = new ArrayList();
for (Entry<String, C> entry : nameToWidget.entrySet())
        if (entry.getKey().startsWith(namePrefix)) widgets.add(entry.getValue());
    return widgets;
}

Cell& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getCell (const C& widget) {
    return widgetToCell.get(widget);
}

Cell& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getCell (const std::string& name) {
    return getCell(getWidget(name));
}

std::list<Cell>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getAllCells () {
    return new ArrayList(widgetToCell.values());
}

std::list<Cell>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getAllCells (const std::string& namePrefix) {
    ArrayList<Cell> cells = new ArrayList();
for (Cell cell : widgetToCell.values())
        if (cell.name.startsWith(namePrefix)) cells.add(cell);
    return cells;
}

std::list<Cell>& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getCells () {
    return cells;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::setWidget (const std::string& name,const C& widget) {
    getCell(name).setWidget(widget);
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::setParent (const BaseTableLayout& parent) {
    // Shared per table hierarchy.
    nameToWidget = parent.nameToWidget;
    widgetToCell = parent.widgetToCell;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::setToolkit (const K& toolkit) {
    this.toolkit = toolkit;
}

T& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getTable () {
    return table;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::setTable (const T& table) {
    this.table = table;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getLayoutX () {
    return layoutX;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getLayoutY () {
    return layoutY;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getLayoutWidth () {
    return layoutWidth;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getLayoutHeight () {
    return layoutHeight;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getMinWidth () {
    return tableMinWidth;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getMinHeight () {
    return tableMinHeight;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPrefWidth () {
    return tablePrefWidth;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPrefHeight () {
    return tablePrefHeight;
}

Cell& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::defaults () {
    return cellDefaults;
}

K& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getToolkit () {
    return toolkit;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::size (const std::string& width,const std::string& height) {
    this.width = width;
    this.height = height;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::width (const std::string& width) {
    this.width = width;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::height (const std::string& height) {
    this.height = height;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::size (int width,int height) {
    this.width = String.valueOf(width);
    this.height = String.valueOf(height);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::width (int width) {
    this.width = String.valueOf(width);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::height (int height) {
    this.height = String.valueOf(height);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::pad (const std::string& pad) {
    padTop = pad;
    padLeft = pad;
    padBottom = pad;
    padRight = pad;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::pad (const std::string& top,const std::string& left,const std::string& bottom,const std::string& right) {
    padTop = top;
    padLeft = left;
    padBottom = bottom;
    padRight = right;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padTop (const std::string& padTop) {
    this.padTop = padTop;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padLeft (const std::string& padLeft) {
    this.padLeft = padLeft;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padBottom (const std::string& padBottom) {
    this.padBottom = padBottom;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padRight (const std::string& padRight) {
    this.padRight = padRight;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::pad (int pad) {
    padTop = String.valueOf(pad);
    padLeft = String.valueOf(pad);
    padBottom = String.valueOf(pad);
    padRight = String.valueOf(pad);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::pad (int top,int left,int bottom,int right) {
    padTop = String.valueOf(top);
    padLeft = String.valueOf(left);
    padBottom = String.valueOf(bottom);
    padRight = String.valueOf(right);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padTop (int padTop) {
    this.padTop = String.valueOf(padTop);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padLeft (int padLeft) {
    this.padLeft = String.valueOf(padLeft);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padBottom (int padBottom) {
    this.padBottom = String.valueOf(padBottom);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::padRight (int padRight) {
    this.padRight = String.valueOf(padRight);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::align (int align) {
    this.align = align;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::align (const std::string& value) {
    align = 0;
    if (value.contains("center")) align |= CENTER;
    if (value.contains("left")) align |= LEFT;
    if (value.contains("right")) align |= RIGHT;
    if (value.contains("top")) align |= TOP;
    if (value.contains("bottom")) align |= BOTTOM;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::center () {
    align |= CENTER;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::top () {
    align |= TOP;
    align &= ~BOTTOM;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::left () {
    align |= LEFT;
    align &= ~RIGHT;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::bottom () {
    align |= BOTTOM;
    align &= ~TOP;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::right () {
    align |= RIGHT;
    align &= ~LEFT;
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::debug (int debug) {
    this.debug = debug;
    if (debug == DEBUG_NONE) toolkit.clearDebugRectangles(this);
    return (L)this;
}

L& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::debug (const std::string& value) {
    debug = 0;
    if (value == null) return (L)this;
    if (value.equalsIgnoreCase("true")) debug |= DEBUG_ALL;
    if (value.contains("all")) debug |= DEBUG_ALL;
    if (value.contains("cell")) debug |= DEBUG_CELL;
    if (value.contains("table")) debug |= DEBUG_TABLE;
    if (value.contains("widget")) debug |= DEBUG_WIDGET;
    if (debug == DEBUG_NONE) toolkit.clearDebugRectangles(this);
    return (L)this;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getDebug () {
    return debug;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getWidth () {
    return width;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getHeight () {
    return height;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPadTop () {
    return padTop;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPadLeft () {
    return padLeft;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPadBottom () {
    return padBottom;
}

std::string& BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getPadRight () {
    return padRight;
}

int BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::getAlign () {
    return align;
}

void BaseTableLayout<C, T extends C, L extends BaseTableLayout, K extends Toolkit>::layout () {
    Toolkit toolkit = this.toolkit;
    ArrayList<Cell> cells = this.cells;

    if (cells.size() > 0 && !cells.get(cells.size() - 1).endRow) endRow();

    // Determine minimum and preferred cell sizes. Also compute the combined padding/spacing for each cell.
    int[] columnMinWidth = new int[columns];
    int[] rowMinHeight = new int[rows];
    int[] columnPrefWidth = new int[columns];
    int[] rowPrefHeight = new int[rows];
    int spaceRightLast = 0;
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;

        // Spacing between widgets isn't additive, the larger is used. Also, no spacing around edges.
        c.padLeftTemp = c.column == 0 ? toolkit.width(this, c.padLeft) : toolkit.width(this, c.padLeft)
                        + Math.max(0, toolkit.width(this, c.spaceLeft) - spaceRightLast);
        c.padTopTemp = c.cellAboveIndex == -1 ? toolkit.height(this, c.padTop) : toolkit.height(this, c.padTop)
                       + Math.max(0, toolkit.height(this, c.spaceTop) - toolkit.height(this, cells.get(c.cellAboveIndex).spaceBottom));
        int spaceRight = toolkit.width(this, c.spaceRight);
        c.padRightTemp = c.column + c.colspan == columns ? toolkit.width(this, c.padRight) : toolkit.width(this, c.padRight)
                         + spaceRight;
        c.padBottomTemp = c.row == rows - 1 ? toolkit.height(this, c.padBottom) : toolkit.height(this, c.padBottom)
                          + toolkit.height(this, c.spaceBottom);
        spaceRightLast = spaceRight;

        int prefWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.prefWidth);
        int prefHeight = toolkit.getWidgetHeight(this, (C)c.widget, c.prefHeight);
        int minWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.minWidth);
        int minHeight = toolkit.getWidgetHeight(this, (C)c.widget, c.minHeight);
        if (prefWidth < minWidth) prefWidth = minWidth;
        if (prefHeight < minHeight) prefHeight = minHeight;

        if (c.colspan == 1) {
            int hpadding = c.padLeftTemp + c.padRightTemp;
            columnPrefWidth[c.column] = Math.max(columnPrefWidth[c.column], prefWidth + hpadding);
            columnMinWidth[c.column] = Math.max(columnMinWidth[c.column], minWidth + hpadding);
        }
        int vpadding = c.padTopTemp + c.padBottomTemp;
        rowPrefHeight[c.row] = Math.max(rowPrefHeight[c.row], prefHeight + vpadding);
        rowMinHeight[c.row] = Math.max(rowMinHeight[c.row], minHeight + vpadding);
    }

    // Determine maximum cell sizes using (preferred - min) size to weight distribution of extra space.
    tableMinWidth = 0;
    tableMinHeight = 0;
    tablePrefWidth = 0;
    tablePrefHeight = 0;
    for (int i = 0; i < columns; i++) {
        tableMinWidth += columnMinWidth[i];
        tablePrefWidth += columnPrefWidth[i];
    }
    for (int i = 0; i < rows; i++) {
        tableMinHeight += rowMinHeight[i];
        tablePrefHeight += Math.max(rowMinHeight[i], rowPrefHeight[i]);
    }
    int hpadding = toolkit.width(this, padLeft) + toolkit.width(this, padRight);
    int vpadding = toolkit.height(this, padTop) + toolkit.height(this, padBottom);
    int width = toolkit.width(this, this.width) - hpadding;
    int height = toolkit.height(this, this.height) - vpadding;
    tableMinWidth = Math.max(tableMinWidth + hpadding, width);
    tableMinHeight = Math.max(tableMinHeight + vpadding, height);
    tablePrefWidth = Math.max(tablePrefWidth + hpadding, tableMinWidth);
    tablePrefHeight = Math.max(tablePrefHeight + vpadding, tableMinHeight);

    int[] columnMaxWidth;
    int tableLayoutWidth = this.layoutWidth;
    int totalGrowWidth = tablePrefWidth - tableMinWidth;
    if (totalGrowWidth == 0)
        columnMaxWidth = columnMinWidth;
    else {
        int extraWidth = Math.max(0, tableLayoutWidth - tableMinWidth);
        columnMaxWidth = new int[columns];
        for (int i = 0; i < columns; i++) {
            int growWidth = columnPrefWidth[i] - columnMinWidth[i];
            float growRatio = growWidth / (float)totalGrowWidth;
            columnMaxWidth[i] = columnMinWidth[i] + (int)(extraWidth * growRatio);
        }
    }

    int[] rowMaxHeight;
    int tableLayoutHeight = this.layoutHeight;
    int totalGrowHeight = tablePrefHeight - tableMinHeight;
    if (totalGrowHeight == 0)
        rowMaxHeight = rowMinHeight;
    else {
        int extraHeight = Math.max(0, tableLayoutHeight - tableMinHeight);
        rowMaxHeight = new int[rows];
        for (int i = 0; i < rows; i++) {
            int growHeight = rowPrefHeight[i] - rowMinHeight[i];
            float growRatio = growHeight / (float)totalGrowHeight;
            rowMaxHeight[i] = rowMinHeight[i] + (int)(extraHeight * growRatio);
        }
    }

    // Determine widget and cell sizes (before uniform/expand/fill). Also collect columns/rows that expand.
    int[] columnWidth = new int[columns];
    int[] rowHeight = new int[rows];
    float[] expandWidth = new float[columns];
    float[] expandHeight = new float[rows];
    float totalExpandWidth = 0, totalExpandHeight = 0;
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;

        int spannedCellMaxWidth = 0;
        for (int column = c.column, nn = column + c.colspan; column < nn; column++) {
            spannedCellMaxWidth += columnMaxWidth[column];

            if (c.colspan == 1 && c.expandX != 0 && expandWidth[column] == 0) {
                expandWidth[column] = c.expandX / (float)c.colspan;
                totalExpandWidth += c.expandX / (float)c.colspan;
            }
        }
        spannedCellMaxWidth -= c.padLeftTemp + c.padRightTemp;
        if (c.expandY != 0 && expandHeight[c.row] == 0) {
            expandHeight[c.row] = c.expandY;
            totalExpandHeight += c.expandY;
        }

        int prefWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.prefWidth);
        int prefHeight = toolkit.getWidgetHeight(this, (C)c.widget, c.prefHeight);
        int minWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.minWidth);
        int minHeight = toolkit.getWidgetHeight(this, (C)c.widget, c.minHeight);
        if (prefWidth < minWidth) prefWidth = minWidth;
        if (prefHeight < minHeight) prefHeight = minHeight;

        c.widgetWidth = Math.min(spannedCellMaxWidth, prefWidth);
        c.widgetHeight = Math.min(rowMaxHeight[c.row] - c.padTopTemp - c.padBottomTemp, prefHeight);

        if (c.colspan == 1)
            columnWidth[c.column] = Math.max(columnWidth[c.column], c.widgetWidth + c.padLeftTemp + c.padRightTemp);
        rowHeight[c.row] = Math.max(rowHeight[c.row], c.widgetHeight + c.padTopTemp + c.padBottomTemp);
    }

    // Uniform cells are all the same width/height.
    int uniformMaxWidth = 0, uniformMaxHeight = 0;
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;
        if (c.uniformX != null) uniformMaxWidth = Math.max(uniformMaxWidth, columnWidth[c.column]);
        if (c.uniformY != null) uniformMaxHeight = Math.max(uniformMaxHeight, rowHeight[c.row]);
    }
    if (uniformMaxWidth > 0 || uniformMaxHeight > 0) {
outer:
        for (int i = 0, n = cells.size(); i < n; i++) {
            Cell c = cells.get(i);
            if (c.ignore) continue;
            if (uniformMaxWidth > 0 && c.uniformX != null) {
                int diff = uniformMaxWidth - columnWidth[c.column];
                if (diff > 0) {
                    columnWidth[c.column] = uniformMaxWidth;
                    tableMinWidth += diff;
                    tablePrefWidth += diff;
                }
            }
            if (uniformMaxHeight > 0 && c.uniformY != null) {
                int diff = uniformMaxHeight - rowHeight[c.row];
                if (diff > 0) {
                    rowHeight[c.row] = uniformMaxHeight;
                    tableMinHeight += diff;
                    tablePrefHeight += diff;
                }
            }
            continue outer;
        }
    }

    // Distribute remaining space to any expanding columns/rows.
    if (totalExpandWidth > 0) {
        int extra = Math.max(0, tableLayoutWidth - tablePrefWidth);
        int used = 0, lastIndex = 0;
        for (int i = 0; i < columns; i++) {
            if (expandWidth[i] == 0) continue;
            int amount = (int)(extra * expandWidth[i] / totalExpandWidth);
            columnWidth[i] += amount;
            used += amount;
            lastIndex = i;
        }
        columnWidth[lastIndex] += extra - used;
    }
    if (totalExpandHeight > 0) {
        int extra = Math.max(0, tableLayoutHeight - tablePrefHeight);
        int used = 0, lastIndex = 0;
        for (int i = 0; i < rows; i++) {
            if (expandHeight[i] == 0) continue;
            int amount = (int)(extra * expandHeight[i] / totalExpandHeight);
            rowHeight[i] += amount;
            used += amount;
            lastIndex = i;
        }
        rowHeight[lastIndex] += extra - used;
    }

    // Distribute any additional width added by colspanned cells evenly to the columns spanned.
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;
        if (c.colspan == 1) continue;

        int minWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.minWidth);

        int spannedCellWidth = 0;
        for (int column = c.column, nn = column + c.colspan; column < nn; column++)
            spannedCellWidth += columnWidth[column];

        int extraWidth = Math.max(0, minWidth - spannedCellWidth) / c.colspan;
        for (int column = c.column, nn = column + c.colspan; column < nn; column++)
            columnWidth[column] += extraWidth;

        c.widgetWidth = Math.max(c.widgetWidth, minWidth - (c.padLeftTemp + c.padRightTemp));
    }

    // Determine table size.
    int tableWidth = 0, tableHeight = 0;
    for (int i = 0; i < columns; i++)
        tableWidth += columnWidth[i];
    tableWidth = Math.max(tableWidth + hpadding, width);
    for (int i = 0; i < rows; i++)
        tableHeight += rowHeight[i];
    tableHeight = Math.max(tableHeight + vpadding, height);

    // Position table within the container.
    int x = layoutX + toolkit.width(this, padLeft);
    if ((align & RIGHT) != 0)
        x += tableLayoutWidth - tableWidth;
    else if ((align & LEFT) == 0) // Center
        x += (tableLayoutWidth - tableWidth) / 2;

    int y = layoutY + toolkit.height(this, padTop);
    if ((align & BOTTOM) != 0)
        y += tableLayoutHeight - tableHeight;
    else if ((align & TOP) == 0) // Center
        y += (tableLayoutHeight - tableHeight) / 2;

    // Position widgets within cells.
    int currentX = x;
    int currentY = y;
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;

        int spannedCellWidth = 0;
        for (int column = c.column, nn = column + c.colspan; column < nn; column++)
            spannedCellWidth += columnWidth[column];
        spannedCellWidth -= c.padLeftTemp + c.padRightTemp;

        currentX += c.padLeftTemp;

        if (c.fillX > 0) {
            c.widgetWidth = (int)(spannedCellWidth * c.fillX);
            int maxWidth = toolkit.getWidgetWidth(this, (C)c.widget, c.maxWidth);
            if (maxWidth > 0) c.widgetWidth = Math.min(c.widgetWidth, maxWidth);
        }
        if (c.fillY > 0) {
            c.widgetHeight = (int)(rowHeight[c.row] * c.fillY) - c.padTopTemp - c.padBottomTemp;
            int maxHeight = toolkit.getWidgetHeight(this, (C)c.widget, c.maxHeight);
            if (maxHeight > 0) c.widgetHeight = Math.min(c.widgetHeight, maxHeight);
        }

        if ((c.align & LEFT) != 0)
            c.widgetX = currentX;
        else if ((c.align & RIGHT) != 0)
            c.widgetX = currentX + spannedCellWidth - c.widgetWidth;
        else
            c.widgetX = currentX + (spannedCellWidth - c.widgetWidth) / 2;

        if ((c.align & TOP) != 0)
            c.widgetY = currentY + c.padTopTemp;
        else if ((c.align & BOTTOM) != 0)
            c.widgetY = currentY + rowHeight[c.row] - c.widgetHeight - c.padBottomTemp;
        else
            c.widgetY = currentY + (rowHeight[c.row] - c.widgetHeight + c.padTopTemp - c.padBottomTemp) / 2;

        if (c.endRow) {
            currentX = x;
            currentY += rowHeight[c.row];
        } else
            currentX += spannedCellWidth + c.padRightTemp;
    }

    // Draw widgets and bounds.
    if (debug == DEBUG_NONE) return;
    toolkit.clearDebugRectangles(this);
    currentX = x;
    currentY = y;
    if ((debug & DEBUG_TABLE) != 0 || (debug & DEBUG_ALL) != 0) {
        toolkit.addDebugRectangle(this, DEBUG_TABLE, layoutX, layoutY, tableLayoutWidth, tableLayoutHeight);
        toolkit.addDebugRectangle(this, DEBUG_TABLE, x, y, tableWidth - hpadding, tableHeight - vpadding);
    }
    for (int i = 0, n = cells.size(); i < n; i++) {
        Cell c = cells.get(i);
        if (c.ignore) continue;

        // Widget bounds.
        if ((debug & DEBUG_WIDGET) != 0 || (debug & DEBUG_ALL) != 0)
            toolkit.addDebugRectangle(this, DEBUG_WIDGET, c.widgetX, c.widgetY, c.widgetWidth, c.widgetHeight);

        // Cell bounds.
        int spannedCellWidth = 0;
        for (int column = c.column, nn = column + c.colspan; column < nn; column++)
            spannedCellWidth += columnWidth[column];
        spannedCellWidth -= c.padLeftTemp + c.padRightTemp;
        currentX += c.padLeftTemp;
        if ((debug & DEBUG_CELL) != 0 || (debug & DEBUG_ALL) != 0) {
            toolkit.addDebugRectangle(this, DEBUG_CELL, currentX, currentY + c.padTopTemp, spannedCellWidth, rowHeight[c.row]
                                      - c.padTopTemp - c.padBottomTemp);
        }

        if (c.endRow) {
            currentX = x;
            currentY += rowHeight[c.row];
        } else
            currentX += spannedCellWidth + c.padRightTemp;
    }
}

