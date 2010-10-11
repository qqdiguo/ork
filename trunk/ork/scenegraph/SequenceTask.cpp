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

#include "ork/scenegraph/SequenceTask.h"

#include "ork/resource/ResourceTemplate.h"
#include "ork/taskgraph/TaskGraph.h"
#include "ork/scenegraph/SceneManager.h"

namespace ork
{

namespace scenegraph
{

SequenceTask::SequenceTask() : AbstractTask("SequenceTask")
{
}

SequenceTask::SequenceTask(const vector< Ptr<TaskFactory> > &subtasks) :
    AbstractTask("SequenceTask")
{
    init(subtasks);
}

void SequenceTask::init(const vector< Ptr<TaskFactory> > &subtasks)
{
    this->subtasks = subtasks;
}

SequenceTask::~SequenceTask()
{
}

Ptr<Task> SequenceTask::getTask(Ptr<Object> context)
{
    if (subtasks.size() == 1) {
        return subtasks[0]->getTask(context);
    } else {
        Ptr<TaskGraph> result = new TaskGraph();
        Ptr<Task> prev = NULL;
        for (unsigned int i = 0; i < subtasks.size(); ++i) {
            try {
                Ptr<Task> next = subtasks[i]->getTask(context);
                if (next.cast<TaskGraph>() == NULL || !next.cast<TaskGraph>()->isEmpty()) {
                    result->addTask(next);
                    if (prev != NULL) {
                        result->addDependency(next, prev);
                    }
                    prev = next;
                }
            } catch (...) {
            }
        }
        return result;
    }
}

void SequenceTask::swap(Ptr<SequenceTask> t)
{
    std::swap(subtasks, t->subtasks);
}

/// @cond RESOURCES

class SequenceTaskResource : public ResourceTemplate<40, SequenceTask>
{
public:
    SequenceTaskResource(Ptr<ResourceManager> manager, const string &name, Ptr<ResourceDescriptor> desc, const TiXmlElement *e = NULL) :
        ResourceTemplate<40, SequenceTask>(manager, name, desc)
    {
        e = e == NULL ? desc->descriptor : e;
        checkParameters(desc, e, "");
        vector< Ptr<TaskFactory> > subtasks;
        const TiXmlNode *n = e->FirstChild();
        while (n != NULL) {
            const TiXmlElement *f = n->ToElement();
            if (f != NULL) {
                Ptr<TaskFactory> tf;
                tf = ResourceFactory::getInstance()->create(manager, "", desc, f).cast<TaskFactory>();
                subtasks.push_back(tf);
            }
            n = n->NextSibling();
        }
        init(subtasks);
    }
};

extern const char sequence[] = "sequence";

static ResourceFactory::Type<sequence, SequenceTaskResource> SequenceTaskType;

/// @endcond

}

}
