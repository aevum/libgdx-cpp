
#ifndef GDXCPP_APPLICATION_LISTENER_H
#define GDXCPP_APPLICATION_LISTENER_H

namespace gdx_cpp {
  
class ApplicationListener {
    /** Called when the {@link Application} is first created. */
    virtual void create () = 0;

    /** Called when the {@link Application} is resumed from a paused state. On Android this happens when the activity gets focus
     * again. On the desktop this method will never be called. */
    virtual void resume () = 0;

    /** Called when the {@link Application} should render itself. */
    virtual void render () = 0;

    /** Called when the {@link Application} is resized. This can happen at any point during a non-paused state but will never happen
     * before a call to {@link #create()}.
     *
     * @param width the new width in pixels
     * @param height the new height in pixels */
    virtual void resize (int width, int height) = 0;

    /** Called when the {@link Application} is paused. An Application is paused before it is destroyed, when a user pressed the Home
     * button on Android or an incoming call happend. On the desktop this will only be called immediately before {@link #dispose()}
     * is called. */
    virtual void pause () = 0;

    /** Called when the {@link Application} is destroyed. Preceded by a call to {@link #pause()}. */
    virtual void dispose () = 0;
};

}

#endif // GDXCPP_APPLICATION_LISTENER_H