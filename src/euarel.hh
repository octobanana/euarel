#ifndef OB_EUAREL_HH
#define OB_EUAREL_HH

#include <string>

namespace OB::Euarel
{

  std::string url_encode(std::string const& str, bool form);
  std::string url_decode(std::string const& str, bool form);

} // namespace OB::Euarel

#endif // OB_EUAREL_HH
