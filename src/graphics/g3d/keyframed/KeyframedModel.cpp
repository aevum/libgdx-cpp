
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

#include "KeyframedModel.hpp"

using namespace gdx_cpp::graphics::g3d::keyframed;

gdx_cpp::graphics::g3d::Animator& KeyframedModel::getAnimator () {
    return animator;
}

void KeyframedModel::setMaterials () {
    materials = new Material[mats.length];
    for (int i = 0; i < mats.length; i++) {
        materials[i] = mats[i];
    }
}

void KeyframedModel::setTaggedJoints (const ArrayList<String>& joints) {
    taggedJointNames = joints;
}

KeyframeAnimation& KeyframedModel::sampleAnimationFromMD5 (const gdx_cpp::graphics::g3d::loaders::md5::MD5Model& md5model,const gdx_cpp::graphics::g3d::loaders::md5::MD5Renderer& md5renderer,const gdx_cpp::graphics::g3d::loaders::md5::MD5Animator& md5animator,const gdx_cpp::graphics::g3d::loaders::md5::MD5Animation& md5animation,float sampleRate,const std::string& modelAsset,const std::string& animKey) {
    this.assetName = modelAsset;
    numMeshes = md5model.meshes.length;
    boolean cached = false;

    if (animator == null) {
        animator = new KeyframeAnimator(numMeshes, sampleRate);
        target = new Mesh[numMeshes];
        visible = new boolean[numMeshes];
        for (int i = 0; i < visible.length; i++) {
            visible[i] = true;
        }
    }

    if (animations == null) {
        animations = new ObjectMap<String, KeyframeAnimation>();
    }
    String key = modelAsset + "_" + animKey;

    KeyframeAnimation a = null;
    if (animations.containsKey(key)) {
        a = animations.get(key);
        a.addRef();
        cached = true;
    }
    animationRefs.add(key);

    md5animator.setAnimation(md5animation, WrapMode.Clamp);

    float len = md5animation.frames.length * md5animation.secondsPerFrame;
    int numSamples = (int)(len / sampleRate) + 1;

    if (!cached) {
        a = new KeyframeAnimation(md5animation.name, numSamples, len, sampleRate);
        animations.put(key, a);
    }

    md5animator.update(0.1f);
    md5renderer.setSkeleton(md5animator.getSkeleton());

    int i = 0;
    int numVertices = 0, numIndices = 0;
    for (float t = 0; t < len; t += sampleRate) {
        // store meshes.
        Keyframe k = null;
        if (!cached) {
            k = new Keyframe();
            k.vertices = new float[numMeshes][];
            k.indices = new short[numMeshes][];
            if (taggedJointNames.size() > 0) {
                k.taggedJointPos = new Vector3[taggedJointNames.size()];
                k.taggedJoint = new Quaternion[taggedJointNames.size()];
            }
        }
        for (int m = 0; m < numMeshes; m++) {
            float vertices[] = md5renderer.getVertices(m);
            short indices[] = md5renderer.getIndices(m);
            numVertices = vertices.length;
            numIndices = indices.length;
            if (!cached) {
                k.vertices[m] = new float[vertices.length];
                k.vertices[m] = vertices.clone();
                k.indices[m] = new short[indices.length];
                k.indices[m] = indices.clone();
            }

            if (target[m] == null) {
                animator.setKeyframeDimensions(m, numVertices, numIndices);
                animator.setNumTaggedJoints(taggedJointNames.size());

                VertexAttributes attribs = md5renderer.getMesh().getVertexAttributes();
                target[m] = new Mesh(false, numVertices, numIndices, attribs);
                if (target[m].getVertexSize() / 4 != KeyframeAnimator.sStride)
                    throw new GdxRuntimeException("Mesh vertexattributes != 8 - is this a valid MD5 source mesh?");
            }
        }

        if (!cached) {
            // store tagged joints.
            MD5Joints skel = md5animator.getSkeleton();
            for (int tj = 0; tj < taggedJointNames.size(); tj++) {
                String name = taggedJointNames.get(tj);
                for (int j = 0; j < skel.numJoints; j++) {
                    if (name.equals(skel.names[j])) {
                        int idx = j * 8;
                        // FIXME what is this? float p = skel.joints[idx];
                        float x = skel.joints[idx + 1];
                        float y = skel.joints[idx + 2];
                        float z = skel.joints[idx + 3];
                        k.taggedJointPos[tj] = new Vector3(x, y, z);
                        float qx = skel.joints[idx + 4];
                        float qy = skel.joints[idx + 5];
                        float qz = skel.joints[idx + 6];
                        float qw = skel.joints[idx + 7];
                        k.taggedJoint[tj] = new Quaternion(qx, qy, qz, qw);
                        break;
                    }
                }
            }

            a.keyframes[i] = k;
        }
        md5animator.update(sampleRate);
        md5renderer.setSkeleton(md5animator.getSkeleton());
        i++;
    }

    if (cached) {
        // Gdx.app.log("Loader",
// "Added ref to animation "+key+" - keyframes ("+i+" keyframes generated). animations.size = "+animations.size);
    } else {
        // Gdx.app.log("Loader",
// "Loaded animation "+key+" - keyframes ("+i+" keyframes generated). animations.size = "+animations.size);
    }

    return a;
}

void KeyframedModel::getJointData (int tagIndex,const gdx_cpp::math::Vector3& pos,const gdx_cpp::math::Quaternion& orient) {
    Keyframe kf = animator.getInterpolatedKeyframe();
    pos.set(kf.taggedJointPos[tagIndex]);
    orient.x = kf.taggedJoint[tagIndex].x;
    orient.y = kf.taggedJoint[tagIndex].y;
    orient.z = kf.taggedJoint[tagIndex].z;
    orient.w = kf.taggedJoint[tagIndex].w;
}

void KeyframedModel::setAnimation (const std::string& animKey,const gdx_cpp::graphics::g3d::Animator::WrapMode& wrapMode) {
    KeyframeAnimation anim = getAnimation(animKey);
    if (anim != null) {
        animator.setAnimation(anim, wrapMode);
        animator.getInterpolatedKeyframe().indicesSet = false;
        animator.getInterpolatedKeyframe().indicesSent = false;
    }
}

KeyframeAnimation& KeyframedModel::getAnimation (const std::string& animKey) {
    return animations.get(assetName + "_" + animKey);
}

void KeyframedModel::update (float dt) {
    if (animator != null) {
        animator.update(dt);

        if (animator.hasAnimation()) {
            Keyframe ikf = animator.getInterpolatedKeyframe();

            if (animator.getCurrentWrapMode() == WrapMode.SingleFrame && ikf.indicesSent) return; /*
																																	 * early out for single frame
																																	 * animations
																																	 */

            // send our target index and vertex data to the target mesh
            for (int i = 0; i < numMeshes; i++) {
                target[i].setVertices(ikf.vertices[i]);
                if (!ikf.indicesSent) {
                    target[i].setIndices(ikf.indices[i]);
                }
            }
            ikf.indicesSent = true;
        }
    }
}

void KeyframedModel::render () {
    for (int i = 0; i < numMeshes; i++) {
        // bind textures etc.
        Material mat = materials[i];
        if (mat != null) {
            if (mat.Texture != null) {
                mat.Texture.bind();
            }
            mat.set(GL10.GL_FRONT);
        }
        if (visible[i]) target[i].render(GL10.GL_TRIANGLES, 0, target[i].getNumIndices());
    }
}

void KeyframedModel::setMeshVisible (int idx,bool visible) {
    this.visible[idx] = visible;
}

void KeyframedModel::dispose () {
for (String key : animationRefs) {
        KeyframeAnimation anim = animations.get(key);
        if (anim.removeRef() == 0) {
            // Gdx.app.log("Engine", "Removing anim "+key+" from dict. Dict size = "+animations.size);
            animations.remove(key);
        }
    }
for (Mesh m : target) {
        if (m != null) {
            m.dispose();
        }
    }
    // Gdx.app.log("Engine", "Disposed kfmodel "+this.assetName+", "+animations.size+" anims remain in cache");
}

