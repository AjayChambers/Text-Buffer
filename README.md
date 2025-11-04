# Text-Buffer

Text-Buffer is a library that contains a several different classes.
Each class is fully documented, inline, as well as in this file.
The core class is—_as you undoubtedly guessed_—the `TextBuffer`
buffer class; a class used for storing text thats being worked on.

`TextBuffer` has a couple of features built into its core that makes
it a nice _'quality of life'_ library to use. As you walk through
long text files (including any JSON, markup, JavaScript, plain text, plain text data lists, and/or any utf-8/ASCII text ect...) it tracks
the position in row/column format. This is an invaluable feature
thats required for any modern diagnostics, text parsing, text editing,
text editors, etc...

------------------------------------------------------------

## TABLE -of- CONTENTS

### SECTION #1 |  Text Buffer Project
### SECTION #2 |  TextBuffer Documentation
### SECTION #4 |  Error Code Table

------------------------------------------------------------




<br>


<br>


````````````````````````````````````````````````````````````
[more files...]
^^^^^^^^^^^^^^^
│
│
├─[include]
│    │
│    ├─[text]
│    │    │
│    │    ├─* buffer.hpp
│    │    ├─* coordinate.hpp
│    │    └─* position.hpp
│    │
│    └─[utils]
│        │
│        └─* err.hpp
│
└─[src]
     │
     ├─* text-buffer.cpp
     ├─* position.cpp
     └─* CMakeLists.txt
````````````````````````````````````````````````````````````

Below is the chain used by clang++ & d-linker

##### text_buffer (static lib)  &nbsp; ⟹ &nbsp; `[text-buffer.cpp]` &nbsp; ⟹ &nbsp; `[buffer.hpp]` &nbsp; ⟹ &nbsp; \*\*`[position.hpp]` &nbsp; ⟹ &nbsp; `[coordinate.hpp]`

###### ** position.hpp is also included by position.cpp, however, position.cpp

<br>
<br>

## Text-Buffer Library Intro & Install Options

<br>
<br>


## Documented Classes & Class Members

-----------------------------

1. **Text Coordinate Class: `Text::Coordinate Class`**
2. **Text Position Class: `Text::Position Class`**
3. **Text Buffer Class: `Text::Buffer Class`**

-----------------------------


### Coordinate Class

Coordinate classes numeric type is set using size_type. By default
size_type is set to size_t.


<br>
<br>


## Error Table

