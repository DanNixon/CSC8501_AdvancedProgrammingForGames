#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

const std::string file_name = "data.txt";

void read_scores(std::vector<int> &scores)
{
  std::ifstream data_file;
  int temp;

  data_file.open(file_name.c_str());

  if (data_file.fail())
    throw std::invalid_argument("no file exists " + file_name);

  while (data_file >> temp)
    scores.push_back(temp);

  data_file.close();
}

double find_average(const int sum, const int divisor)
{
  if (!divisor)
    throw std::runtime_error("divisor is zero");
  return (sum / (double)divisor);
}

void throwing_ftn()
{
  throw std::runtime_error("something went wrong\n");
}

void memory_leak()
{
  std::string *s = new std::string("hello");

  throwing_ftn();

  delete s;
}

void no_memory_leak()
{
  std::string *s = new std::string("hello");

  try
  {
    throwing_ftn();
  }
  catch (...)
  {
    delete s;
    throw;
  }
  delete s;
}

int main()
{
  std::vector<int> scores;
  int sum = 0;

  try
  {
    read_scores(scores);
    for (int i = 0; i < scores.size(); ++i)
    {
      sum += scores[i];
    }
    std::cout << "avg = " << find_average(sum, (int)scores.size()) << "\n";
  }
  catch (const std::invalid_argument &iae)
  {
    std::cout << "unable to read data: " << iae.what() << "\n";
    exit(1);
  }
  catch (const std::runtime_error &rte)
  {
    std::cout << "unable to compute average: " << rte.what() << "\n";
    exit(1);
  }

  for (int i = 0; i < scores.size(); ++i)
    std::cout << "score " << i << " = " << scores[i] << "\n";

  return 0;
}