# ACore - Core Library Utilites

## Contents
This module contains a bunch of utility functions and classes, only the most important are detailed below:

### Data/DataManager
DataManager provides a memory pool designed to be used by objects of large size (100kB+) that are created and destroyed over and over again (using exactly the same number of bytes).  For example in an image processing pipeline lots of images of exactly the same size will be allocated and deallocated, it would be expensive to use 'new' and 'delete' for each of these calls so the memory pool is used instead.

Note: DataManager is only meant for large objects, as each allocation is alligned to PAGE_SIZE

Note: This is the underlying memory manager that Image::Image uses

### Thread/QueueReaderAgent
This is a time synced reader Agent that responds to a control queue.


## Dependencies

ACore splits its dependencies depending on the compiler being used:

On msvc:  
- Win32API  
- MAAL - Microsoft's Asynchronous Agents Library  

On gcc:
