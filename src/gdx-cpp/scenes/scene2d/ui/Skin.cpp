
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

#include "Skin.hpp"

using namespace gdx_cpp::scenes::scene2d::ui;

void Skin::dispose () {
    data.texture.dispose();
for (Object object : data.resources.values())
        if (object instanceof Disposable) ((Disposable)object).dispose();
}

void Skin::setTexture (const gdx_cpp::graphics::Texture& texture) {
    data.texture = texture;
}

gdx_cpp::graphics::Texture& Skin::getTexture () {
    return data.texture;
}

void Skin::save (const gdx_cpp::files::FileHandle& skinFile) {
    String text = getJsonLoader(null).prettyPrint(this, true);
    Writer writer = skinFile.writer(false);
    try {
        writer.write(text);
        writer.close();
    } catch (IOException ex) {
    }
}

gdx_cpp::utils::Json& Skin::getJsonLoader (const final& FileHandle) {
    final Skin skin = this;

    Json json = new Json();
    json.setTypeName(null);
    json.setUsePrototypes(false);

    class AliasSerializer implements Serializer {
        final ObjectMap<String, ?> map;

        public AliasSerializer (ObjectMap<String, ?> map) {
            this.map = map;
        }

        public void write (Json json, Object object, Class valueType) {
            for (Entry<String, ?> entry : map.entries()) {
                if (entry.value.equals(object)) {
                    json.writeValue(entry.key);
                    return;
                }
            }
            throw new SerializationException(object.getClass().getSimpleName() + " not found: " + object);
        }

        public Object read (Json json, Object jsonData, Class type) {
            String name = (String)jsonData;
            Object object = map.get(name);
            if (object == null) {
                ObjectMap<String, Object> regions = data.resources.get(TextureRegion.class);
                if (regions != null) {
                    object = regions.get(name);
                    if (object != null) object = new NinePatch((TextureRegion)object);
                }
                if (object == null)
                    throw new SerializationException("Skin has a " + type.getSimpleName()
                                                     + " that could not be found in the resources: " + jsonData);
            }
            return object;
        }
    }

    json.setSerializer(Skin.class, new Serializer<Skin>() {
        public void write (Json json, Skin skin, Class valueType) {
            json.writeObjectStart();
            json.writeValue("resources", skin.data.resources);
for (Entry<Class, ObjectMap<String, Object>> entry : data.resources.entries())
                json.setSerializer(entry.key, new AliasSerializer(entry.value));
            json.writeField(skin, "styles");
            json.writeObjectEnd();
        }

        public Skin read (Json json, Object jsonData, Class ignored) {
            ObjectMap map = (ObjectMap)jsonData;
            readTypeMap(json, (ObjectMap)map.get("resources"), true);
for (Entry<Class, ObjectMap<String, Object>> entry : data.resources.entries())
                json.setSerializer(entry.key, new AliasSerializer(entry.value));
            readTypeMap(json, (ObjectMap)map.get("styles"), false);
            return skin;
        }

        private void readTypeMap (Json json, ObjectMap<String, ObjectMap> typeToValueMap, boolean isResource) {
            if (typeToValueMap == null)
                throw new SerializationException("Skin file is missing a \"" + (isResource ? "resources" : "styles")
                                                 + "\" section.");
for (Entry<String, ObjectMap> typeEntry : typeToValueMap.entries()) {
                Class type;
                try {
                    type = Class.forName(typeEntry.key);
                } catch (ClassNotFoundException ex) {
                    throw new SerializationException(ex);
                }
                ObjectMap<String, ObjectMap> valueMap = (ObjectMap)typeEntry.value;
for (Entry<String, ObjectMap> valueEntry : valueMap.entries()) {
                    try {
                        if (isResource)
                            addResource(valueEntry.key, json.readValue(type, valueEntry.value));
                        else
                            addStyle(valueEntry.key, json.readValue(type, valueEntry.value));
                    } catch (Exception ex) {
                        throw new SerializationException("Error reading " + type.getSimpleName() + ": " + valueEntry.key, ex);
                    }
                }
            }
        }
    });

    json.setSerializer(TextureRegion.class, new Serializer<TextureRegion>() {
        public void write (Json json, TextureRegion region, Class valueType) {
            json.writeObjectStart();
            json.writeValue("x", region.getRegionX());
            json.writeValue("y", region.getRegionY());
            json.writeValue("width", region.getRegionWidth());
            json.writeValue("height", region.getRegionHeight());
            json.writeObjectEnd();
        }

        public TextureRegion read (Json json, Object jsonData, Class type) {
            int x = json.readValue("x", int.class, jsonData);
            int y = json.readValue("y", int.class, jsonData);
            int width = json.readValue("width", int.class, jsonData);
            int height = json.readValue("height", int.class, jsonData);
            return new TextureRegion(skin.data.texture, x, y, width, height);
        }
    });

    json.setSerializer(BitmapFont.class, new Serializer<BitmapFont>() {
        public void write (Json json, BitmapFont font, Class valueType) {
            json.writeValue(font.getData().getFontFile().toString().replace('\\', '/'));
        }

        public BitmapFont read (Json json, Object jsonData, Class type) {
            String path = json.readValue(String.class, jsonData);
            FileHandle file = skinFile.parent().child(path);
            if (!file.exists()) file = Gdx.files.internal(path);
            return new BitmapFont(file, false);
        }
    });

    json.setSerializer(NinePatch.class, new Serializer<NinePatch>() {
        public void write (Json json, NinePatch ninePatch, Class valueType) {
            json.writeValue(ninePatch.getPatches());
        }

        public NinePatch read (Json json, Object jsonData, Class type) {
            return new NinePatch(json.readValue(TextureRegion[].class, jsonData));
        }
    });

    return json;
}

void Skin::write (const gdx_cpp::utils::Json& json,const Object& object,const Class& valueType) {
    for (Entry<String, ?> entry : map.entries()) {
        if (entry.value.equals(object)) {
            json.writeValue(entry.key);
            return;
        }
    }
    throw new SerializationException(object.getClass().getSimpleName() + " not found: " + object);
}

Object& Skin::read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type) {
    String name = (String)jsonData;
    Object object = map.get(name);
    if (object == null) {
        ObjectMap<String, Object> regions = data.resources.get(TextureRegion.class);
        if (regions != null) {
            object = regions.get(name);
            if (object != null) object = new NinePatch((TextureRegion)object);
        }
        if (object == null)
            throw new SerializationException("Skin has a " + type.getSimpleName()
                                             + " that could not be found in the resources: " + jsonData);
    }
    return object;
}

void Skin::write (const gdx_cpp::utils::Json& json,const Skin& skin,const Class& valueType) {
    json.writeObjectStart();
    json.writeValue("resources", skin.data.resources);
for (Entry<Class, ObjectMap<String, Object>> entry : data.resources.entries())
        json.setSerializer(entry.key, new AliasSerializer(entry.value));
    json.writeField(skin, "styles");
    json.writeObjectEnd();
}

Skin& Skin::read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& ignored) {
    ObjectMap map = (ObjectMap)jsonData;
    readTypeMap(json, (ObjectMap)map.get("resources"), true);
for (Entry<Class, ObjectMap<String, Object>> entry : data.resources.entries())
        json.setSerializer(entry.key, new AliasSerializer(entry.value));
    readTypeMap(json, (ObjectMap)map.get("styles"), false);
    return skin;
}

void Skin::readTypeMap (const gdx_cpp::utils::Json& json,gdx_cpp::utils::ObjectMapString, ObjectMap>& typeToValueMap,bool isResource) {
    if (typeToValueMap == null)
        throw new SerializationException("Skin file is missing a \"" + (isResource ? "resources" : "styles")
                                         + "\" section.");
for (Entry<String, ObjectMap> typeEntry : typeToValueMap.entries()) {
        Class type;
        try {
            type = Class.forName(typeEntry.key);
        } catch (ClassNotFoundException ex) {
            throw new SerializationException(ex);
        }
        ObjectMap<String, ObjectMap> valueMap = (ObjectMap)typeEntry.value;
for (Entry<String, ObjectMap> valueEntry : valueMap.entries()) {
            try {
                if (isResource)
                    addResource(valueEntry.key, json.readValue(type, valueEntry.value));
                else
                    addStyle(valueEntry.key, json.readValue(type, valueEntry.value));
            } catch (Exception ex) {
                throw new SerializationException("Error reading " + type.getSimpleName() + ": " + valueEntry.key, ex);
            }
        }
    }
}

void Skin::write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::TextureRegion& region,const Class& valueType) {
    json.writeObjectStart();
    json.writeValue("x", region.getRegionX());
    json.writeValue("y", region.getRegionY());
    json.writeValue("width", region.getRegionWidth());
    json.writeValue("height", region.getRegionHeight());
    json.writeObjectEnd();
}

gdx_cpp::graphics::g2d::TextureRegion& Skin::read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type) {
    int x = json.readValue("x", int.class, jsonData);
    int y = json.readValue("y", int.class, jsonData);
    int width = json.readValue("width", int.class, jsonData);
    int height = json.readValue("height", int.class, jsonData);
    return new TextureRegion(skin.data.texture, x, y, width, height);
}

void Skin::write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::BitmapFont& font,const Class& valueType) {
    json.writeValue(font.getData().getFontFile().toString().replace('\\', '/'));
}

gdx_cpp::graphics::g2d::BitmapFont& Skin::read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type) {
    String path = json.readValue(String.class, jsonData);
    FileHandle file = skinFile.parent().child(path);
    if (!file.exists()) file = Gdx.files.internal(path);
    return new BitmapFont(file, false);
}

void Skin::write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::NinePatch& ninePatch,const Class& valueType) {
    json.writeValue(ninePatch.getPatches());
}

gdx_cpp::graphics::g2d::NinePatch& Skin::read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type) {
    return new NinePatch(json.readValue(TextureRegion[].class, jsonData));
}

Skin::Skin () {
    data = new SkinData();
}

Skin::Skin (const gdx_cpp::files::FileHandle& skinFile,const gdx_cpp::files::FileHandle& textureFile) {
    data = new SkinData();
    data.texture = new Texture(textureFile);
    try {
        getJsonLoader(skinFile).fromJson(Skin.class, skinFile);
    } catch (SerializationException ex) {
        throw new SerializationException("Error reading file: " + skinFile, ex);
    }
}

Skin::Skin (const gdx_cpp::files::FileHandle& skinFile,const SkinData& data) {
    this.data = data;
    data.texture.setFilter(TextureFilter.Linear, TextureFilter.Linear);
    try {
        getJsonLoader(skinFile).fromJson(Skin.class, skinFile);
    } catch (SerializationException ex) {
        throw new SerializationException("Error reading file: " + skinFile, ex);
    }
}

