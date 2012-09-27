
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

#include "Json.hpp"
#include <stdexcept>

using namespace gdx;

void Json::setIgnoreUnknownFields (bool ignoreUnknownFields) {
    this->ignoreUnknownFields = ignoreUnknownFields;
}

void Json::setOutputType (const JsonWriter::OutputType& outputType) {
    this->outputType = outputType;
}

void Json::addClassTag (const std::string& tag,const Class& type) {
    tagToClass.put(tag, type);
    classToTag.put(type, tag);
}

void Json::setTypeName (const std::string& typeName) {
    this->typeName = typeName;
}

void Json::setUsePrototypes (bool usePrototypes) {
    this->usePrototypes = usePrototypes;
}

void Json::setElementType (const Class& type,const std::string& fieldName,const Class& elementType) {
    ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
    if (fields == NULL) fields = cacheFields(type);
    FieldMetadata metadata = fields.get(fieldName);
    if (metadata == NULL) throw new SerializationException("Field not found: " + fieldName + " (" + type.getName() + ")");
    metadata.elementType = elementType;
}

std::string& Json::toJson (const JsonValue& object) {
    return toJson(object, object == NULL ? NULL : object.getClass(), (Class)NULL);
}

std::string& Json::toJson (const JsonValue& object,const Class& knownType) {
    return toJson(object, knownType, (Class)NULL);
}

std::string& Json::toJson (const JsonValue& object) {
    std::stringstream buffer;
    toJson(object, knownType, elementType, buffer);
    return buffer.str();
}

void Json::toJson (const JsonValue& object,const FileHandle& file) {
    toJson(object, object == NULL ? NULL : object.getClass(), NULL, file);
}

void Json::toJson (const JsonValue& object,const Class& knownType,const FileHandle& file) {
    toJson(object, knownType, NULL, file);
}

void Json::toJson (const JsonValue& object,const Class& knownType,const Class& elementType,const FileHandle& file) {
    try {
        FileHandle::ofstream_ptr writer = file.write(false);
        toJson(object, knownType, elementType, writer);
        writer->close();
    } catch (...) {
        gdx_log_error("gdx","Error writing file: " + file.name());
    }
}

void Json::writeFields (const JsonValue& object) {
    std::vector< JsonValue > defaultValues = getDefaultValues(object.item_type);

    ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
    if (fields == NULL) fields = cacheFields(type);
    int i = 0;
for (FieldMetadata metadata : fields.values()) {
        Field field = metadata.field;
        try {
            Object value = field.get(object);

            if (defaultValues != NULL) {
                Object defaultValue = defaultValues[i++];
                if (value == NULL && defaultValue == NULL) continue;
                if (value != NULL && defaultValue != NULL && value.equals(defaultValue)) continue;
            }

            if (debug) System.out.println("Writing field: " + field.getName() + " (" + type.getName() + ")");
            writer.name(field.getName());
            writeValue(value, field.getType(), metadata.elementType);
        } catch (IllegalAccessException ex) {
            throw new SerializationException("Error accessing field: " + field.getName() + " (" + type.getName() + ")", ex);
        } catch (SerializationException ex) {
            ex.addTrace(field + " (" + type.getName() + ")");
            throw ex;
        } catch (Exception runtimeEx) {
            SerializationException ex = new SerializationException(runtimeEx);
            ex.addTrace(field + " (" + type.getName() + ")");
            throw ex;
        }
    }
}

std::vector< Json::json_item > Json::getDefaultValues (const Json::json_item& item) {
    if (!usePrototypes) return std::vector< JsonValue >();
    
    std::vector< Json::json_item > values = classToDefaultValues[item.item_type];
    if (values.empty()) {
        JsonValue object;

        ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
        if (fields == NULL) fields = cacheFields(type);

        values = new Object[fields.size];
        classToDefaultValues.put(type, values);

        int i = 0;
for (FieldMetadata metadata : fields.values()) {
            Field field = metadata.field;
            try {
                values[i++] = field.get(object);
            } catch (IllegalAccessException ex) {
                throw new SerializationException("Error accessing field: " + field.getName() + " (" + type.getName() + ")", ex);
            } catch (SerializationException ex) {
                ex.addTrace(field + " (" + type.getName() + ")");
                throw ex;
            } catch (RuntimeException runtimeEx) {
                SerializationException ex = new SerializationException(runtimeEx);
                ex.addTrace(field + " (" + type.getName() + ")");
                throw ex;
            }
        }
    }
    return values;
}

void Json::writeField (const JsonValue& object,const std::string& name) {
    writeField(object, name, name, NULL);
}

