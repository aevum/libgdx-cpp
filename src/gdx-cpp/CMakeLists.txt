
file(GLOB GDX_HEADERS
Files.hpp
Input.hpp
# scenes/scene2d/Group.hpp
# scenes/scene2d/Stage.hpp
# scenes/scene2d/CompositeAction.hpp
# scenes/scene2d/TemporalAction.hpp
# scenes/scene2d/AnimationAction.hpp
# scenes/scene2d/OnActionCompleted.hpp
# scenes/scene2d/Interpolator.hpp
# scenes/scene2d/actors/Label.hpp
# scenes/scene2d/actors/FastImage.hpp
# scenes/scene2d/actors/Image.hpp
# scenes/scene2d/actors/BoundGroup.hpp
# scenes/scene2d/actors/ClickListener.hpp
# scenes/scene2d/actors/Button.hpp
# scenes/scene2d/actors/LinearGroup.hpp
# scenes/scene2d/interpolators/DecelerateInterpolator.hpp
# scenes/scene2d/interpolators/OvershootInterpolator.hpp
# scenes/scene2d/interpolators/AnticipateInterpolator.hpp
# scenes/scene2d/interpolators/AccelerateDecelerateInterpolator.hpp
# scenes/scene2d/interpolators/AccelerateInterpolator.hpp
# scenes/scene2d/interpolators/LinearInterpolator.hpp
# scenes/scene2d/Layout.hpp
# scenes/scene2d/ui/ImageToggleButton.hpp
# scenes/scene2d/ui/ImageButton.hpp
# scenes/scene2d/ui/Label.hpp
# scenes/scene2d/ui/ScrollPane.hpp
# scenes/scene2d/ui/ComboBox.hpp
# scenes/scene2d/ui/FlickScrollPane.hpp
# scenes/scene2d/ui/Window.hpp
# scenes/scene2d/ui/CheckBox.hpp
# scenes/scene2d/ui/List.hpp
# scenes/scene2d/ui/tablelayout/Cell.hpp
# scenes/scene2d/ui/tablelayout/Toolkit.hpp
# scenes/scene2d/ui/tablelayout/Table.hpp
# scenes/scene2d/ui/tablelayout/TableLayout.hpp
# scenes/scene2d/ui/tablelayout/TableLayoutParser.hpp
# scenes/scene2d/ui/tablelayout/ParseException.hpp
# scenes/scene2d/ui/tablelayout/LibgdxToolkit.hpp
# scenes/scene2d/ui/tablelayout/BaseTableLayout.hpp
# scenes/scene2d/ui/Skin.hpp
# scenes/scene2d/ui/TextField.hpp
# scenes/scene2d/ui/Slider.hpp
# scenes/scene2d/ui/Widget.hpp
# scenes/scene2d/ui/ToggleButton.hpp
# scenes/scene2d/ui/Stack.hpp
# scenes/scene2d/ui/SplitPane.hpp
# scenes/scene2d/ui/utils/ScissorStack.hpp
# scenes/scene2d/ui/utils/DesktopClipboard.hpp
# scenes/scene2d/ui/utils/AndroidClipboard.hpp
# scenes/scene2d/ui/utils/Clipboard.hpp
# scenes/scene2d/ui/Button.hpp
# scenes/scene2d/ui/Pane.hpp
# scenes/scene2d/Actor.hpp
# scenes/scene2d/Action.hpp
# scenes/scene2d/actions/Delay.hpp
# scenes/scene2d/actions/Remove.hpp
# scenes/scene2d/actions/FadeIn.hpp
# scenes/scene2d/actions/FadeTo.hpp
# scenes/scene2d/actions/FadeOut.hpp
# scenes/scene2d/actions/Sequence.hpp
# scenes/scene2d/actions/RotateBy.hpp
# scenes/scene2d/actions/ActionResetingPool.hpp
# scenes/scene2d/actions/Parallel.hpp
# scenes/scene2d/actions/Forever.hpp
# scenes/scene2d/actions/RotateTo.hpp
# scenes/scene2d/actions/ScaleTo.hpp
# scenes/scene2d/actions/Repeat.hpp
# scenes/scene2d/actions/MoveTo.hpp
# scenes/scene2d/actions/MoveBy.hpp
ApplicationListener.hpp
audio/AudioDevice.hpp
audio/analysis/NativeFFT.hpp
audio/analysis/KissFFT.hpp
audio/analysis/ThresholdFunction.hpp
audio/analysis/FourierTransform.hpp
audio/analysis/DFT.hpp
audio/analysis/FFT.hpp
audio/Music.hpp
audio/Sound.hpp
audio/io/Mpg123Decoder.hpp
audio/io/Decoder.hpp
audio/io/VorbisDecoder.hpp
audio/AudioRecorder.hpp
# input/RemoteSender.hpp
# input/RemoteInput.hpp
Screen.hpp
Graphics.hpp
# files/FileHandle.hpp
# files/FileHandleStream.hpp
Gdx.hpp
implementation/MutexFactory.hpp
implementation/Thread.hpp
implementation/Mutex.hpp
implementation/ThreadFactory.hpp
Audio.hpp
Application.hpp
math/MathUtils.hpp
math/WindowedMean.hpp
math/Vector2.hpp
math/collision/Ray.hpp
math/collision/Sphere.hpp
math/collision/Segment.hpp
math/collision/BoundingBox.hpp
math/Matrix3.hpp
math/Quaternion.hpp
math/Matrix4.hpp
math/Rectangle.hpp
math/Plane.hpp
math/EarClippingTriangulator.hpp
math/Polygon.hpp
math/Intersector.hpp
math/Circle.hpp
math/Frustum.hpp
math/CatmullRomSpline.hpp
math/Vector3.hpp
graphics/Texture.hpp
graphics/Pixmap.hpp
graphics/VertexAttribute.hpp
graphics/GL11.hpp
graphics/TextureDict.hpp
graphics/Mesh.hpp
graphics/Camera.hpp
graphics/PerspectiveCamera.hpp
graphics/glutils/ImmediateModeRenderer20.hpp
graphics/glutils/VertexArray.hpp
graphics/glutils/IndexBufferObject.hpp
graphics/glutils/MipMapGenerator.hpp
graphics/glutils/ShaderProgram.hpp
graphics/glutils/IndexData.hpp
graphics/glutils/VertexBufferObject.hpp
graphics/glutils/ETC1TextureData.hpp
graphics/glutils/IndexBufferObjectSubData.hpp
graphics/glutils/ImmediateModeRenderer10.hpp
graphics/glutils/FileTextureData.hpp
graphics/glutils/VertexBufferObjectSubData.hpp
graphics/glutils/FrameBuffer.hpp
graphics/glutils/ImmediateModeRenderer.hpp
graphics/glutils/ETC1.hpp
graphics/glutils/VertexData.hpp
graphics/glutils/PixmapTextureData.hpp
graphics/GLU.hpp
graphics/VertexAttributes.hpp
graphics/TextureRef.hpp
graphics/GL10.hpp
graphics/TextureData.hpp
graphics/GLCommon.hpp
graphics/g3d/Animation.hpp
graphics/g3d/Animator.hpp
graphics/g3d/decals/GroupStrategy.hpp
graphics/g3d/decals/DefaultGroupStrategy.hpp
graphics/g3d/decals/GroupPlug.hpp
graphics/g3d/decals/DecalBatch.hpp
graphics/g3d/decals/PluggableGroupStrategy.hpp
graphics/g3d/decals/SimpleOrthoGroupStrategy.hpp
graphics/g3d/decals/Decal.hpp
graphics/g3d/decals/CameraGroupStrategy.hpp
graphics/g3d/decals/DecalMaterial.hpp
graphics/g3d/loaders/obj/ObjLoader.hpp
graphics/g3d/loaders/ModelLoaderOld.hpp
graphics/g3d/loaders/md5/MD5Animator.hpp
graphics/g3d/loaders/md5/MD5Quaternion.hpp
graphics/g3d/loaders/md5/MD5Mesh.hpp
graphics/g3d/loaders/md5/MD5Renderer.hpp
graphics/g3d/loaders/md5/MD5Model.hpp
graphics/g3d/loaders/md5/MD5Joints.hpp
graphics/g3d/loaders/md5/MD5Loader.hpp
graphics/g3d/loaders/md5/MD5Animation.hpp
graphics/g3d/loaders/md5/MD5Jni.hpp
graphics/g3d/loaders/md5/MD5AnimationInfo.hpp
graphics/g3d/Material.hpp
graphics/g3d/keyframed/Keyframe.hpp
graphics/g3d/keyframed/KeyframeAnimator.hpp
graphics/g3d/keyframed/KeyframedModel.hpp
graphics/g3d/keyframed/KeyframeAnimation.hpp
graphics/g2d/BitmapFontCache.hpp
graphics/g2d/Animation.hpp
graphics/g2d/BitmapFont.hpp
graphics/g2d/TextureRegion.hpp
graphics/g2d/SpriteCache.hpp
graphics/g2d/ParticleEffect.hpp
graphics/g2d/TextureAtlas.hpp
graphics/g2d/NinePatch.hpp
graphics/g2d/ParticleEmitter.hpp
graphics/g2d/Sprite.hpp
graphics/g2d/EmptyNinePatch.hpp
graphics/g2d/SpriteBatch.hpp
graphics/g2d/tiled/TiledLayer.hpp
graphics/g2d/tiled/SimpleTileAtlas.hpp
graphics/g2d/tiled/TileMapRenderer.hpp
graphics/g2d/tiled/TiledObject.hpp
graphics/g2d/tiled/TiledMap.hpp
graphics/g2d/tiled/TileAtlas.hpp
graphics/g2d/tiled/TiledObjectGroup.hpp
graphics/g2d/tiled/TileSet.hpp
graphics/g2d/tiled/TiledLoader.hpp
graphics/g2d/Gdx2DPixmap.hpp
graphics/FPSLogger.hpp
graphics/OrthographicCamera.hpp
graphics/Color.hpp
graphics/GL20.hpp
Game.hpp
InputProcessor.hpp
# utils/LittleEndianInputStream.hpp
# utils/TimSort.hpp
# utils/Base64Coder.hpp
# utils/Buffer.hpp
# utils/BufferUtils.hpp
# utils/PooledLinkedList.hpp
# utils/ScreenUtils.hpp
# utils/GdxRuntimeException.hpp
# utils/IntMap.hpp
# utils/Sort.hpp
# utils/AtomicQueue.hpp
# utils/Json.hpp
# utils/IntArray.hpp
# utils/IdentityMap.hpp
# utils/Runnable.hpp
# utils/MatrixBase.hpp
# utils/Disposable.hpp
# utils/Pool.hpp
# utils/SerializationException.hpp
# utils/LockGuard.hpp
# utils/Array.hpp
# utils/PauseableThread.hpp
# utils/FloatArray.hpp
# utils/GdxNativesLoader.hpp
# utils/JsonWriter.hpp
# utils/Synchronized.hpp
# utils/LongArray.hpp
# utils/Logger.hpp
# utils/ArrayBase.hpp
# utils/XmlReader.hpp
# utils/XmlWriter.hpp
# utils/gzstream.hpp
# utils/ObjectMap.hpp
# utils/NumberUtils.hpp
# utils/SortedIntList.hpp
# utils/ComparableTimSort.hpp
# utils/LongMap.hpp
# utils/Aliases.hpp
# utils/JsonReader.hpp
# Version.hpp
# physics/box2d/PolygonShape.hpp
# physics/box2d/JointEdge.hpp
# physics/box2d/Transform.hpp
# physics/box2d/Body.hpp
# physics/box2d/QueryCallback.hpp
# physics/box2d/CircleShape.hpp
# physics/box2d/JointDef.hpp
# physics/box2d/ContactImpulse.hpp
# physics/box2d/Shape.hpp
# physics/box2d/Manifold.hpp
# physics/box2d/ContactFilter.hpp
# physics/box2d/Box2DDebugRenderer.hpp
# physics/box2d/WorldManifold.hpp
# physics/box2d/Filter.hpp
# physics/box2d/ContactListener.hpp
# physics/box2d/FixtureDef.hpp
# physics/box2d/World.hpp
# physics/box2d/Fixture.hpp
# physics/box2d/RayCastCallback.hpp
# physics/box2d/MassData.hpp
# physics/box2d/joints/DistanceJointDef.hpp
# physics/box2d/joints/PrismaticJoint.hpp
# physics/box2d/joints/MouseJoint.hpp
# physics/box2d/joints/FrictionJointDef.hpp
# physics/box2d/joints/RevoluteJointDef.hpp
# physics/box2d/joints/WeldJointDef.hpp
# physics/box2d/joints/FrictionJoint.hpp
# physics/box2d/joints/PulleyJointDef.hpp
# physics/box2d/joints/LineJoint.hpp
# physics/box2d/joints/GearJoint.hpp
# physics/box2d/joints/PulleyJoint.hpp
# physics/box2d/joints/MouseJointDef.hpp
# physics/box2d/joints/GearJointDef.hpp
# physics/box2d/joints/RevoluteJoint.hpp
# physics/box2d/joints/LineJointDef.hpp
# physics/box2d/joints/DistanceJoint.hpp
# physics/box2d/joints/WeldJoint.hpp
# physics/box2d/joints/PrismaticJointDef.hpp
# physics/box2d/Contact.hpp
# physics/box2d/DestructionListener.hpp
# physics/box2d/Joint.hpp
# physics/box2d/BodyDef.hpp
Preferences.hpp
InputMultiplexer.hpp
InputAdapter.hpp)

