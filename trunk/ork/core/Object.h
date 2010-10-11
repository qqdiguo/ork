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

#ifndef _ORK_OBJECT_H_
#define _ORK_OBJECT_H_

#include <cstdio>
#include <cassert>

#ifndef NDEBUG
#include <map>
#include <set>
#endif

#ifndef NULL
#define NULL 0
#endif

using namespace std;

// ---------------------------------------------------------------------------
// Static and dynamic assertions
// ---------------------------------------------------------------------------

#define CONCATENATE(arg1, arg2) arg1 ## arg2
#define CONCAT(arg1, arg2) CONCATENATE(arg1, arg2)
#define static_assert(cond) typedef int CONCAT(ASSERTION_FAILED_AT_LINE_, __LINE__)[(cond) ? 1 : -1]

#ifndef NDEBUG
#undef assert
#define assert(e) if (!(e)) { ::assertAndSegfault(#e, __FILE__, __LINE__); }
ORK_API void assertAndSegfault(const char* a, const char* f, int l);
#endif

// ---------------------------------------------------------------------------
// Portable file functions
// ---------------------------------------------------------------------------

ORK_API void fopen(FILE **f, const char* fileName, const char *mode);

ORK_API void fseek64(FILE *f, long long offset, int origin);

// ---------------------------------------------------------------------------
// Object and smart pointer classes
// ---------------------------------------------------------------------------

#include "Atomic.h"

/**
 * Provides the OpenGL Rendering Kernel (Ork).
 */
namespace ork
{

/**
 * Provides basic smart pointer classes, and logger and timer utilities.
 */
namespace core
{

/**
 * An object with a reference counter. The reference count is managed by
 * the Ptr and StaticPtr classes to count the number of references to this
 * object. When this counter becomes 0 the object is automatically
 * destroyed. Instances of this class or of derived classes must NOT be
 * explicitely destroyed with the delete operator.
 */
class ORK_API Object
{
public:
    /**
     * Creates a new object.
     *
     * @param type the name of the class of this object. For debug only.
     */
    Object(const char *type);

    /**
     * Destroys this object.
     */
    virtual ~Object();

    /**
     * Returns the name of the class of this object. For debug only.
     */
    const char* getClass() const;

    /**
     * Increments the reference counter of this object.
     */
    inline void acquire()
    {
        atomic_increment(&references);
    }

    /**
     * Decrements the reference counter of this object.
     */
    inline void release()
    {
        if (atomic_decrement(&references) == 1) {
            doRelease();
        }
    }

    /**
     * Sets all static references to NULL.
     */
    static void exit();

#ifdef KEEP_OBJECTS_REFERENCES
    /**
     * Returns a set containing all instances of a class, or NULL is non was created.
     */
    static set<Object*>* findAllInstances(const char* className);
#endif

    virtual const char* toString();

protected:
    /**
     * The method called when the reference count of this object becomes 0.
     * The default implementation of this method deletes the object.
     */
    virtual void doRelease()
    {
        delete this;
    }

public:
    /**
     * A static reference to an object.
     */
    class StaticRef
    {
    protected:
        /**
         * Link to the next static reference.
         */
        StaticRef *next;

        /**
         * Creates a new static reference and adds it to the list of all
         * static references.
         */
        StaticRef()
        {
            next = Object::statics;
            Object::statics = this;
        }

        /**
         * Destroys this static reference.
         */
        virtual ~StaticRef()
        {
        }

        /**
         * Sets this static reference to NULL.
         */
        virtual void erase() = 0;

        friend class Object;
    };

private:

#ifndef NDEBUG
    /**
     * The class of this object.
     */
    char *type;
#endif

    /**
     * The number of references to this object.
     */
    int references;

#ifndef NDEBUG
    /**
     * The total number of objects currently allocated in memory.
     */
    static unsigned int count;

    /**
     * The number of objects currently allocated in memory, for each class.
     */
    static map<char*, int> *counts;

#endif

#ifdef KEEP_OBJECTS_REFERENCES
    /**
     * Reference to all objects created (auto-list)
     */
    static map<char*, set<Object*>* >* instances;
#endif

    /**
     * The list of all static references.
     */
    static StaticRef *statics;

