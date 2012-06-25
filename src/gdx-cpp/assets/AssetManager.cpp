
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

#include "AssetManager.hpp"
#include "loaders/BitmapFontLoader.hpp"
#include "loaders/MusicLoader.hpp"
#include "loaders/PixmapLoader.hpp"
#include "loaders/SoundLoader.hpp"
#include "loaders/TextureAtlasLoader.hpp"
#include "loaders/TextureLoader.hpp"
#include "assets/AssetErrorListener.hpp"
#include "ReferenceCountedAsset.hpp"

using namespace gdx;

AssetManager::AssetManager() : errorListener(0), toLoad(0), loaded(0)
{
    setLoader(AssetType::BitmapFont, new BitmapFontLoader(new InternalFileHandleResolver()));
    setLoader(AssetType::Music, new MusicLoader(new InternalFileHandleResolver()));
    setLoader(AssetType::Pixmap, new PixmapLoader(new InternalFileHandleResolver()));
    setLoader(AssetType::Sound, new SoundLoader(new InternalFileHandleResolver()));
    setLoader(AssetType::TextureAtlas, new TextureAtlasLoader(new InternalFileHandleResolver()));
    setLoader(AssetType::Texture, new TextureLoader(new InternalFileHandleResolver()));
}


Thread& AssetManager::newThread (const Runnable& r) {
    Thread thread = new Thread(r, "AssetManager-Loader-Thread");
    thread.setDaemon(true);
    return thread;
}

void AssetManager::remove (const std::string& fileName) {
    // get the asset and its type
    Class type = assetTypes.get(fileName);
    if (type == null) throw new GdxRuntimeException("Asset '" + fileName + "' not loaded");
    Object asset = assets.get(type).get(fileName);

    // if it is disposable dispose it
    if (asset instanceof Disposable) ((Disposable)asset).dispose();

    // if it is reference counted, check if we can really get rid of it.
    if (asset instanceof ReferenceCountedAsset) {
        if (((ReferenceCountedAsset)asset).getRefCount() > 0) return;
    }

    // remove the asset from the manager.
    assetTypes.remove(fileName);
    assets.get(type).remove(fileName);

    // remove any dependencies (which might also be reference counted)
    Array<String> dependencies = assetDependencies.remove(fileName);
    if (dependencies != null) {
for (String dependency : dependencies) {
            remove(dependency);
        }
    }
}

bool AssetManager::isLoaded (const std::string& fileName) {
    return assetTypes.containsKey(fileName);
}

bool AssetManager::update () {
    try {
        if (tasks.size() == 0) {
            if (preloadQueue.size() == 0) return true;
            nextTask();
        }
        return updateTask() && preloadQueue.size == 0;
    } catch (Throwable t) {
        handleTaskError(t);
        return preloadQueue.size == 0;
    }
}

void AssetManager::nextTask () {
    AssetDescriptor::ptr assetDesc = preloadQueue.front();
    preloadQueue.pop_front();
    
    if (isLoaded(assetDesc->fileName)) {
        int type = assetTypes[assetDesc->fileName];
        Asset::ptr asset = assets[type][assetDesc->fileName];
        if (asset->isRefCounted()) {
            ((ReferenceCountedAsset*)asset)->incRefCount();
        }
    } else {
        addTask(assetDesc);
    }
}

void AssetManager::addTask (const AssetDescriptor& assetDesc) {
    AssetLoader loader = loaders.get(assetDesc.type);
    if (loader == null) throw new GdxRuntimeException("No loader for type '" + assetDesc.type.getSimpleName() + "'");
    tasks.push(new AssetLoadingTask(this, assetDesc, loader, threadPool));
}

bool AssetManager::updateTask () {
    AssetLoadingTask task = tasks.peek();
    // if the task has finished loading
    if (task.update()) {
        // add the asset to the filename lookup
        assetTypes.put(task.assetDesc.fileName, task.assetDesc.type);

        // add the asset to the type lookup
        ObjectMap<String, Object> typeToAssets = assets.get(task.assetDesc.type);
        if (typeToAssets == null) {
            typeToAssets = new ObjectMap<String, Object>();
            assets.put(task.assetDesc.type, typeToAssets);
        }
        typeToAssets.put(task.assetDesc.fileName, task.getAsset());

        // increase the ref count of all dependencies (and their dependencies)
        incrementRefCountedDependencies(task.assetDesc.fileName);

        // increase the number of loaded assets and pop the task from the stack
        loaded++;
        tasks.pop();
        return true;
    } else {
        return false;
    }
}

void AssetManager::incrementRefCountedDependencies (const std::string& parent) {
    Array<String> dependencies = assetDependencies.get(parent);
    if (dependencies == null) return;

for (String dependency : dependencies) {
        Class type = assetTypes.get(dependency);
        if (type == null) throw new GdxRuntimeException("Asset '" + dependency + "' not loaded");
        // if we found a reference counted dependency we increase the ref count
        Object asset = assets.get(type).get(dependency);
        if (asset instanceof ReferenceCountedAsset) {
            ((ReferenceCountedAsset)asset).incRefCount();
        }
        // otherwise we go deeper down the rabbit hole
        else {
            incrementRefCountedDependencies(dependency);
        }
    }
}

void AssetManager::handleTaskError (const Throwable& t) {
    // pop the faulty task from the stack
    AssetLoadingTask task = tasks.pop();
    AssetDescriptor assetDesc = task.assetDesc;

    if (listener != null) {
        listener.error(assetDesc.fileName, assetDesc.type, t);
    } else {
        throw new GdxRuntimeException(t);
    }
}

