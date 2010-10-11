/*
 * Ork: a small object-oriented OpenGL Rendering Kernel.
 * Copyright (c) 2008-2010 INRIA
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

/*
 * Authors: Eric Bruneton, Antoine Begault, Guillaume Piolat.
 */

#ifndef _ORK_SHOW_INFO_TASK_H_
#define _ORK_SHOW_INFO_TASK_H_

#include <time.h>
#include "ork/render/Mesh.h"
#include "ork/render/Program.h"
#include "ork/scenegraph/AbstractTask.h"
#include "ork/util/Font.h"

using namespace ork::render;
using namespace ork::util;

namespace ork
{

namespace scenegraph
{

/**
 * An AbstractTask to display the framerate and other information.
 */
class ORK_API ShowInfoTask : public AbstractTask
{
public:
    /**
     * Creates a new ShowInfoTask.
     *
     * @param font the Font used to display Text.
     * @param p the program to be used to draw characters.
     * @param color the font color in RGBA8 format.
     * @param size the font height.
     * @param pos x,y position and maximum number of lines of text to display.
     */
    ShowInfoTask(Ptr<Font> font, Ptr<Program> p, int color, float size, vec3i pos);

    /**
     * Deletes this ShowInfoTask.
     */
    virtual ~ShowInfoTask();

    virtual Ptr<Task> getTask(Ptr<Object> context);

    /**
     * Adds an information to display. The information has a topic and replaces
     * the previous information in this topic. All the topics are cleared after
     * each frame (you have to set them at each frame if you want them to
     * persist on screen).
     *
     * @param topic the topic of the information.
     * @param info an information message.
     */
    static void setInfo(const string &topic, const string &info);

protected:
    /**
     * The mesh used to draw character quads, in order to display text.
     */
    static StaticPtr< Mesh<Font::Vertex, unsigned int> > fontMesh;

    /**
     * The current information messages, associated with their topic.
     */
    static map<string, string> infos;

    /**
     * The program use to draw characters.
     */
    Ptr<Program> fontProgram;

    /**
     * The uniform in #fontProgram used to control the font texture.
     */
    Ptr<UniformSampler> fontU;

    /**
     * The Font used to display Text.
     */
    Ptr<Font> font;

    /**
     * The font color in RGBA8 format.
     */
    int fontColor;

    /**
     * The used font height.
     */
    float fontHeight;

    /**
     * The x,y position and the maximum number of lines of text to be displayed.
     */
    vec3i position;

    /**
     * Creates an uninitialized ShowInfoTask.
     */
    ShowInfoTask();

    /**
     * Initializes this ShowInfoTask.
     *
     * @param font the Font used to display Text.
     * @param p the program to be used to draw characters.
     * @param color the font color in RGBA8 format.
     * @param size the font height.
     * @param pos x,y position and maximum number of lines of text to display.
     */
    virtual void init(Ptr<Font> font, Ptr<Program> p, int color, float size, vec3i pos);

    /**
     * Swaps this ShowInfoTask with another one.
     *
     * @param t a ShowInfoTask.
     */
    virtual void swap(Ptr<ShowInfoTask> t);

    /**
     * Draws a line of text.
     *
     * @param vp the framebuffer viewport, in pixels.
     * @param xs the x coordinate of the first character to display.
     * @param ys the y coordinate of the first character to display.
     * @param color the color of this line of text, in RGBA8 format.
     * @param s the line of text to display.
     */
    virtual void drawLine(const vec4f &vp, float xs, float ys, int color, const string &s);

    /**
     * Draws the framerate and the information messages.
     *
     * @param context the method to which this task belongs.
     */
    virtual void draw(Ptr<Method> context);

private:
    /**
     * The current framerate.
     */
    int fps;

    /**
     * The number of frames displayed since #start. This counter is periodically
     * reset to 0.
     */
    int frames;

    /**
     * The time at which the #frames counter was reset to 0.
     */
    double start;

    /**
     * A Task to display the framerate and other information.
     */
    class Impl : public Task
    {
    public:
        /**
         * Creates a new ShowInfoTask::Impl task.
         *
         * @param context the method to which 'source' belongs.
         * @param source the ShowInfoTask that created this task.
         */
        Impl(Ptr<Method> context, Ptr<ShowInfoTask> source);

        /**
         * Deletes this ShowInfoTask::Impl.
         */
        virtual ~Impl();

        virtual bool run();

    protected:
        virtual const type_info *getTypeInfo();

    private:
        /**
         * The method to which #source belongs.
         */
        Ptr<Method> context;

        /**
         * The ShowInfoTask that created this task.
         */
        Ptr<ShowInfoTask> source;
    };
};

}

}

#endif
