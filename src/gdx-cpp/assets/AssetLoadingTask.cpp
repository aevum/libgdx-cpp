
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

#include "AssetLoadingTask.hpp"

using namespace gdx;

Void& AssetLoadingTask::call () throws Exception {
    AsynchronousAssetLoader asyncLoader = (AsynchronousAssetLoader)loader;
    if (dependenciesLoaded == false) {
        Array<AssetDescriptor> dependencies = asyncLoader.getDependencies(assetDesc.fileName, assetDesc.params);
        if (dependencies != null) {
for (AssetDescriptor desc : dependencies) {
                manager.injectDependency(assetDesc.fileName, desc);
            }
        }
    } else {
        asyncLoader.loadAsync(manager, assetDesc.fileName, assetDesc.params);
    }
    return null;
}

bool AssetLoadingTask::update () {
    if (loader instanceof SynchronousAssetLoader) {
        handleSyncLoader();
    } else {
        handleAsyncLoader();
    }
    return asset != null;
}

void AssetLoadingTask::handleSyncLoader () {
    SynchronousAssetLoader syncLoader = (SynchronousAssetLoader)loader;
    if (!dependenciesLoaded) {
        dependenciesLoaded = true;
        Array<AssetDescriptor> dependencies = syncLoader.getDependencies(assetDesc.fileName, assetDesc.params);
        if (dependencies == null) {
            asset = syncLoader.load(manager, assetDesc.fileName, assetDesc.params);
            return;
        }
for (AssetDescriptor desc : dependencies) {
            manager.injectDependency(assetDesc.fileName, desc);
        }
    } else {
        asset = syncLoader.load(manager, assetDesc.fileName, assetDesc.params);
    }
}

void AssetLoadingTask::handleAsyncLoader () {
    AsynchronousAssetLoader asyncLoader = (AsynchronousAssetLoader)loader;
    if (!dependenciesLoaded) {
        if (depsFuture == null) {
            depsFuture = threadPool.submit(this);
        } else {
            if (depsFuture.isDone()) {
                try {
                    depsFuture.get();
                } catch (Exception e) {
                    throw new GdxRuntimeException("Couldn't load dependencies of asset '" + assetDesc.fileName + "'", e);
                }
                dependenciesLoaded = true;
            }
        }
    } else {
        if (loadFuture == null) {
            loadFuture = threadPool.submit(this);
        } else {
            if (loadFuture.isDone()) {
                try {
                    loadFuture.get();
                } catch (Exception e) {
                    throw new GdxRuntimeException("Couldn't load asset '" + assetDesc.fileName + "'", e);
                }
                asset = asyncLoader.loadSync();
            }
        }
    }
}

Object& AssetLoadingTask::getAsset () {
    return asset;
}

