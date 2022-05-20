//! @file roc_core/helpers.h
//! @brief Complie time helpers

#ifndef ROC_CORE_HELPERS_H_
#define ROC_CORE_HELPERS_H_

//! Get numver of elements in a static array
#define ROC_ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

//! Cast a member of a structre out to the containing structure.
#define ROC_CONTAINER_OF(ptr, type, member) (reinterpret_cast<type*)((char*)(ptr)-offsetof(type, member))

//! Stringize marco helper
#define ROC_STRINGIZE_(s) #s

//! String marco
#define ROC_STRINGIZE(S) ROC_STRINGIZE_(s)


#endif // ROC_CORE_HELPERS_H_