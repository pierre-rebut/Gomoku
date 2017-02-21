#include <iostream>
#include "Core.hpp"

int	main()
{
  Core	*core;

  try
    {
      core = new Core;

      core->loopGame();
      delete core;
    }
  catch (const std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  return (0);
}
