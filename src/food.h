#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"
#include <mutex>
#include <chrono>
#include "snake.h"
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
    void calculate(int &score, Snake *snake);
    bool operator== (FoodItem &source);
    inline const char* ToString()
    {
        switch (_type)
        {
            case FoodType::Normal:   return "Normal";
            case FoodType::Points_Only:   return "Points_Only";
            case FoodType::Speed_Reducer: return "Speed_Reducer";
            case FoodType::Double: return "Double";
            default:      return "[Unknown FoodType]";
        }
    }
    int GetR();
    int GetG();
    int GetB();
    bool valid{false};
    std::chrono::system_clock::time_point getTimeAdded();
private:
  SDL_Point _place;
  FoodType _type;
  int _r;
  int _g;
  int _b;
  std::chrono::system_clock::time_point _timeAdded;
};

class Food {
 public:
   Food();
   ~Food();
   void AddItem(FoodItem item);
   void RemoveItem(FoodItem &source);
   vector<FoodItem> GetItems() const;
   FoodItem GetOne() const;
   FoodItem GetByCoordinate(int y, int x);
   bool CheckFoodAtCoordinate(int y, int x);
   void RemoveOutdated();
   std::mutex _items_mutex;
 private:
  vector<FoodItem> _items;
};

#endif
