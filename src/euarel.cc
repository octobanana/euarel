#include "euarel.hh"

#include <cstdio>
#include <cctype>
#include <cstddef>

#include <string>

namespace OB::Euarel
{

std::string hex_encode(char const c);
char hex_decode(std::string const& s);

std::string hex_encode(char const c)
{
  char s[3];

  if (c & 0x80)
  {
    std::snprintf(&s[0], 3, "%02X",
      static_cast<unsigned int>(c & 0xff)
    );
  }
  else
  {
    std::snprintf(&s[0], 3, "%02X",
      static_cast<unsigned int>(c)
    );
  }

  return std::string(s);
}

char hex_decode(std::string const& s)
{
  unsigned int n;

  std::sscanf(s.data(), "%x", &n);

  return static_cast<char>(n);
}

std::string url_encode(std::string const& str, bool form)
{
  std::string res;
  res.reserve(str.size());

  for (auto const& e : str)
  {
    if (e == ' ' && form)
    {
      res += "+";
    }
    else if (std::isalnum(static_cast<unsigned char>(e)) ||
      e == '-' || e == '_' || e == '.' || e == '~')
    {
      res += e;
    }
    else
    {
      res += "%" + hex_encode(e);
    }
  }

  return res;
}

std::string url_decode(std::string const& str, bool form)
{
  std::string res;
  res.reserve(str.size());

  for (std::size_t i = 0; i < str.size(); ++i)
  {
    if (str[i] == '+' && form)
    {
      res += " ";
    }
    else if (str[i] == '%' && i + 2 < str.size() &&
      std::isxdigit(static_cast<unsigned char>(str[i + 1])) &&
      std::isxdigit(static_cast<unsigned char>(str[i + 2])))
    {
      res += hex_decode(str.substr(i + 1, 2));
      i += 2;
    }
    else
    {
      res += str[i];
    }
  }

  return res;
}

} // namespace OB::Euarel