void Json::writeField (const JsonValue& object,const std::string& name,const Class& elementType) {
    writeField(object, name, name, elementType);
}

void Json::writeField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName) {
    writeField(object, fieldName, jsonName, NULL);
}

void Json::writeField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName,const Class& elementType) {
    Class type = object.getClass();
    ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
    if (fields == NULL) fields = cacheFields(type);
    FieldMetadata metadata = fields.get(fieldName);
    if (metadata == NULL) throw new SerializationException("Field not found: " + fieldName + " (" + type.getName() + ")");
    Field field = metadata.field;
    if (elementType == NULL) elementType = metadata.elementType;
    try {
        if (debug) System.out.println("Writing field: " + field.getName() + " (" + type.getName() + ")");
        writer.name(jsonName);
        writeValue(field.get(object), field.getType(), elementType);
    } catch (IllegalAccessException ex) {
        throw new SerializationException("Error accessing field: " + field.getName() + " (" + type.getName() + ")", ex);
    } catch (SerializationException ex) {
        ex.addTrace(field + " (" + type.getName() + ")");
        throw ex;
    } catch (Exception runtimeEx) {
        SerializationException ex = new SerializationException(runtimeEx);
        ex.addTrace(field + " (" + type.getName() + ")");
        throw ex;
    }
}

