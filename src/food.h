#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"
#include <mutex>
using std::vector;

enum class FoodType {
  Normal, //increase size and speed
  Points_Only, //increase points but not size nor speed
  Speed_Reducer, //decrease speed
  Double //increase size and speed by two
};

class FoodItem {
public:
    FoodItem(int y, int x, FoodType type);
    SDL_Point GetPlace();
    FoodType GetType();
    int GetR();
    int GetG();
    int GetB();
    bool valid{false};
private:
  SDL_Point _place;
  FoodType _type;
  int _r;
  int _g;
  int _b;
};

class Food {
 public:
   void AddItem(FoodItem item);
   void RemoveItem(FoodItem item);
   vector<FoodItem> GetItems() const;
   FoodItem GetOne() const;
   FoodItem GetByCoordinate(int y, int x);
   bool CheckFoodAtCoordinate(int y, int x);
 private:
   std::mutex _items_mutex;
  vector<FoodItem> _items;
};

#endif