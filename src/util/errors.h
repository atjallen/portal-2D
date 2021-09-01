#pragma once

#include <stdexcept>

namespace util {

class NotImplementedError : public std::logic_error {
   public:
    NotImplementedError() : std::logic_error("Function not yet implemented"){};
};

}  // namespace util
