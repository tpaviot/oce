// Author: Roman Lygin, 2011.
// This file is put into Public Domain and thus can freely be used for any purpose.
// The author disclaims any rights and liabilities.

#ifndef _Standard_StdAllocator_HeaderFile
#define _Standard_StdAllocator_HeaderFile

#include <Standard.hxx>

//! Implements allocator requirements as defined in ISO C++ Standard 2003, section 20.1.5.
/*! The allocator uses Open CASCADE Technology memory management API (
    Standard::Allocate() and Standard::Free()). It can be used with standard
    containers (std::vector, std::map, etc) to use centralized Open CASCADE
    memory management and hence decrease memory footprint and/or increase
    performance.

    Example of use:
    \code
    std::vector<TopoDS_Shape, Standard_StdAllocator<TopoDS_Shape> > aVec;
    TopoDS_Solid aSolid = BRepPrimAPI_MakeBox (10., 20., 30.);
    aVec.push_back (aSolid);
    \endcode
*/
template<typename T>
class Standard_StdAllocator {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    template<typename U> struct rebind {
        typedef Standard_StdAllocator<U> other;
    };

    //! Constructor.
    /*! Creates an empty object.*/
    Standard_StdAllocator() throw() {}

    //! Constructor.
    /*! Creates an empty object.*/
    Standard_StdAllocator( const Standard_StdAllocator& ) throw() {}

    //! Destructor.
    /*! Empty implementation.*/
    ~Standard_StdAllocator() throw() {}

    //! Constructor.
    /*! Creates an empty object.*/
    template<typename U> Standard_StdAllocator( const Standard_StdAllocator<U>& ) throw() {}

    //! Returns an object address.
    /*! Returns &x.*/
    pointer address( reference x ) const { return &x; }

    //! Returns an object address.
    /*! Returns &x.*/
    const_pointer address( const_reference x ) const { return &x; }
    
    //! Allocates memory for \a n objects.
    /*! Uses Standard::Allocate().*/
    pointer allocate( size_type n, const void* /*hint*/ = 0 )
    { return pointer( Standard::Allocate( n * sizeof( value_type ))); }

    //! Frees previously allocated memory.
    /*! Uses Standard::Free().*/
    void deallocate( pointer p, size_type )
    {
        Standard_Address a = p;
        Standard::Free (a); //Standard::Free() requires Standard_Address&
    }

    //! Returns the largest value for which method allocate might succeed.
    size_type max_size() const throw()
    {
        size_type aMax = static_cast<size_type>( -1 ) / sizeof( value_type );
        return (aMax > 0 ? aMax : 1);
    }

    //! Constructs an object.
    /*! Uses the placement new operator and copy constructor to construct an object.*/
    void construct( pointer p, const_reference val )
    { new( static_cast<void*>( p )) value_type( val ); }

    //! Destroys the object.
    /*! Uses object destructor.*/
    /*  Destructor name must match the class name for __BORLANDC__.*/
#ifdef __BORLANDC__
    void destroy( pointer p ) { p->~T(); }
#else
    void destroy( pointer p ) { p->~value_type(); }
#endif
};

//! Implements specialization Standard_StdAllocator<void>.
/*! Specialization is similar to std::allocator<void>, as defined in ISO C++
    Standard 2003, section 20.4.1.

    This specialization is interchangeable with other ones.

    Example of use:
    \code
    std::vector<TopoDS_Shape, Standard_StdAllocator<void> > aVec;
    TopoDS_Solid aSolid = BRepPrimAPI_MakeBox (10., 20., 30.);
    aVec.push_back (aSolid);
    \endcode
*/
template<> 
class Standard_StdAllocator<void> {
public:
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;
    template<typename U> struct rebind {
        typedef Standard_StdAllocator<U> other;
    };
};

template<typename T, typename U>
inline bool operator==( const Standard_StdAllocator<T>&, const Standard_StdAllocator<U>& )
{ return true; }

template<typename T, typename U>
inline bool operator!=( const Standard_StdAllocator<T>&, const Standard_StdAllocator<U>& )
{ return false; }


#endif
