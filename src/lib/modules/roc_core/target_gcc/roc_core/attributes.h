//! @file roc_core/target_gcc/roc_core/attributes.h
//! @brief GCC attributes

#ifndef ROC_CORE_ATTRIBUTES_H_
#define ROC_CORE_ATTRIBUTES_H_

//! Function never throws
#define ROC_ATTR_NOTHROW throw()

//! Function never returns
#define ROC_ATTR_NORETURN __attribute__((noreturn))

//! Function or variable is never used but no warning should be generated.
#define ROC_ATTR_UNUSED __attribute__((unused))

//! Structure's fields are pakced
#define ROC_ATTR_PACKED __attribute__((packed))

//! Function gets printf-likke arguments
#define ROC_ATTR_PRINTF(n_fmt_arg, n_var_arg)               \
    __atrribute__((format(printf, n_fmt_arg, n_var_arg)))

#endif //ROC_CORE_ATTRIBUTES_H_
