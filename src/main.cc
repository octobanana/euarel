#include "parg.hh"
using Parg = OB::Parg;

#include "euarel.hh"
namespace Euarel = OB::Euarel;

#include <unistd.h>

#include <string>
#include <iostream>

int program_options(Parg& pg);
void print(std::string const& str);
void run(Parg& pg);

int program_options(Parg& pg)
{
  pg.name("euarel").version("0.1.1 (06.12.2018)");
  pg.description("A CLI tool for URL percent-encoding and percent-decoding text.");
  pg.usage("[flags] [options] [--] [arguments]");
  pg.usage("[-e|--encode] [-f|--form] 'text'");
  pg.usage("[-d|--decode] [-f|--form] 'text'");
  pg.usage("[-v|--version]");
  pg.usage("[-h|--help]");
  pg.info("Examples", {
    "euarel --encode 'text to encode'",
    "euarel --decode 'text to decode'",
    "euarel -ef 'encode form data'",
    "printf 'redirect text to encode' | euarel -e",
    "euarel --help",
    "euarel --version",
  });
  pg.info("Exit Codes", {"0 -> normal", "1 -> error"});
  pg.info("Repository", {
    "https://github.com/octobanana/euarel.git",
  });
  pg.info("Homepage", {
    "https://octobanana.com/software/euarel",
  });
  pg.author("Brett Robinson (octobanana) <octobanana.dev@gmail.com>");

  // flags
  pg.set("help,h", "print the help output");
  pg.set("version,v", "print the program version");
  pg.set("encode,e", "percent encode text");
  pg.set("decode,d", "percent decode text");
  pg.set("form,f", "use 'application/x-www-form-urlencoded' media type");

  pg.set_pos();
  pg.set_stdin();

  int status {pg.parse()};

  if (status > 0 && pg.get_stdin().empty())
  {
    std::cerr << pg.help() << "\n";
    std::cerr << "Error: " << "expected arguments" << "\n";

    return -1;
  }

  if (status < 0)
  {
    std::cerr << pg.help() << "\n";
    std::cerr << "Error: " << pg.error() << "\n";

    return -1;
  }

  if (pg.get<bool>("help"))
  {
    std::cerr << pg.help();

    return 1;
  }

  if (pg.get<bool>("version"))
  {
    std::cerr << pg.name() << " v" << pg.version() << "\n";

    return 1;
  }

  if (! pg.get<bool>("encode") && ! pg.get<bool>("decode"))
  {
    std::cerr << pg.help() << "\n";
    std::cerr << "Error: " << "expected either '-e' or '-d' flag" << "\n";

    return -1;
  }

  if (pg.get<bool>("encode") && pg.get<bool>("decode"))
  {
    std::cerr << pg.help() << "\n";
    std::cerr << "Error: " << "flags '-e' and '-d' are in conflict" << "\n";

    return -1;
  }

  if ((pg.get<bool>("encode") || pg.get<bool>("decode")) &&
    (pg.get_stdin().empty() && pg.get_pos().empty()))
  {
    std::cerr << pg.help() << "\n";
    std::cerr << "Error: " << "expected input text" << "\n";

    return -1;
  }

  return 0;
}

void print(std::string const& str)
{
  if (! isatty(STDOUT_FILENO))
  {
    std::cout << str;
  }
  else
  {
    std::cout << str << "\n";
  }
}

void run(Parg& pg)
{
  bool form {pg.get<bool>("form")};
  std::string data {pg.get_stdin() + pg.get_pos()};

  std::string str;

  if (pg.get<bool>("encode"))
  {
    str = Euarel::url_encode(data, form);
  }
  else if (pg.get<bool>("decode"))
  {
    str = Euarel::url_decode(data, form);
  }

  print(str);
}

int main(int argc, char *argv[])
{
  Parg pg {argc, argv};
  int pstatus {program_options(pg)};
  if (pstatus > 0) return 0;
  if (pstatus < 0) return 1;

  run(pg);

  return 0;
}
