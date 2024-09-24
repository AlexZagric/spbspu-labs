#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <string>
#include <vector>

#include "hashtable.hpp"

namespace zagrivnyy
{
  struct Position
  {
    long unsigned int row, col;
  };

  std::ostream &operator<<(std::ostream &out, const Position &pos);

  class Dictionary
  {
  public:
    Dictionary();

    void add(std::string word, Position pos);
    void add(std::string word, std::vector< Position > pos);
    bool remove(std::string word);
    void parse_table(std::vector< std::vector< std::string > > table);
    std::vector< std::vector< std::string > > generate_table() const;
    std::vector< Position > get(std::string word) const;

    zagrivnyy::hash_table< std::vector< Position > > get_dict()
    {
      return dict_;
    }

  private:
    zagrivnyy::hash_table< std::vector< Position > > dict_;
  };
}
#endif
