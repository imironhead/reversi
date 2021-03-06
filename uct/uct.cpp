// Copyright 2016 iRonhead
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include "uct.hpp"

using std::cin;
using std::shared_ptr;
using std::srand;
using std::time;

//------------------------------------------------------------------------------
UpperConfidenceTree::UpperConfidenceTree(int32_t count_round)
    : count_round_(count_round) {
  // Simulatation needs random numbers.
  srand(time(nullptr));
}

//------------------------------------------------------------------------------
State* UpperConfidenceTree::Search(State* root) const {
  assert(root != nullptr);

  // I don't want to manipulate root.
  shared_ptr<State> temp(root->Clone());

  State* selected = nullptr;

  for (int32_t round = 0; round < this->count_round_; ++round) {
    selected = temp->Select();

    if (selected->IsNormal()) {
      selected = selected->Expand();
    }

    auto winner = selected->Simulate();

    selected->Backpropagate(winner);
  }

  return temp->BestMove();
}

//------------------------------------------------------------------------------
State* UpperConfidenceTree::SearchDemo(State* root) const {
  assert(root != nullptr);

  // I don't want to manipulate root.
  shared_ptr<State> temp(root->Clone());

  State* selected = nullptr;

  for (int32_t round = 0; round < this->count_round_; ++round) {
    selected = temp->Select();

    if (selected->IsNormal()) {
      selected = selected->Expand();
    }

    auto winner = selected->Simulate();

    selected->Backpropagate(winner);

    temp->InspectValue();

    cin.get();
  }

  return temp->BestMove();
}
