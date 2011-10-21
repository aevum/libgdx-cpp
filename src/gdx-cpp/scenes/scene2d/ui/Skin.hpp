
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class Skin: public gdx_cpp::utils::Disposable {
public:
    void dispose ();
    void setTexture (const gdx_cpp::graphics::Texture& texture);
    gdx_cpp::graphics::Texture& getTexture ();
    void save (const gdx_cpp::files::FileHandle& skinFile);
    void write (const gdx_cpp::utils::Json& json,const Object& object,const Class& valueType);
    Object& read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type);
    void write (const gdx_cpp::utils::Json& json,const Skin& skin,const Class& valueType);
    Skin& read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& ignored);
    void write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::TextureRegion& region,const Class& valueType);
    gdx_cpp::graphics::g2d::TextureRegion& read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type);
    void write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::BitmapFont& font,const Class& valueType);
    gdx_cpp::graphics::g2d::BitmapFont& read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type);
    void write (const gdx_cpp::utils::Json& json,const gdx_cpp::graphics::g2d::NinePatch& ninePatch,const Class& valueType);
    gdx_cpp::graphics::g2d::NinePatch& read (const gdx_cpp::utils::Json& json,const Object& jsonData,const Class& type);
    Skin ();
    Skin (const gdx_cpp::files::FileHandle& skinFile,const gdx_cpp::files::FileHandle& textureFile);
    Skin (const gdx_cpp::files::FileHandle& skinFile,const SkinData& data);
    ObjectMap<Class, ObjectMap<String, Object>> resources = new ObjectMap();
    Texture texture ;

protected:
    gdx_cpp::utils::Json& getJsonLoader (const final& FileHandle);
    ObjectMap<Class, ObjectMap<String, Object>> styles = new ObjectMap();
    SkinData data ;
    ObjectMap<String, Object> typeResources = data.resources.get(resource.getClass());
    ObjectMap<String, Object> typeResources = data.resources.get(type);
    Object resource = typeResources.get(name);
    ObjectMap<String, Object> typeStyles = styles.get(style.getClass());
    ObjectMap<String, Object> typeStyles = styles.get(type);
    Object style = typeStyles.get(name);

private:
    void readTypeMap (const gdx_cpp::utils::Json& json,gdx_cpp::utils::ObjectMapString, ObjectMap>& typeToValueMap,bool isResource);
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_SKIN_HPP_
