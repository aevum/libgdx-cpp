
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

#include "Toolkit<C, T extends C, L extends BaseTableLayout>.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::tablelayout;

void Toolkit<C, T extends C, L extends BaseTableLayout>::addChild (const C& parent,const C& child,const std::string& layoutString);

abstract public void removeChild (C parent, C child);

abstract public int getMinWidth (C widget);

abstract public int getMinHeight (C widget);

abstract public int getPrefWidth (C widget);

abstract public int getPrefHeight (C widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

void Toolkit<C, T extends C, L extends BaseTableLayout>::removeChild (const C& parent,const C& child);

abstract public int getMinWidth (C widget);

abstract public int getMinHeight (C widget);

abstract public int getPrefWidth (C widget);

abstract public int getPrefHeight (C widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getMinWidth (const C& widget);

abstract public int getMinHeight (C widget);

abstract public int getPrefWidth (C widget);

abstract public int getPrefHeight (C widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getMinHeight (const C& widget);

abstract public int getPrefWidth (C widget);

abstract public int getPrefHeight (C widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getPrefWidth (const C& widget);

abstract public int getPrefHeight (C widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getPrefHeight (const C& widget);

abstract public int getMaxWidth (C widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getMaxWidth (const C& widget);

abstract public int getMaxHeight (C widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

int Toolkit<C, T extends C, L extends BaseTableLayout>::getMaxHeight (const C& widget);

/** Clears all debugging rectangles. */
abstract public void clearDebugRectangles (L layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

void Toolkit<C, T extends C, L extends BaseTableLayout>::clearDebugRectangles (const L& layout);

/** Adds a rectangle that should be drawn for debugging.
 * @param type {@value #DEBUG_ALL}

void Toolkit<C, T extends C, L extends BaseTableLayout>::addDebugRectangle (const L& layout,int type,int x,int y,int w,int h);

/** Returns a new widget that sizes all of its children to its size. */
abstract public C newStack ();

/** Returns the layout for a table. */
abstract public L getLayout (T table);

/** Returns a new table that will be nested under the specified table. The default implementation attempts to use the zero
 * argument constructor of the specified table's class. */
public T newTable (T parent) {
    try {
        return (T)parent.getClass().newInstance();
    } catch (Exception ex) {
        throw new RuntimeException("Unable to create an instance of: " + parent.getClass().getName());
    }
}

C& Toolkit<C, T extends C, L extends BaseTableLayout>::newStack ();

/** Returns the layout for a table. */
abstract public L getLayout (T table);

/** Returns a new table that will be nested under the specified table. The default implementation attempts to use the zero
 * argument constructor of the specified table's class. */
public T newTable (T parent) {
    try {
        return (T)parent.getClass().newInstance();
    } catch (Exception ex) {
        throw new RuntimeException("Unable to create an instance of: " + parent.getClass().getName());
    }
}

L& Toolkit<C, T extends C, L extends BaseTableLayout>::getLayout (const T& table);

/** Returns a new table that will be nested under the specified table. The default implementation attempts to use the zero
 * argument constructor of the specified table's class. */
public T newTable (T parent) {
    try {
        return (T)parent.getClass().newInstance();
    } catch (Exception ex) {
        throw new RuntimeException("Unable to create an instance of: " + parent.getClass().getName());
    }
}

T& Toolkit<C, T extends C, L extends BaseTableLayout>::newTable (const T& parent) {
    try {
        return (T)parent.getClass().newInstance();
    } catch (Exception ex) {
        throw new RuntimeException("Unable to create an instance of: " + parent.getClass().getName());
    }
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::setWidget (const L& layout,const Cell& cell,const C& widget) {
    if (widget != null) {
        removeChild((T)layout.table, widget);
        layout.widgetToCell.remove(widget);
    }
    cell.widget = widget;
    layout.nameToWidget.put(cell.name, widget);
    layout.widgetToCell.put(widget, cell);
    addChild((T)layout.table, widget, null);
}

std::string& Toolkit<C, T extends C, L extends BaseTableLayout>::validateSize (const std::string& size) {
    return size;
}

C& Toolkit<C, T extends C, L extends BaseTableLayout>::newWidget (const L& layout,const std::string& className) {
    try {
        return wrap(Class.forName(className).newInstance());
    } catch (Exception ex) {
        for (int i = 0, n = classPrefixes.size(); i < n; i++) {
            String prefix = classPrefixes.get(i);
            try {
                return newInstance(prefix + className);
            } catch (Exception ignored) {
            }
        }
        throw new RuntimeException("Error creating instance of class: " + className, ex);
    }
}

C& Toolkit<C, T extends C, L extends BaseTableLayout>::newInstance (const std::string& className) throws Exception {
    return (C)Class.forName(className).newInstance();
}

C& Toolkit<C, T extends C, L extends BaseTableLayout>::wrap (const Object& object) {
    if (object instanceof BaseTableLayout) return (C)((BaseTableLayout)object).getTable();
    try {
        return (C)object;
    } catch (ClassCastException ex) {
        throw new RuntimeException("Unknown object type: " + object.getClass());
    }
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::setProperty (const L& layout,const C& object,const std::string& name,std::list<String>& values) {
    try {
        invokeMethod(object, name, values);
    } catch (NoSuchMethodException ex1) {
        try {
            invokeMethod(object, "set" + Character.toUpperCase(name.charAt(0)) + name.substring(1), values);
        } catch (NoSuchMethodException ex2) {
            try {
                Field field = object.getClass().getField(name);
                Object value = convertType(object, field.getType(), name, values.get(0));
                if (value != null) field.set(object, value);
            } catch (Exception ex3) {
                throw new RuntimeException("No method, bean property, or field found: " + name + "\nClass: " + object.getClass()
                                           + "\nValues: " + values);
            }
        }
    }
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::setTableProperty (const L& layout,const std::string& name,std::list<String>& values) {
    name = name.toLowerCase();
    for (int i = 0, n = values.size(); i < n; i++)
        values.set(i, values.get(i).toLowerCase());
    try {
        String value;
        if (name.equals("size")) {
            switch (values.size()) {
            case 2:
                layout.height = validateSize(values.get(1));
            case 1:
                layout.width = validateSize(values.get(0));
                break;
            }

        } else if (name.equals("width") || name.equals("w")) {
            layout.width = validateSize(values.get(0));

        } else if (name.equals("height") || name.equals("h")) {
            layout.height = validateSize(values.get(0));

        } else if (name.equals("padding") || name.equals("pad")) {
            switch (values.size()) {
            case 4:
                value = values.get(3);
                if (value.length() > 0) layout.padRight = validateSize(value);
            case 3:
                value = values.get(2);
                if (value.length() > 0) layout.padBottom = validateSize(value);
            case 2:
                value = values.get(0);
                if (value.length() > 0) layout.padTop = validateSize(value);
                value = values.get(1);
                if (value.length() > 0) layout.padLeft = validateSize(value);
                break;
            case 1:
                layout.padTop = layout.padLeft = layout.padBottom = layout.padRight = validateSize(values.get(0));
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.startsWith("padding") || name.startsWith("pad")) {
            name = name.replace("padding", "").replace("pad", "");
            if (name.equals("top") || name.equals("t"))
                layout.padTop = validateSize(values.get(0));
            else if (name.equals("left") || name.equals("l"))
                layout.padLeft = validateSize(values.get(0));
            else if (name.equals("bottom") || name.equals("b"))
                layout.padBottom = validateSize(values.get(0));
            else if (name.equals("right") || name.equals("r"))
                layout.padRight = validateSize(values.get(0));
            else
                throw new IllegalArgumentException("Unknown property.");

        } else if (name.equals("align")) {
            int align = 0;
            for (int i = 0, n = values.size(); i < n; i++) {
                value = values.get(i);
                if (value.equals("center"))
                    align |= CENTER;
                else if (value.equals("left"))
                    align |= LEFT;
                else if (value.equals("right"))
                    align |= RIGHT;
                else if (value.equals("top"))
                    align |= TOP;
                else if (value.equals("bottom"))
                    align |= BOTTOM;
                else
                    throw new IllegalArgumentException("Invalid value: " + value);
            }
            layout.align = align;

        } else if (name.equals("debug")) {
            int debug = 0;
            if (values.size() == 0) debug = DEBUG_ALL;
            for (int i = 0, n = values.size(); i < n; i++) {
                value = values.get(i);
                if (value.equalsIgnoreCase("all") || value.equalsIgnoreCase("true")) debug |= DEBUG_ALL;
                if (value.equalsIgnoreCase("cell")) debug |= DEBUG_CELL;
                if (value.equalsIgnoreCase("table")) debug |= DEBUG_TABLE;
                if (value.equalsIgnoreCase("widget")) debug |= DEBUG_WIDGET;
            }
            layout.debug = debug;

        } else
            throw new IllegalArgumentException("Unknown table property: " + name);
    } catch (Exception ex) {
        throw new RuntimeException("Error setting table property: " + name, ex);
    }
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::setCellProperty (const Cell& c,const std::string& name,std::list<String>& values) {
    name = name.toLowerCase();
    for (int i = 0, n = values.size(); i < n; i++)
        values.set(i, values.get(i).toLowerCase());
    try {
        String value;
        if (name.equals("expand")) {
            switch (values.size()) {
            case 0:
                c.expandX = c.expandY = 1;
                break;
            case 1:
                value = values.get(0);
                if (value.equals("x"))
                    c.expandX = 1;
                else if (value.equals("y")) //
                    c.expandY = 1;
                else
                    c.expandX = c.expandY = Integer.parseInt(value);
                break;
            case 2:
                value = values.get(0);
                if (value.length() > 0) c.expandX = Integer.parseInt(value);
                value = values.get(1);
                if (value.length() > 0) c.expandY = Integer.parseInt(value);
                break;
            }

        } else if (name.equals("fill")) {
            switch (values.size()) {
            case 0:
                c.fillX = c.fillY = 1f;
                break;
            case 1:
                value = values.get(0);
                if (value.equals("x"))
                    c.fillX = 1f;
                else if (value.equals("y")) //
                    c.fillY = 1f;
                else
                    c.fillX = c.fillY = Integer.parseInt(value) / 100f;
                break;
            case 2:
                value = values.get(0);
                if (value.length() > 0) c.fillX = Integer.parseInt(value) / 100f;
                value = values.get(1);
                if (value.length() > 0) c.fillY = Integer.parseInt(value) / 100f;
                break;
            }

        } else if (name.equals("size")) {
            switch (values.size()) {
            case 2:
                value = values.get(0);
                if (value.length() > 0) c.minWidth = c.prefWidth = validateSize(value);
                value = values.get(1);
                if (value.length() > 0) c.minHeight = c.prefHeight = validateSize(value);
                break;
            case 1:
                value = values.get(0);
                if (value.length() > 0) c.minWidth = c.minHeight = c.prefWidth = c.prefHeight = validateSize(value);
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.equals("width") || name.equals("w")) {
            switch (values.size()) {
            case 3:
                value = values.get(2);
                if (value.length() > 0) c.maxWidth = validateSize(value);
            case 2:
                value = values.get(1);
                if (value.length() > 0) c.prefWidth = validateSize(value);
            case 1:
                value = values.get(0);
                if (value.length() > 0) c.minWidth = validateSize(value);
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.equals("height") || name.equals("h")) {
            switch (values.size()) {
            case 3:
                value = values.get(2);
                if (value.length() > 0) c.maxHeight = validateSize(value);
            case 2:
                value = values.get(1);
                if (value.length() > 0) c.prefHeight = validateSize(value);
            case 1:
                value = values.get(0);
                if (value.length() > 0) c.minHeight = validateSize(value);
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.equals("spacing") || name.equals("space")) {
            switch (values.size()) {
            case 4:
                value = values.get(3);
                if (value.length() > 0) c.spaceRight = validateSize(value);
            case 3:
                value = values.get(2);
                if (value.length() > 0) c.spaceBottom = validateSize(value);
            case 2:
                value = values.get(0);
                if (value.length() > 0) c.spaceTop = validateSize(value);
                value = values.get(1);
                if (value.length() > 0) c.spaceLeft = validateSize(value);
                break;
            case 1:
                c.spaceTop = c.spaceLeft = c.spaceBottom = c.spaceRight = validateSize(values.get(0));
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.equals("padding") || name.equals("pad")) {
            switch (values.size()) {
            case 4:
                value = values.get(3);
                if (value.length() > 0) c.padRight = validateSize(value);
            case 3:
                value = values.get(2);
                if (value.length() > 0) c.padBottom = validateSize(value);
            case 2:
                value = values.get(0);
                if (value.length() > 0) c.padTop = validateSize(value);
                value = values.get(1);
                if (value.length() > 0) c.padLeft = validateSize(value);
                break;
            case 1:
                c.padTop = c.padLeft = c.padBottom = c.padRight = validateSize(values.get(0));
                break;
            default:
                throw new IllegalArgumentException("Invalid number of values (" + values.size() + "): " + values);
            }

        } else if (name.startsWith("padding") || name.startsWith("pad")) {
            name = name.replace("padding", "").replace("pad", "");
            if (name.equals("top") || name.equals("t"))
                c.padTop = validateSize(values.get(0));
            else if (name.equals("left") || name.equals("l"))
                c.padLeft = validateSize(values.get(0));
            else if (name.equals("bottom") || name.equals("b"))
                c.padBottom = validateSize(values.get(0));
            else if (name.equals("right") || name.equals("r")) //
                c.padRight = validateSize(values.get(0));
            else
                throw new IllegalArgumentException("Unknown property.");

        } else if (name.startsWith("spacing") || name.startsWith("space")) {
            name = name.replace("spacing", "").replace("space", "");
            if (name.equals("top") || name.equals("t"))
                c.spaceTop = validateSize(values.get(0));
            else if (name.equals("left") || name.equals("l"))
                c.spaceLeft = validateSize(values.get(0));
            else if (name.equals("bottom") || name.equals("b"))
                c.spaceBottom = validateSize(values.get(0));
            else if (name.equals("right") || name.equals("r")) //
                c.spaceRight = validateSize(values.get(0));
            else
                throw new IllegalArgumentException("Unknown property.");

        } else if (name.equals("align")) {
            c.align = 0;
            for (int i = 0, n = values.size(); i < n; i++) {
                value = values.get(i);
                if (value.equals("center"))
                    c.align |= CENTER;
                else if (value.equals("left"))
                    c.align |= LEFT;
                else if (value.equals("right"))
                    c.align |= RIGHT;
                else if (value.equals("top"))
                    c.align |= TOP;
                else if (value.equals("bottom"))
                    c.align |= BOTTOM;
                else
                    throw new IllegalArgumentException("Invalid value: " + value);
            }

        } else if (name.equals("ignore")) {
            c.ignore = values.size() == 0 ? true : Boolean.valueOf(values.get(0));

        } else if (name.equals("colspan")) {
            c.colspan = Integer.parseInt(values.get(0));

        } else if (name.equals("uniform")) {
            if (values.size() == 0) c.uniformX = c.uniformY = true;
            for (int i = 0, n = values.size(); i < n; i++) {
                value = values.get(i);
                if (value.equals("x"))
                    c.uniformX = true;
                else if (value.equals("y"))
                    c.uniformY = true;
                else if (value.equals("false"))
                    c.uniformY = c.uniformY = null;
                else
                    throw new IllegalArgumentException("Invalid value: " + value);
            }

        } else
            throw new IllegalArgumentException("Unknown cell property.");
    } catch (Exception ex) {
        throw new RuntimeException("Error setting cell property: " + name, ex);
    }
}

int Toolkit<C, T extends C, L extends BaseTableLayout>::width (const L& layout,const std::string& value) {
    int length;
    if (value == null || (length = value.length()) == 0) return width(0);
    if (value.charAt(length - 1) == '%' && length > 1)
        return (int)(layout.getLayoutWidth() * Integer.parseInt(value.substring(0, length - 1)) / 100f);
    if (value.endsWith("px")) return Integer.parseInt(value.substring(0, value.length() - 2));
    return width(value == null ? 0 : Integer.parseInt(value));
}

int Toolkit<C, T extends C, L extends BaseTableLayout>::width (float value) {
    return (int)value;
}

int Toolkit<C, T extends C, L extends BaseTableLayout>::height (const L& layout,const std::string& value) {
    int length;
    if (value == null || (length = value.length()) == 0) return height(0);
    if (value.charAt(length - 1) == '%' && length > 1)
        return (int)(layout.getLayoutHeight() * Integer.parseInt(value.substring(0, length - 1)) / 100f);
    if (value.endsWith("px")) return Integer.parseInt(value.substring(0, value.length() - 2));
    return height(value == null ? 0 : Integer.parseInt(value));
}

int Toolkit<C, T extends C, L extends BaseTableLayout>::height (float value) {
    return (int)value;
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::invokeMethod (const Object& object,const std::string& name,std::list<String>& values) throws NoSuchMethodException {
    Object[] params = values.toArray();
    // Prefer methods with string parameters.
    Class[] stringParamTypes = new Class[params.length];
    Method method = null;
    try {
        for (int i = 0, n = params.length; i < n; i++)
            stringParamTypes[i] = String.class;
        method = object.getClass().getMethod(name, stringParamTypes);
    } catch (NoSuchMethodException ignored) {
        try {
            for (int i = 0, n = params.length; i < n; i++)
                stringParamTypes[i] = CharSequence.class;
            method = object.getClass().getMethod(name, stringParamTypes);
        } catch (NoSuchMethodException ignored2) {
        }
    }
    if (method != null) {
        try {
            method.invoke(object, params);
        } catch (Exception ex) {
            throw new RuntimeException("Error invoking method: " + name, ex);
        }
        return;
    }
    // Try to convert the strings to match a method.
    Method[] methods = object.getClass().getMethods();
outer:
    for (int i = 0, n = methods.length; i < n; i++) {
        method = methods[i];
        if (!method.getName().equalsIgnoreCase(name)) continue;
        Class[] paramTypes = method.getParameterTypes();
        if (paramTypes.length != values.size()) continue;
        params = values.toArray();
        for (int ii = 0, nn = paramTypes.length; ii < nn; ii++) {
            Object value = convertType(object, paramTypes[ii], name, (String)params[ii]);
            if (value == null) continue outer;
            params[ii] = value;
        }
        try {
            method.invoke(object, params);
            return;
        } catch (Exception ex) {
            throw new RuntimeException("Error invoking method: " + name, ex);
        }
    }
    throw new NoSuchMethodException();
}

Object& Toolkit<C, T extends C, L extends BaseTableLayout>::convertType (const Object& parentObject,const Class& memberType,const std::string& memberName,const std::string& value) {
    if (memberType == String.class || memberType == CharSequence.class) return value;
    try {
        if (memberType == int.class || memberType == Integer.class) return Integer.valueOf(value);
        if (memberType == float.class || memberType == Float.class) return Float.valueOf(value);
        if (memberType == long.class || memberType == Long.class) return Long.valueOf(value);
        if (memberType == double.class || memberType == Double.class) return Double.valueOf(value);
    } catch (NumberFormatException ignored) {
    }
    if (memberType == boolean.class || memberType == Boolean.class) return Boolean.valueOf(value);
    if (memberType == char.class || memberType == Character.class) return value.charAt(0);
    if (memberType == short.class || memberType == Short.class) return Short.valueOf(value);
    if (memberType == byte.class || memberType == Byte.class) return Byte.valueOf(value);
    // Look for a static field.
    try {
        Field field = getField(memberType, value);
        if (field != null && memberType == field.getType()) return field.get(null);
    } catch (Exception ignored) {
    }
    try {
        Field field = getField(parentObject.getClass(), value);
        if (field != null && memberType == field.getType()) return field.get(null);
    } catch (Exception ignored) {
    }
    return null;
}

Field& Toolkit<C, T extends C, L extends BaseTableLayout>::getField (const Class& type,const std::string& name) {
    try {
        Field field = type.getField(name);
        if (field != null) return field;
    } catch (Exception ignored) {
    }
    while (type != null && type != Object.class) {
        Field[] fields = type.getDeclaredFields();
        for (int i = 0, n = fields.length; i < n; i++)
            if (fields[i].getName().equalsIgnoreCase(name)) return fields[i];
        type = type.getSuperclass();
    }
    return null;
}

void Toolkit<C, T extends C, L extends BaseTableLayout>::addClassPrefix (const std::string& prefix) {
    classPrefixes.add(prefix);
}

