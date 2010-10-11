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

#ifndef _ORK_PROGRAM_H_
#define _ORK_PROGRAM_H_

#include "ork/render/Module.h"
#include "ork/render/Uniform.h"

using namespace std;

namespace ork
{

namespace render
{

class FrameBuffer;

/**
 * A GPU program. A GPU program can define vertex, tessellation, geometry and
 * fragment programs. It is made of one or more Module, themselves made of one
 * or more GLSL shaders.
 */
class ORK_API Program : public Object
{
public:
    /**
     * Creates a new program.
     *
     * @param modules the modules that will compose this program.
     */
    Program(const vector< Ptr<Module> > &modules);

    /**
     * Creates a new program.
     *
     * @param module the single module that will compose this program.
     */
    Program(Ptr<Module> module);

    /**
     * Deletes this program.
     */
    virtual ~Program();

    /**
     * Returns the id of this program.
     */
    virtual int getId() const;

    /**
     * Returns the number of Module objects in this program.
     */
    int getModuleCount() const;

    /**
     * Returns the Module of this program whose index is given.
     */
    Ptr<Module> getModule(int index) const;

    /**
     * Returns the uniform of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    Ptr<Uniform> getUniform(const string &name);

    /**
     * Returns the uniform1f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform1f> getUniform1f(const string &name);

    /**
     * Returns the uniform1d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform1d> getUniform1d(const string &name);

    /**
     * Returns the uniform1i of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform1i> getUniform1i(const string &name);

    /**
     * Returns the uniform1ui of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform1ui> getUniform1ui(const string &name);

    /**
     * Returns the uniform1b of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform1b> getUniform1b(const string &name);

    /**
     * Returns the uniform2f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform2f> getUniform2f(const string &name);

    /**
     * Returns the uniform2d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform2d> getUniform2d(const string &name);

    /**
     * Returns the uniform2i of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform2i> getUniform2i(const string &name);

    /**
     * Returns the uniform2ui of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform2ui> getUniform2ui(const string &name);

    /**
     * Returns the uniform2b of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform2b> getUniform2b(const string &name);

    /**
     * Returns the uniform3f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform3f> getUniform3f(const string &name);

    /**
     * Returns the uniform3d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform3d> getUniform3d(const string &name);

    /**
     * Returns the uniform3i of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform3i> getUniform3i(const string &name);

    /**
     * Returns the uniform3ui of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform3ui> getUniform3ui(const string &name);

    /**
     * Returns the uniform3b of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform3b> getUniform3b(const string &name);

    /**
     * Returns the uniform4f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform4f> getUniform4f(const string &name);

    /**
     * Returns the uniform4d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform4d> getUniform4d(const string &name);

    /**
     * Returns the uniform4i of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform4i> getUniform4i(const string &name);

    /**
     * Returns the uniform4ui of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform4ui> getUniform4ui(const string &name);

    /**
     * Returns the uniform4b of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<Uniform4b> getUniform4b(const string &name);

    /**
     * Returns the uniformMatrix2f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2f> getUniformMatrix2f(const string &name);

    /**
     * Returns the uniformMatrix2d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2d> getUniformMatrix2d(const string &name);

    /**
     * Returns the uniformMatrix3f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3f> getUniformMatrix3f(const string &name);

    /**
     * Returns the uniformMatrix3d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3d> getUniformMatrix3d(const string &name);

    /**
     * Returns the uniformMatrix4f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4f> getUniformMatrix4f(const string &name);

    /**
     * Returns the uniformMatrix4d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4d> getUniformMatrix4d(const string &name);

    /**
     * Returns the uniformMatrix2x3f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2x3f> getUniformMatrix2x3f(const string &name);

    /**
     * Returns the uniformMatrix2x3d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2x3d> getUniformMatrix2x3d(const string &name);

    /**
     * Returns the uniformMatrix2x4f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2x4f> getUniformMatrix2x4f(const string &name);

    /**
     * Returns the uniformMatrix2x4d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix2x4d> getUniformMatrix2x4d(const string &name);

    /**
     * Returns the uniformMatrix3x2f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3x2f> getUniformMatrix3x2f(const string &name);

    /**
     * Returns the uniformMatrix3x2d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3x2d> getUniformMatrix3x2d(const string &name);

    /**
     * Returns the uniformMatrix3x4f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3x4f> getUniformMatrix3x4f(const string &name);

    /**
     * Returns the uniformMatrix3x4d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix3x4d> getUniformMatrix3x4d(const string &name);

    /**
     * Returns the uniformMatrix4x2f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4x2f> getUniformMatrix4x2f(const string &name);

    /**
     * Returns the uniformMatrix4x2d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4x2d> getUniformMatrix4x2d(const string &name);

    /**
     * Returns the uniformMatrix4x3f of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4x3f> getUniformMatrix4x3f(const string &name);

    /**
     * Returns the uniformMatrix4x2d of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformMatrix4x3d> getUniformMatrix4x3d(const string &name);

    /**
     * Returns the uniform sampler of this program whose name is given.
     *
     * @param name a GLSL uniform name.
     * @return the uniform of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    inline Ptr<UniformSampler> getUniformSampler(const string &name);

    /**
     * Returns the uniform block of this program whose name is given.
     *
     * @param name a GLSL uniform block name.
     * @return the uniform block of this program whose name is given,
     *       or NULL if there is no such uniform.
     */
    Ptr<UniformBlock> getUniformBlock(const string &name);

protected:
    /**
     * The modules of this program.
     */
    vector< Ptr<Module> > modules;

