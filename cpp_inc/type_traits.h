//
// Created by hujianzhe on 20-9-3
//

#ifndef	UTIL_CPP_TYPE_TRAITS_H
#define	UTIL_CPP_TYPE_TRAITS_H

#include "cpp_compiler_define.h"

namespace util {
// is_same
template <typename T, typename U>
struct is_same {
	enum { value = false };
};
template <typename T>
struct is_same<T, T> {
	enum { value = true };
};
// is_array
template <typename T>
struct is_array {
	enum { value = false };
};
template <typename T>
struct is_array<T[]> {
	enum { value = true };
};
template <typename T, size_t N>
struct is_array<T[N]> {
	enum { value = true };
};
// is_void
template <typename T>
struct is_void {
	enum { value = false };
};
template <>
struct is_void<void> {
	enum { value = true };
};
// is_pointer
template <typename T>
struct is_pointer {
	enum { value = false };
};
template <typename C, typename D>
struct is_pointer<D C::*> {
	enum { value = true };
};
template <typename T>
struct is_pointer<T(*)()> {
	enum { value = true };
};
template <typename T>
struct is_pointer<T*> {
	enum { value = true };
};
template <>
struct is_pointer<void> {
	enum { value = false };
};
// is class
template <typename T>
struct is_class {
private:
	template <typename C> static char test(int C::*);
	template <typename C> static int test(...);

public:
	enum { value = (sizeof(test<T>(0)) == sizeof(char)) };
};
// is_base_of
template <typename T, bool isClass = is_class<T>::value> struct is_inherit_impl;
template <typename T>
struct is_inherit_impl <T, true> {
private:
	template <typename C> static char test(const T*);
	template <typename C> static int test(...);

public:
	template <typename C>
	struct Check {
	private:
		static C* getType();
	public:
		enum { value = (sizeof(test<T>(getType())) == sizeof(char)) };
	};
};
template <typename T>
struct is_inherit_impl <T, false> {
public:
	template <typename C>
	struct Check {
	public:
		enum { value = false };
	};
};
template <class Parent, class Sub>
struct is_base_of {
	enum { value =  is_inherit_impl<Parent>::template Check<Sub>::value };
};
}

#endif