    friend class StaticRef;
};

/**
 * A pointer to an Object.
 */
template <class T> class Ptr
{
public:
    /**
     * Creates a pointer pointing to NULL.
     */
    inline Ptr() : target(0)
    {
    }

    /**
     * Creates a pointer to the given object.
     */
    inline Ptr(T *target) : target(target)
    {
        if (target != 0) {
            target->acquire();
        }
    }

    /**
     * Creates a pointer as a copy of the given pointer.
     */
    inline Ptr(const Ptr<T> &p) : target(p.target)
    {
        if (target != 0) {
            target->acquire();
        }
    }

    /**
     * Creates a pointer as a copy of the given pointer.
     */
    template<class U>
    inline Ptr(const Ptr<U> p) : target(p == NULL ? NULL : &(*p))
    {
        if (target != 0) {
            target->acquire();
        }
    }

    /**
     * Destroys this pointer.
     */
    inline ~Ptr()
    {
        if (target != 0) {
            T* oldTarget = target;
            target = 0;
            oldTarget->release();
        }
    }

    /**
     * Assigns the given pointer to this pointer.
     */
    inline void operator=(const Ptr<T> &v)
    {
        // acquire must be done before release
        // to correctly handle self assignment cases
        if (v.target != 0) {
            v.target->acquire();
        }
        T* oldTarget = target;
        target = v.target;
        if (oldTarget != 0) {
            oldTarget->release();
        }
    }

    /**
     * Returns the target object of this pointer.
     */
    inline T *operator->() const
    {
        assert(target != NULL);
        return target;
    }

    /**
     * Returns the target object of this pointer.
     */
    inline T &operator*() const
    {
        assert(target != NULL);
        return *target;
    }

    /**
     * Returns true if this pointer and the given pointer point to the same
     * object.
     */
    inline bool operator==(const Ptr<T> &v) const
    {
        return target == v.target;
    }

    /**
     * Returns true if this pointer and the given pointer point to different
     * objects.
     */
    inline bool operator!=(const Ptr<T> &v) const
    {
        return target != v.target;
    }

    /**
     * Compares the addresses of the objects pointed by this pointer and by
     * the given pointer. Returns true if the address of the object pointed by
     * this pointer is less than the address of the object pointed by the
     * given pointer.
     */
    inline bool operator<(const Ptr<T> &v) const
    {
        return target < v.target;
    }

    /**
     * Returns true if this pointer points to the given object.
     */
    inline bool operator==(const T *target) const
    {
        return this->target == target;
    }

    /**
     * Returns true if this pointer does not point to the given object.
     */
    inline bool operator!=(const T *target) const
    {
        return this->target != target;
    }

    /**
     * Casts this pointer to a pointer of the given type.
     * Using dynamic_cast.
     */
    template <class U>
    inline Ptr<U> cast() const
    {
        return Ptr<U>(dynamic_cast<U*>(target));
    }

    /**
     * Casts this pointer to a pointer of the given type.
     * Using static_cast.
     */
    template <class U>
    inline Ptr<U> staticCast() const
    {
        return Ptr<U>(static_cast<U*>(target));
    }

protected:
    /**
     * The object pointed by this pointer.
     */
    T *target;
};

/**
 * A static pointer to an Object. StaticPtr must be used instead of Ptr for
 * static variables.
 */
template <class T> class StaticPtr : public Ptr<T>, Object::StaticRef
{
public:
    /**
     * Creates a pointer pointing to NULL.
     */
    inline StaticPtr() : Ptr<T>(), StaticRef()
    {
    }

    /**
     * Creates a pointer to the given object.
     */
    inline explicit StaticPtr(T *target) : Ptr<T>(target), StaticRef()
    {
    }

    /**
     * Destroys this pointer.
     */
    inline ~StaticPtr()
    {
    }

    /**
     * Returns true if this pointer and the given pointer point to the same
     * object.
     */
    inline void operator=(const Ptr<T> &v)
    {
        Ptr<T>::operator=(v);
    }

protected:
    virtual void erase()
    {
        if (Ptr<T>::target != 0) {
            T *t = Ptr<T>::target;
            Ptr<T>::target = 0;
            t->release();
        }
    }
};

}

}

#endif
