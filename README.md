Arraylist and Hashtable in C
============================

(c) 2012 Marek Zaluski 

Objective
---------

Lists and mappings are two of the most common generic data types. This library implements both, independantly, in pure modern C. It aims to be simple, concise, and completely generic.

The Arraylist and Hashtable implementations are provided as templates, which means they can produce specific implementations for use with any given element type. See below.

The code follows the C99 standard. If you're compiling using `gcc`, use the `-std=c99` flag.

Use in your project
-------------------

To use Arraylist or Hashtable, you first need to instantiate the template with a specific element type. For instance, to instantiate the template for elements of type `int`, you can use the shortcut `maketemplate` script as follows:

```bash
	# maketempalte <template> <name> <type>
	./maketemplate arraylist int int
```

This creates a two new files: `int_arralist.c` and `int_arraylist.h`.

The `<name>` prefix is prepended to all function calls, i.e. you will then use `int_arraylist_create()`,`int_arraylist_add(...)`, etc.

The <name> and <type> arguments are separate to accomodate types that can't be prepended to symbol names. For example, to create an Arraylist of strings, you can use the following:

```bash
	./maketemplate arraylist str char*
```

The result will be `str_arraylist` which contains elements of type `char *`.

Arraylists
-----------

The `arraylist.c` file contains an arraylist implementation. It is implemented as a dynamic array which is automatically resized as needed.

Usage (with an `int` type):

```c
int_arraylist* mylist = int_arraylist_create();
int_arraylist_add(mylist, value);
int result = int_arraylist_pop(mylist);
```

Hashtables
-----------

The `hashtable.c` file contains a hashtable implementation. It is implemented with open addressing and linear probing. It is automatically resized as needed.

The keys of the hashtable are strings. That's what the hashing function uses. If you want to use different values for keys, you have the option of converting them to strings.

Usage (with an `int` type):

```c
int_hashtable* mytable = int_hashtable_create();
int_hashtable_set(mytable, "foo", value1);
int_hashtable_remove(mytable, "boo");
int result;
hashtable_get(mytable, "bar", &result);
```

License
-------

Release under the MIT license.