int AssetManager::getLoadedAssets () {
    return assetTypes.size;
}

int AssetManager::getQueuedAssets () {
    return preloadQueue.size + (tasks.size());
}

float AssetManager::getProgress () {
    return loaded / (float)toLoad;
}

void AssetManager::setErrorListener (const AssetErrorListener& listener) {
    this.listener = listener;
}

void AssetManager::dispose () {
    clear();
    threadPool.shutdown();
    try {
        threadPool.awaitTermination(Long.MAX_VALUE, TimeUnit.SECONDS);
    } catch (InterruptedException e) {
        new GdxRuntimeException("Couldn't shutdown loading thread");
    }
}

void AssetManager::clear () {
    if (preloadQueue.size > 0 || tasks.size() != 0) {
        try {
            while (!updateTask())
                ;
        } catch (Throwable t) {
            handleTaskError(t);
        }
    }

    Array<String> assets = assetTypes.keys().toArray();
for (String asset : assets) {
        remove(asset);
    }

    this.assets.clear();
    this.assetTypes.clear();
    this.assetDependencies.clear();
    this.loaded = 0;
    this.preloadQueue.clear();
    this.tasks.clear();
}

Logger& AssetManager::getLogger () {
    return log;
}

std::string& AssetManager::getDiagonistics () {
    Synchronizable::lock_holder hnd(synchronize());
     std::stringstream buffer;
     AssetTypeMap::iterator it = assetTypes.begin();
     AssetTypeMap::iterator end = assetTypes.end();
     
     for (; it != end; ++it)
        buffer << it->first << ", ";
        int type = assetTypes[it->first];
        Asset::ptr asset = assets[type][it->first];
        std::vector<std::string>& dependencies = assetDependencies[it->first];

        buffer << type;

        if (asset instanceof ReferenceCountedAsset) {
            buffer.append(", refs: ");
            buffer.append(((ReferenceCountedAsset)asset).getRefCount());
        }

        if (dependencies != null) {
            buffer.append(", deps: [");
for (String dep : dependencies) {
                buffer.append(dep);
                buffer.append(",");
            }
            buffer.append("]");
        }
        buffer.append("\n");
    }
    return buffer.toString();
}

void AssetManager::injectDependency(const std::string& parentAssetFilename,
                                    AssetDescriptor::ptr dependendAssetDesc) {
    // add the asset as a dependency of the parent asset

    std::vector<std::string>& dependencies = assetDependencies[parentAssetFilename];

    dependencies.push_back(dependendAssetDesc->fileName);

    // if the asset is already loaded, increase its reference count if needed.
    if (isLoaded(dependendAssetDesc->fileName)) {
        int type = assetTypes[dependendAssetDesc->fileName];
        Asset::ptr asset = assets[type][dependendAssetDesc->fileName];
             if (asset->isRefCounted()) {
                 ((ReferenceCountedAsset*)asset).incRefCount();
             }
    }
    // else add a new task for the asset. if the asset is already on the preloading queue
    else {
        addTask(dependendAssetDesc);
    }

    gdx::Gdx::app->log("AssetManager.hpp") << "Injected dependency '" + dependendAssetDesc + "' for asset '" + parentAssetFilename + "'";
}

void AssetManager::setLoader(AssetType& type, AssetLoader* loader) {
    Synchronizable::lock_holder hnd(synchronize());
    loaders[type] = loader;
}

void AssetManager::preload(const std::string& fileName, AssetType& type) {
    AssetLoaderParameters::ptr null(NULL);
    preload(fileName, type, null);
}

void AssetManager::preload(const std::string& fileName, const AssetType& type, AssetLoaderParameters::ptr parameter) {
    Synchronizable::lock_holder hnd(synchronize());

    AssetLoader* loader = loaders[type];

    if (loader == NULL) {
        gdx::Gdx::app->error("AssetManager.hpp") << "No loader for type '" + type.getSimpleName() + "'";
    }

    if (isLoaded(fileName)) {
        gdx::Gdx::app->error("AssetManager.hpp") << "Asset '" + fileName + "' already loaded";
    }

    PreloadQueueType::iterator it = preloadQueue.begin();
    PreloadQueueType::iterator end = preloadQueue.end();

    for (; it != end; ++it) {
        if ((*it)->fileName == fileName) {
            gdx::Gdx::app->error("AssetManager.hpp") << "Asset '" + fileName + "' already in preload queue";
        }
    }

    if (preloadQueue.empty()) {
        loaded = 0;
        toLoad = 0;
    }

    toLoad++;

    AssetDescriptor::ptr assetDesc = AssetDescriptor::ptr(new AssetDescriptor(fileName, type, parameter));
    preloadQueue.push_back(assetDesc);

    gdx::Gdx::app->log("AssetManager.hpp") << "Added asset '" + assetDesc->toString() + "' to preload queue";
}

bool AssetManager::getAssetFileName(const Asset& asset, std::string& result) {
    Synchronizable::lock_holder hnd(synchronize());

    const AssetMap& typedAssets = assets[asset.getAssetType()];
    AssetMap::const_iterator it = typedAssets.begin();
    AssetMap::const_iterator end = typedAssets.end();

    for (; it != end; ++it) {
        Asset::ptr otherAsset = typedAssets[it->first];
        if (*otherAsset == asset) {
            result = *it;
            return true;
        }
    }

    return false;
}