set(GDX_SRC
Version.cpp
# assets/AssetLoadingTask.cpp
# assets/AssetManager.cpp
# assets/loaders/BitmapFontLoader.cpp
# assets/loaders/TextureParameter.cpp
# assets/loaders/MusicLoader.cpp
# assets/loaders/SynchronousAssetLoader.cpp
# assets/loaders/PixmapParameter.cpp
# assets/loaders/TextureAtlasLoader.cpp
# assets/loaders/MusicParameter.cpp
# assets/loaders/AsynchronousAssetLoader.cpp
# assets/loaders/resolvers/InternalFileHandleResolver.cpp
# assets/loaders/resolvers/ExternalFileHandleResolver.cpp
# assets/loaders/SoundLoader.cpp
# assets/loaders/TextureLoader.cpp
# assets/loaders/PixmapLoader.cpp
# assets/loaders/SoundParameter.cpp
# assets/loaders/TextureAtlasParameter.cpp
# assets/AssetType.cpp
# assets/AssetDescriptor.cpp
# scenes/scene2d/Stage.cpp
# scenes/scene2d/Action.cpp
# scenes/scene2d/TemporalAction.cpp
# scenes/scene2d/actors/Image.cpp
# scenes/scene2d/actors/LinearGroup.cpp
# scenes/scene2d/actors/Button.cpp
# scenes/scene2d/actors/Label.cpp
# scenes/scene2d/actors/FastImage.cpp
# scenes/scene2d/actors/BoundGroup.cpp
# scenes/scene2d/AnimationAction.cpp
# scenes/scene2d/Group.cpp
# scenes/scene2d/interpolators/AccelerateInterpolator.cpp
# scenes/scene2d/interpolators/OvershootInterpolator.cpp
# scenes/scene2d/interpolators/AnticipateInterpolator.cpp
# scenes/scene2d/interpolators/LinearInterpolator.cpp
# scenes/scene2d/interpolators/AccelerateDecelerateInterpolator.cpp
# scenes/scene2d/interpolators/DecelerateInterpolator.cpp
# scenes/scene2d/ui/ImageToggleButton.cpp
# scenes/scene2d/ui/Widget.cpp
# scenes/scene2d/ui/Pane.cpp
# scenes/scene2d/ui/FlickScrollPane.cpp
# scenes/scene2d/ui/TextField.cpp
# scenes/scene2d/ui/Button.cpp
# scenes/scene2d/ui/ScrollPane.cpp
# scenes/scene2d/ui/Slider.cpp
# scenes/scene2d/ui/Skin.cpp
# scenes/scene2d/ui/CheckBox.cpp
# scenes/scene2d/ui/tablelayout/LibgdxToolkit.cpp
# scenes/scene2d/ui/tablelayout/ParseException.cpp
# scenes/scene2d/ui/tablelayout/TableLayout.cpp
# scenes/scene2d/ui/tablelayout/Cell.cpp
# scenes/scene2d/ui/tablelayout/Table.cpp
# scenes/scene2d/ui/tablelayout/BaseTableLayout.cpp
# scenes/scene2d/ui/tablelayout/TableLayoutParser.cpp
# scenes/scene2d/ui/tablelayout/Toolkit.cpp
# scenes/scene2d/ui/SplitPane.cpp
# scenes/scene2d/ui/ToggleButton.cpp
# scenes/scene2d/ui/Window.cpp
# scenes/scene2d/ui/Label.cpp
# scenes/scene2d/ui/utils/ScissorStack.cpp
# scenes/scene2d/ui/utils/AndroidClipboard.cpp
# scenes/scene2d/ui/utils/Clipboard.cpp
# scenes/scene2d/ui/utils/DesktopClipboard.cpp
# scenes/scene2d/ui/List.cpp
# scenes/scene2d/ui/Stack.cpp
# scenes/scene2d/ui/ImageButton.cpp
# scenes/scene2d/ui/ComboBox.cpp
# scenes/scene2d/actions/ActionResetingPool.cpp
# scenes/scene2d/actions/Parallel.cpp
# scenes/scene2d/actions/Forever.cpp
# scenes/scene2d/actions/MoveTo.cpp
# scenes/scene2d/actions/MoveBy.cpp
# scenes/scene2d/actions/Remove.cpp
# scenes/scene2d/actions/FadeIn.cpp
# scenes/scene2d/actions/FadeTo.cpp
# scenes/scene2d/actions/ScaleTo.cpp
# scenes/scene2d/actions/RotateTo.cpp
# scenes/scene2d/actions/Sequence.cpp
# scenes/scene2d/actions/FadeOut.cpp
# scenes/scene2d/actions/Repeat.cpp
# scenes/scene2d/actions/Delay.cpp
# scenes/scene2d/actions/RotateBy.cpp
# scenes/scene2d/Actor.cpp
# scenes/scene2d/CompositeAction.cpp
audio/analysis/ThresholdFunction.cpp
audio/analysis/NativeFFT.cpp
audio/analysis/KissFFT.cpp
audio/analysis/DFT.cpp
audio/analysis/FourierTransform.cpp
audio/analysis/FFT.cpp
audio/io/Mpg123Decoder.cpp
audio/io/VorbisDecoder.cpp
InputMultiplexer.cpp
# input/RemoteSender.cpp
# input/RemoteInput.cpp
# files/FileHandle.cpp
# files/FileHandleStream.cpp
math/Circle.cpp
math/Matrix4.cpp
math/WindowedMean.cpp
math/Polygon.cpp
math/Rectangle.cpp
math/Vector2.cpp
math/Vector3.cpp
math/collision/Sphere.cpp
math/collision/Segment.cpp
math/collision/Ray.cpp
math/collision/BoundingBox.cpp
math/Quaternion.cpp
math/Plane.cpp
math/Intersector.cpp
math/CatmullRomSpline.cpp
math/Matrix3.cpp
math/Frustum.cpp
math/EarClippingTriangulator.cpp
graphics/PerspectiveCamera.cpp
graphics/Color.cpp
graphics/VertexAttributes.cpp
graphics/Mesh.cpp
graphics/VertexAttribute.cpp
# graphics/Texture.cpp
graphics/glutils/MipMapGenerator.cpp
# graphics/glutils/FileTextureData.cpp
graphics/glutils/VertexBufferObject.cpp
# graphics/glutils/ImmediateModeRenderer10.cpp
graphics/glutils/IndexBufferObjectSubData.cpp
graphics/glutils/FrameBuffer.cpp
graphics/glutils/PixmapTextureData.cpp
graphics/glutils/ShaderProgram.cpp
graphics/glutils/IndexBufferObject.cpp
graphics/glutils/VertexBufferObjectSubData.cpp
# graphics/glutils/ETC1.cpp
# graphics/glutils/ImmediateModeRenderer20.cpp
# graphics/glutils/ETC1TextureData.cpp
graphics/glutils/VertexArray.cpp
graphics/TextureDict.cpp
graphics/FPSLogger.cpp
graphics/Pixmap.cpp
# graphics/g3d/decals/DefaultGroupStrategy.cpp
# graphics/g3d/decals/SimpleOrthoGroupStrategy.cpp
# graphics/g3d/decals/DecalMaterial.cpp
# graphics/g3d/decals/CameraGroupStrategy.cpp
# graphics/g3d/decals/PluggableGroupStrategy.cpp
# graphics/g3d/decals/DecalBatch.cpp
# graphics/g3d/decals/Decal.cpp
# graphics/g3d/Material.cpp
# graphics/g3d/loaders/obj/ObjLoader.cpp
# graphics/g3d/loaders/md5/MD5Animation.cpp
# graphics/g3d/loaders/md5/MD5Animator.cpp
# graphics/g3d/loaders/md5/MD5Quaternion.cpp
# graphics/g3d/loaders/md5/MD5AnimationInfo.cpp
# graphics/g3d/loaders/md5/MD5Joints.cpp
# graphics/g3d/loaders/md5/MD5Renderer.cpp
# graphics/g3d/loaders/md5/MD5Model.cpp
# graphics/g3d/loaders/md5/MD5Mesh.cpp
# graphics/g3d/loaders/md5/MD5Jni.cpp
# graphics/g3d/loaders/md5/MD5Loader.cpp
# graphics/g3d/loaders/ModelLoaderOld.cpp
# graphics/g3d/Animation.cpp
# graphics/g3d/keyframed/KeyframeAnimation.cpp
# graphics/g3d/keyframed/Keyframe.cpp
# graphics/g3d/keyframed/KeyframedModel.cpp
# graphics/g3d/keyframed/KeyframeAnimator.cpp
# graphics/g3d/Animator.cpp
graphics/g2d/BitmapFont.cpp
graphics/g2d/BitmapFontCache.cpp
graphics/g2d/EmptyNinePatch.cpp
graphics/g2d/ParticleEmitter.cpp
graphics/g2d/SpriteBatch.cpp
graphics/g2d/SpriteCache.cpp
graphics/g2d/NinePatch.cpp
graphics/g2d/Gdx2DPixmap.cpp
# graphics/g2d/tiled/TileSet.cpp
# graphics/g2d/tiled/TileAtlas.cpp
# graphics/g2d/tiled/TileMapRenderer.cpp
# graphics/g2d/tiled/TiledMap.cpp
# graphics/g2d/tiled/TiledLoader.cpp
# graphics/g2d/tiled/SimpleTileAtlas.cpp
# graphics/g2d/tiled/TiledObject.cpp
# graphics/g2d/tiled/TiledObjectGroup.cpp
# graphics/g2d/tiled/TiledLayer.cpp
graphics/g2d/TextureRegion.cpp
graphics/g2d/ParticleEffect.cpp
graphics/g2d/Animation.cpp
graphics/g2d/Sprite.cpp
graphics/g2d/TextureAtlas.cpp
graphics/OrthographicCamera.cpp
graphics/TextureRef.cpp
graphics/Camera.cpp
# utils/Sort.cpp
utils/gzstream.cpp
# utils/LongMap.cpp
# utils/LongArray.cpp
# utils/JsonReader.cpp
# utils/XmlWriter.cpp
# utils/FloatArray.cpp
# utils/JsonWriter.cpp
# utils/AtomicQueue.cpp
# utils/TimSort.cpp
# utils/GdxRuntimeException.cpp
# utils/PauseableThread.cpp
# utils/PooledLinkedList.cpp
utils/Base64Coder.cpp
# utils/ObjectMap.cpp
# utils/Logger.cpp
# utils/SortedIntList.cpp
# utils/XmlReader.cpp
# utils/ComparableTimSort.cpp
# utils/IdentityMap.cpp
# utils/BufferUtils.cpp
# utils/SerializationException.cpp
# utils/GdxNativesLoader.cpp
# utils/Pool.cpp
utils/NumberUtils.cpp
# utils/LittleEndianInputStream.cpp
# utils/IntArray.cpp
# utils/Array.cpp
# utils/ScreenUtils.cpp
# utils/IntMap.cpp
# utils/Json.cpp
# physics/box2d/PolygonShape.cpp
# physics/box2d/JointDef.cpp
# physics/box2d/Joint.cpp
# physics/box2d/CircleShape.cpp
# physics/box2d/Box2DDebugRenderer.cpp
# physics/box2d/World.cpp
# physics/box2d/Transform.cpp
# physics/box2d/MassData.cpp
# physics/box2d/Contact.cpp
# physics/box2d/Manifold.cpp
# physics/box2d/Shape.cpp
# physics/box2d/ContactImpulse.cpp
# physics/box2d/Filter.cpp
# physics/box2d/WorldManifold.cpp
# physics/box2d/Fixture.cpp
# physics/box2d/BodyDef.cpp
# physics/box2d/FixtureDef.cpp
# physics/box2d/JointEdge.cpp
# physics/box2d/joints/PulleyJointDef.cpp
# physics/box2d/joints/WeldJointDef.cpp
# physics/box2d/joints/MouseJointDef.cpp
# physics/box2d/joints/GearJointDef.cpp
# physics/box2d/joints/RevoluteJointDef.cpp
# physics/box2d/joints/DistanceJointDef.cpp
# physics/box2d/joints/FrictionJointDef.cpp
# physics/box2d/joints/WeldJoint.cpp
# physics/box2d/joints/DistanceJoint.cpp
# physics/box2d/joints/FrictionJoint.cpp
# physics/box2d/joints/RevoluteJoint.cpp
# physics/box2d/joints/PulleyJoint.cpp
# physics/box2d/joints/GearJoint.cpp
# physics/box2d/joints/LineJoint.cpp
# physics/box2d/joints/LineJointDef.cpp
# physics/box2d/joints/MouseJoint.cpp
# physics/box2d/joints/PrismaticJoint.cpp
# physics/box2d/joints/PrismaticJointDef.cpp
# physics/box2d/Body.cpp
Game.cpp
InputAdapter.cpp
Gdx.cpp)

install(DIRECTORY src DESTINATION include/gdx-cpp
          FILES_MATCHING PATTERN "*.hpp")

add_library(gdx-cpp SHARED ${GDX_HEADERS} ${GDX_SRC})
