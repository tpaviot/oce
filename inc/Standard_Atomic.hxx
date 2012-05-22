// Created on: 2007-09-04
// Created by: Andrey BETENEV
// Copyright (c) 2007-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.


//! @file 
//! Implementation of some atomic operations (elementary operations 
//! with data that cannot be interrupted by parallel threads in the
//! multithread process) on various platforms
//!
//! By the moment, only operations necessary for reference counter 
//! in Standard_Transient objects are implemented.
//! 
//! This is preffered to use fixed size types "int32_t" / "int64_t" for
//! correct function declarations however we leave "int" assuming it is 32bits for now.

#ifndef _Standard_Atomic_HeaderFile
#define _Standard_Atomic_HeaderFile

#include <Standard_Macro.hxx>

#if defined(_MSC_VER) || defined(__BORLANDC__)
#ifdef __BORLANDC__
extern "C" {
  __declspec(dllimport) long __stdcall InterlockedIncrement ( long volatile *lpAddend);
  __declspec(dllimport) long __stdcall InterlockedDecrement ( long volatile *lpAddend);
 }
 #define _InterlockedIncrement InterlockedIncrement
 #define _InterlockedDecrement InterlockedDecrement
#elif defined(_MSC_VER)
 extern "C" {
  long _InterlockedIncrement(long volatile* lpAddend);
  long _InterlockedDecrement(long volatile* lpAddend);
 }
#endif
#endif

#if defined(_MSC_VER)
  // force intrinsic instead of WinAPI calls
  #pragma intrinsic (_InterlockedIncrement)
  #pragma intrinsic (_InterlockedDecrement)
#endif

//! Increments atomically integer variable pointed by theValue
//! and returns resulting incremented value.
static int Standard_Atomic_Increment (volatile int* theValue)
{
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
  // mordern g++ compiler (gcc4.4+)
  // built-in functions available for appropriate CPUs (at least -march=i486 should be specified on x86 platform)
  return __sync_add_and_fetch (theValue, 1);
#elif (defined(_WIN32) || defined(__WIN32__))
  // WinAPI function or MSVC intrinsic
  return _InterlockedIncrement(reinterpret_cast<long volatile*>(theValue));
#elif defined(LIN)
  // use x86 / x86_64 inline assembly (compatibility with alien compilers / old GCC)
  int anIncResult;
  __asm__ __volatile__ (
  #if defined(_OCC64)
    "lock xaddl %%ebx, (%%rax) \n\t"
    "incl %%ebx                \n\t"
    : "=b" (anIncResult)
    : "a" (theValue), "b" (1)
    : "cc", "memory");
  #else
    "lock xaddl %%eax, (%%ecx) \n\t"
    "incl %%eax                \n\t"
    : "=a" (anIncResult)
    : "c" (theValue), "a" (1)
    : "memory");
  #endif
  return anIncResult;
#else
  //#error "Atomic operation doesn't implemented for current platform!"
  return ++(*theValue);
#endif
}

//! Decrements atomically integer variable pointed by theValue
//! and returns resulting decremented value.
static int Standard_Atomic_Decrement (volatile int* theValue)
{
#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
  // mordern g++ compiler (gcc4.4+)
  // built-in functions available for appropriate CPUs (at least -march=i486 should be specified on x86 platform)
  return __sync_sub_and_fetch (theValue, 1);
#elif (defined(_WIN32) || defined(__WIN32__))
  // WinAPI function or MSVC intrinsic
  return _InterlockedDecrement(reinterpret_cast<long volatile*>(theValue));
#elif defined(LIN)
  // use x86 / x86_64 inline assembly (compatibility with alien compilers / old GCC)
  int aDecResult;
  __asm__ __volatile__ (
  #if defined(_OCC64)
    "lock xaddl %%ebx, (%%rax) \n\t"
    "decl %%ebx                \n\t"
    : "=b" (aDecResult)
    : "a" (theValue), "b" (-1)
    : "cc", "memory");
  #else
    "lock xaddl %%eax, (%%ecx) \n\t"
    "decl %%eax                \n\t"
    : "=a" (aDecResult)
    : "c" (theValue), "a" (-1)
    : "memory");
  #endif
  return aDecResult;
#else
  //#error "Atomic operation doesn't implemented for current platform!"
  return --(*theValue);
#endif
}

#endif //_Standard_Atomic_HeaderFile
