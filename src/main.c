#include <stdio.h>
#include <stdbool.h>

static bool parse_args
(
  int    _argc,
  char **_argv
)
{
  return true;
}

int main
(
  int    _argc,
  char **_argv
)
{
  bool are_args_ok = parse_args(_argc, _argv);
  if (!are_args_ok)
  {
    printf("jcon: Could not parse args");

    return 1;
  }
  
  return 0;
}
