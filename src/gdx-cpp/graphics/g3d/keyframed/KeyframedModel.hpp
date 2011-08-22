
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

#ifndef GDX_CPP_GRAPHICS_G3D_KEYFRAMED_KEYFRAMEDMODEL_HPP_
#define GDX_CPP_GRAPHICS_G3D_KEYFRAMED_KEYFRAMEDMODEL_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace keyframed {

class KeyframedModel {
public:
    gdx_cpp::graphics::g3d::Animator& getAnimator ();
    void setMaterials ();
    void setTaggedJoints (const ArrayList<String>& joints);
    KeyframeAnimation& sampleAnimationFromMD5 (const gdx_cpp::graphics::g3d::loaders::md5::MD5Model& md5model,const gdx_cpp::graphics::g3d::loaders::md5::MD5Renderer& md5renderer,const gdx_cpp::graphics::g3d::loaders::md5::MD5Animator& md5animator,const gdx_cpp::graphics::g3d::loaders::md5::MD5Animation& md5animation,float sampleRate,const std::string& modelAsset,const std::string& animKey);
    void getJointData (int tagIndex,const gdx_cpp::math::Vector3& pos,const gdx_cpp::math::Quaternion& orient);
    void setAnimation (const std::string& animKey,const gdx_cpp::graphics::g3d::Animator::WrapMode& wrapMode);
    KeyframeAnimation& getAnimation (const std::string& animKey);
    void update (float dt);
    void render ();
    void setMeshVisible (int idx,bool visible);
    void dispose ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace keyframed

#endif // GDX_CPP_GRAPHICS_G3D_KEYFRAMED_KEYFRAMEDMODEL_HPP_