    /**
     * Creates an unitialized program.
     */
    Program();

    /**
     * Initializes this program.
     *
     * @param modules the modules that will compose this program.
     */
    void init(const vector< Ptr<Module> > &modules);

    /**
     * Swaps this program with the given one.
     */
    virtual void swap(Ptr<Program> t);

private:
    /**
     * The id of this program.
     */
    int programId;

    /**
     * The uniforms of this program. This includes all uniforms,
     * whether outside or inside a uniform block, including uniform samplers.
     */
    map<string, Ptr<Uniform> > uniforms;

    /**
     * The uniforms of this program that were present in old versions,
     * but are no longer present in the current one.
     */
    map<string, Ptr<Uniform> > oldUniforms;

    /**
     * The uniform samplers of this program.
     */
    vector< Ptr<UniformSampler> > uniformSamplers;

    /**
     * The uniform blocks of this program.
     */
    map<string, Ptr<UniformBlock> > uniformBlocks;

    /**
     * The program currently in use.
     */
    static Program *CURRENT;

    /**
     * Checks that each active program sampler is bound to a texture.
     *
     * @return true if all samplers are bound.
     */
    bool checkSamplers();

    /**
     * Sets this program as the current program.
     */
    void set();

    /**
     * Adds or removes this program as a user of the textures bound to
     * the uniform samplers of this program.
     */
    void updateTextureUsers(bool add);

    /**
     * Adds to or removes from #uniforms the uniforms that are inside
     * unifom blocks.
     */
    void updateUniformBlocks(bool add);

    /**
     * Sets the owner program of the uniforms and uniform blocks of this
     * program to the given value.
     *
     * @param owner the new owner for the uniforms of this program.
     */
    void updateUniforms(Program *owner);

    friend class Uniform;

    friend class UniformSampler;

    friend class Texture;

    friend class MeshBuffers;

    friend class TransformFeedback;