void Json::writeValue (const std::string& name,const JsonValue& value) {
    try {
        writer.name(name);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    writeValue(value, value.getClass(), NULL);
}

void Json::writeValue (const std::string& name,const JsonValue& value,const Class& knownType) {
    try {
        writer.name(name);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    writeValue(value, knownType, NULL);
}

void Json::writeValue (const std::string& name,const JsonValue& value,const Class& knownType,const Class& elementType) {
    try {
        writer.name(name);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    writeValue(value, knownType, elementType);
}

void Json::writeValue (const JsonValue& value) {
    writeValue(value, value.getClass(), NULL);
}

void Json::writeValue (const JsonValue& value,const Class& knownType) {
    writeValue(value, knownType, NULL);
}

void Json::writeValue (const JsonValue& value,const Class& knownType,const Class& elementType) {
    try {
        if (value == NULL) {
            writer.value(NULL);
            return;
        }

        Class actualType = value.getClass();

        if (actualType.isPrimitive() || actualType == String.class || actualType == Integer.class || actualType == Boolean.class
                || actualType == Float.class || actualType == Long.class || actualType == Double.class || actualType == Short.class
                || actualType == Byte.class || actualType == Character.class) {
            writer.value(value);
            return;
        }

        if (value instanceof Serializable) {
            writeObjectStart(actualType, knownType);
            ((Serializable)value).write(this);
            writeObjectEnd();
            return;
        }

        Serializer serializer = classToSerializer.get(actualType);
        if (serializer != NULL) {
            serializer.write(this, value, knownType);
            return;
        }

        if (value instanceof Array) {
            if (knownType != NULL && actualType != knownType)
                throw new SerializationException("Serialization of an Array other than the known type is not supported.\n"
                                                 + "Known type: " + knownType + "\nActual type: " + actualType);
            writeArrayStart();
            Array array = (Array)value;
            for (int i = 0, n = array.size; i < n; i++)
                writeValue(array.get(i), elementType, NULL);
            writeArrayEnd();
            return;
        }

        if (value instanceof Collection) {
            if (knownType != NULL && actualType != knownType)
                throw new SerializationException("Serialization of a Collection other than the known type is not supported.\n"
                                                 + "Known type: " + knownType + "\nActual type: " + actualType);
            writeArrayStart();
for (Object item : (Collection)value)
                writeValue(item, elementType, NULL);
            writeArrayEnd();
            return;
        }

        if (actualType.isArray()) {
            if (elementType == NULL) elementType = actualType.getComponentType();
            int length = java.lang.reflect.Array.getLength(value);
            writeArrayStart();
            for (int i = 0; i < length; i++)
                writeValue(java.lang.reflect.Array.get(value, i), elementType, NULL);
            writeArrayEnd();
            return;
        }

        if (value instanceof ObjectMap) {
            if (knownType == NULL) knownType = ObjectMap.class;
            writeObjectStart(actualType, knownType);
for (Entry entry : ((ObjectMap<?, ?>)value).entries()) {
                writer.name(convertToString(entry.key));
                writeValue(entry.value, elementType, NULL);
            }
            writeObjectEnd();
            return;
        }

        if (value instanceof Map) {
            if (knownType == NULL) knownType = ObjectMap.class;
            writeObjectStart(actualType, knownType);
for (Map.Entry entry : ((Map<?, ?>)value).entrySet()) {
                writer.name(convertToString(entry.getKey()));
                writeValue(entry.getValue(), elementType, NULL);
            }
            writeObjectEnd();
            return;
        }

        if (actualType.isEnum()) {
            writer.value(value);
            return;
        }

        writeObjectStart(actualType, knownType);
        writeFields(value);
        writeObjectEnd();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeObjectStart (const std::string& name) {
    try {
        writer.name(name);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    writeObjectStart();
}

void Json::writeObjectStart (const std::string& name,const Class& actualType,const Class& knownType) {
    try {
        writer.name(name);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    writeObjectStart(actualType, knownType);
}

void Json::writeObjectStart () {
    try {
        writer.object();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeObjectStart (const Class& actualType,const Class& knownType) {
    try {
        writer.object();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    if (knownType == NULL || knownType != actualType) writeType(actualType);
}

void Json::writeObjectEnd () {
    try {
        writer.pop();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeArrayStart (const std::string& name) {
    try {
        writer.name(name);
        writer.array();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeArrayStart () {
    try {
        writer.array();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeArrayEnd () {
    try {
        writer.pop();
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
}

void Json::writeType (const Class& type) {
    if (typeName == NULL) return;
    String className = classToTag.get(type);
    if (className == NULL) className = type.getName();
    try {
        writer.set(typeName, className);
    } catch (IOException ex) {
        throw new SerializationException(ex);
    }
    if (debug) System.out.println("Writing type: " + type.getName());
}

void Json::readField (const JsonValue& object, const std::string& name, const JsonValue& jsonData) {
    readField(object, name, name, NULL, jsonData);
}

void Json::readField (const JsonValue& object,const std::string& name,const Class& elementType,const JsonValue& jsonData) {
    readField(object, name, name, elementType, jsonData);
}

void Json::readField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName,const JsonValue& jsonData) {
    readField(object, fieldName, jsonName, NULL, jsonData);
}

void Json::readField (const JsonValue& object,const std::string& fieldName,const std::string& jsonName,
                      const JsonValue& jsonData) {
    
    Class type = object.getClass();
    ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
    if (fields == NULL) fields = cacheFields(type);
    FieldMetadata metadata = fields.get(fieldName);
    if (metadata == NULL) throw new SerializationException("Field not found: " + fieldName + " (" + type.getName() + ")");
    Field field = metadata.field;
    Object jsonValue = jsonMap.get(jsonName);
    if (jsonValue == NULL) return;
    if (elementType == NULL) elementType = metadata.elementType;
    try {
        field.set(object, readValue(field.getType(), elementType, jsonValue));
    } catch (IllegalAccessException ex) {
        throw new SerializationException("Error accessing field: " + field.getName() + " (" + type.getName() + ")", ex);
    } catch (SerializationException ex) {
        ex.addTrace(field.getName() + " (" + type.getName() + ")");
        throw ex;
    } catch (RuntimeException runtimeEx) {
        SerializationException ex = new SerializationException(runtimeEx);
        ex.addTrace(field.getName() + " (" + type.getName() + ")");
        throw ex;
    }
}

void Json::readFields (const JsonValue& object,const JsonValue& jsonData) {
    ObjectMap<String, Object> jsonMap = (ObjectMap)jsonData;
    Class type = object.getClass();
    ObjectMap<String, FieldMetadata> fields = typeToFields.get(type);
    if (fields == NULL) fields = cacheFields(type);
for (Entry<String, Object> entry : jsonMap.entries()) {
        FieldMetadata metadata = fields.get(entry.key);
        if (ignoreUnknownFields) {
            if (debug) System.out.println("Ignoring unknown field: " + entry.key + " (" + type.getName() + ")");
        } else if (metadata == NULL)
            throw new SerializationException("Field not found: " + entry.key + " (" + type.getName() + ")");
        Field field = metadata.field;
        if (entry.value == NULL) continue;
        try {
            field.set(object, readValue(field.getType(), metadata.elementType, entry.value));
        } catch (IllegalAccessException ex) {
            throw new SerializationException("Error accessing field: " + field.getName() + " (" + type.getName() + ")", ex);
        } catch (SerializationException ex) {
            ex.addTrace(field.getName() + " (" + type.getName() + ")");
            throw ex;
        } catch (RuntimeException runtimeEx) {
            SerializationException ex = new SerializationException(runtimeEx);
            ex.addTrace(field.getName() + " (" + type.getName() + ")");
            throw ex;
        }
    }
}

std::string& Json::convertToString (const JsonValue& object) {
    if (object instanceof Class) return ((Class)object).getName();
    return String.valueOf(object);
}

std::string& Json::prettyPrint (const JsonValue& object) {
    return prettyPrint(object, false);
}

std::string& Json::prettyPrint (const std::string& json) {
    return prettyPrint(json, false);
}

std::string& Json::prettyPrint (const JsonValue& object,bool fieldsOnSameLine) {
    return prettyPrint(toJson(object), fieldsOnSameLine);
}

std::string& Json::prettyPrint (const std::string& json,bool fieldsOnSameLine) {
    StringBuilder buffer = new StringBuilder(512);
    prettyPrint(new JsonReader().parse(json), buffer, 0, fieldsOnSameLine);
    return buffer.toString();
}

void Json::prettyPrint (const JsonValue& object,const StringBuilder& buffer,int indent,bool fieldsOnSameLine) {
    if (object instanceof ObjectMap) {
        ObjectMap<?, ?> map = (ObjectMap)object;
        if (map.size == 0) {
            buffer.append("{}");
        } else {
            boolean newLines = !fieldsOnSameLine || !isFlat(map);
            buffer.append(newLines ? "{\n" : "{ ");
            int i = 0;
for (Entry entry : map.entries()) {
                if (newLines) indent(indent, buffer);
                buffer.append(outputType.quoteName((String)entry.key));
                buffer.append(": ");
                prettyPrint(entry.value, buffer, indent + 1, fieldsOnSameLine);
                if (i++ < map.size - 1) buffer.append(",");
                buffer.append(newLines ? '\n' : ' ');
            }
            if (newLines) indent(indent - 1, buffer);
            buffer.append('}');
        }
    } else if (object instanceof Array) {
        Array array = (Array)object;
        if (array.size == 0) {
            buffer.append("[]");
        } else {
            boolean newLines = !fieldsOnSameLine || !isFlat(array);
            buffer.append(newLines ? "[\n" : "[ ");
            for (int i = 0, n = array.size; i < n; i++) {
                if (newLines) indent(indent, buffer);
                prettyPrint(array.get(i), buffer, indent + 1, fieldsOnSameLine);
                if (i < array.size - 1) buffer.append(",");
                buffer.append(newLines ? '\n' : ' ');
            }
            if (newLines) indent(indent - 1, buffer);
            buffer.append(']');
        }
    } else if (object instanceof String) {
        buffer.append(outputType.quoteValue((String)object));
    } else if (object instanceof Float) {
        Float floatValue = (Float)object;
        int intValue = floatValue.intValue();
        buffer.append(floatValue - intValue == 0 ? intValue : object);
    } else if (object instanceof Boolean) {
        buffer.append(object);
    } else if (object == NULL) {
        buffer.append("NULL");
    } else
        throw new SerializationException("Unknown object type: " + object.getClass());
}

static private boolean isFlat (ObjectMap<?, ?> map) {
    for (Entry entry : map.entries()) {
        if (entry.value instanceof ObjectMap) return false;
        if (entry.value instanceof Array) return false;
    }
    return true;
}

static private boolean isFlat (Array array) {
    for (int i = 0, n = array.size; i < n; i++) {
        Object value = array.get(i);
        if (value instanceof ObjectMap) return false;
        if (value instanceof Array) return false;
    }
    return true;
}

static private void indent (int count, StringBuilder buffer) {
    for (int i = 0; i < count; i++)
        buffer.append('\t');
}

static private class FieldMetadata {
    public Field field;
    public Class elementType;

    public FieldMetadata (Field field) {
        this->field = field;
    }
}

static public interface Serializer<T> {
    public void write (Json json, T object, Class knownType);

    public T read (Json json, Object jsonData, Class type);
}

static public interface Serializable {
    public void write (Json json);

    public void read (Json json, ObjectMap<String, Object> jsonData);
}
}

bool Json::isFlat (const ObjectMap<?, ?>& map) {
    for (Entry entry : map.entries()) {
        if (entry.value instanceof ObjectMap) return false;
        if (entry.value instanceof Array) return false;
    }
    return true;
}

bool Json::isFlat (const Array& array) {
    for (int i = 0, n = array.size; i < n; i++) {
        Object value = array.get(i);
        if (value instanceof ObjectMap) return false;
        if (value instanceof Array) return false;
    }
    return true;
}

void Json::indent (int count,const StringBuilder& buffer) {
    for (int i = 0; i < count; i++)
        buffer.append('\t');
}

Json::Json () {
    outputType = OutputType.minimal;
}

Json::Json (const JsonWriter::OutputType& outputType) {
    this->outputType = outputType;
}

