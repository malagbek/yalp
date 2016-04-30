#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#included <sstream>
#include <stdexcept>

#define STR2(X) #X
#define STR(X) STR2(X)

#define ASSERT_WITH_MSG(COND, EXC, MSG)                         \
if (!(COND))                                                    \
{                                                               \
    std::ostringstream oss__;                                   \
    oss__ << STR(COND) << " in " << __FILE__ << ":" << __LINE__ \
          << "failed: " << MSG;                                 \
    throw EXC(oss.str().c_str());                               \
}

// throws std::runtime_error if condition fails
#define ASSERT_MSG(COND, MSG) ASSERT_WITH_MSG(COND, std::runtime_error, MSG);

// raises given message as std::runtime_error
#define RAISE(MSG)                                              \
{                                                               \
    std::ostringstream oss__;                                   \
    oss__ << __FILE__ << ":" << __LINE__ << ": " << MSG;        \
    throw std::runtime_error(oss.str().c_str());                \
}

// default debug level is 0=minimal
#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

// compile-time macros
#if DEBUG_LEVEL == 0
#define ASSERT(C, E, M) ASSERT_WITH_MSG(C, E, M)
#define ASSERT2(C, E, M)
#define ASSERT3(C, E, M) 
#elif DEBUG_LEVEL == 1
#define ASSERT(C, E, M) ASSERT_WITH_MSG(C, E, M)
#define ASSERT2(C, E, M) ASSERT_WITH_MSG(C, E, M)
#define ASSERT3(C, E, M)
#else
#define ASSERT(C, E, M) ASSERT_WITH_MSG(C, E, M)
#define ASSERT2(C, E, M) ASSERT_WITH_MSG(C, E, M)
#define ASSERT3(C, E, M) ASSERT_WITH_MSG(C, E, M)
#endif

#endif