    friend class FrameBuffer;
};

inline Ptr<Uniform1f> Program::getUniform1f(const string &name)
{
    return getUniform(name).cast<Uniform1f>();
}

inline Ptr<Uniform1d> Program::getUniform1d(const string &name)
{
    return getUniform(name).cast<Uniform1d>();
}

inline Ptr<Uniform1i> Program::getUniform1i(const string &name)
{
    return getUniform(name).cast<Uniform1i>();
}

inline Ptr<Uniform1ui> Program::getUniform1ui(const string &name)
{
    return getUniform(name).cast<Uniform1ui>();
}

inline Ptr<Uniform1b> Program::getUniform1b(const string &name)
{
    return getUniform(name).cast<Uniform1b>();
}

inline Ptr<Uniform2f> Program::getUniform2f(const string &name)
{
    return getUniform(name).cast<Uniform2f>();
}

inline Ptr<Uniform2d> Program::getUniform2d(const string &name)
{
    return getUniform(name).cast<Uniform2d>();
}

inline Ptr<Uniform2i> Program::getUniform2i(const string &name)
{
    return getUniform(name).cast<Uniform2i>();
}

inline Ptr<Uniform2ui> Program::getUniform2ui(const string &name)
{
    return getUniform(name).cast<Uniform2ui>();
}

inline Ptr<Uniform2b> Program::getUniform2b(const string &name)
{
    return getUniform(name).cast<Uniform2b>();
}

inline Ptr<Uniform3f> Program::getUniform3f(const string &name)
{
    return getUniform(name).cast<Uniform3f>();
}

inline Ptr<Uniform3d> Program::getUniform3d(const string &name)
{
    return getUniform(name).cast<Uniform3d>();
}

inline Ptr<Uniform3i> Program::getUniform3i(const string &name)
{
    return getUniform(name).cast<Uniform3i>();
}

inline Ptr<Uniform3ui> Program::getUniform3ui(const string &name)
{
    return getUniform(name).cast<Uniform3ui>();
}

inline Ptr<Uniform3b> Program::getUniform3b(const string &name)
{
    return getUniform(name).cast<Uniform3b>();
}

inline Ptr<Uniform4f> Program::getUniform4f(const string &name)
{
    return getUniform(name).cast<Uniform4f>();
}

inline Ptr<Uniform4d> Program::getUniform4d(const string &name)
{
    return getUniform(name).cast<Uniform4d>();
}

inline Ptr<Uniform4i> Program::getUniform4i(const string &name)
{
    return getUniform(name).cast<Uniform4i>();
}

inline Ptr<Uniform4ui> Program::getUniform4ui(const string &name)
{
    return getUniform(name).cast<Uniform4ui>();
}

inline Ptr<Uniform4b> Program::getUniform4b(const string &name)
{
    return getUniform(name).cast<Uniform4b>();
}

inline Ptr<UniformMatrix2f> Program::getUniformMatrix2f(const string &name)
{
    return getUniform(name).cast<UniformMatrix2f>();
}

inline Ptr<UniformMatrix2d> Program::getUniformMatrix2d(const string &name)
{
    return getUniform(name).cast<UniformMatrix2d>();
}

inline Ptr<UniformMatrix3f> Program::getUniformMatrix3f(const string &name)
{
    return getUniform(name).cast<UniformMatrix3f>();
}

inline Ptr<UniformMatrix3d> Program::getUniformMatrix3d(const string &name)
{
    return getUniform(name).cast<UniformMatrix3d>();
}

inline Ptr<UniformMatrix4f> Program::getUniformMatrix4f(const string &name)
{
    return getUniform(name).cast<UniformMatrix4f>();
}

inline Ptr<UniformMatrix4d> Program::getUniformMatrix4d(const string &name)
{
    return getUniform(name).cast<UniformMatrix4d>();
}

inline Ptr<UniformMatrix2x3f> Program::getUniformMatrix2x3f(const string &name)
{
    return getUniform(name).cast<UniformMatrix2x3f>();
}

inline Ptr<UniformMatrix2x3d> Program::getUniformMatrix2x3d(const string &name)
{
    return getUniform(name).cast<UniformMatrix2x3d>();
}

inline Ptr<UniformMatrix2x4f> Program::getUniformMatrix2x4f(const string &name)
{
    return getUniform(name).cast<UniformMatrix2x4f>();
}

inline Ptr<UniformMatrix2x4d> Program::getUniformMatrix2x4d(const string &name)
{
    return getUniform(name).cast<UniformMatrix2x4d>();
}

inline Ptr<UniformMatrix3x2f> Program::getUniformMatrix3x2f(const string &name)
{
    return getUniform(name).cast<UniformMatrix3x2f>();
}

inline Ptr<UniformMatrix3x2d> Program::getUniformMatrix3x2d(const string &name)
{
    return getUniform(name).cast<UniformMatrix3x2d>();
}

inline Ptr<UniformMatrix3x4f> Program::getUniformMatrix3x4f(const string &name)
{
    return getUniform(name).cast<UniformMatrix3x4f>();
}

inline Ptr<UniformMatrix3x4d> Program::getUniformMatrix3x4d(const string &name)
{
    return getUniform(name).cast<UniformMatrix3x4d>();
}

inline Ptr<UniformMatrix4x2f> Program::getUniformMatrix4x2f(const string &name)
{
    return getUniform(name).cast<UniformMatrix4x2f>();
}

inline Ptr<UniformMatrix4x2d> Program::getUniformMatrix4x2d(const string &name)
{
    return getUniform(name).cast<UniformMatrix4x2d>();
}

inline Ptr<UniformMatrix4x3f> Program::getUniformMatrix4x3f(const string &name)
{
    return getUniform(name).cast<UniformMatrix4x3f>();
}

inline Ptr<UniformMatrix4x3d> Program::getUniformMatrix4x3d(const string &name)
{
    return getUniform(name).cast<UniformMatrix4x3d>();
}

inline Ptr<UniformSampler> Program::getUniformSampler(const string &name)
{
    return getUniform(name).cast<UniformSampler>();
}

}

}

#endif
