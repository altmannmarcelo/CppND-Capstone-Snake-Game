#include "food.h"

FoodItem::FoodItem(int y, int x, FoodType type) : _type(type) {
  _place.y = y;
  _place.x = x;
  if(y != -1 && x != -1)
    valid = true;

  switch (_type) {
    case FoodType::Normal:
      _r = 0xFF;
      _g = 0xCC;
      _b = 0x00;
      break;
    case FoodType::Points_Only:
      _r = 0x00;
      _g = 0xFF;
      _b = 0x00;
      break;
    case FoodType::Speed_Reducer:
      _r = 0x00;
      _g = 0x00;
      _b = 0xFF;
      break;
    case FoodType::Double:
      _r = 0xD2;
      _g = 0x69;
      _b = 0x1E;
      break;
  }
};

SDL_Point FoodItem::GetPlace()
{
  return _place;
}
FoodType FoodItem::GetType()
{
  return _type;
}
int FoodItem::GetR()
{
  return _r;
}
int FoodItem::GetG()
{
  return _g;
}
int FoodItem::GetB()
{
  return _b;
}
vector<FoodItem> Food::GetItems() const
{
  return _items;
}
FoodItem Food::GetOne() const
{
  return _items.back();
}

void Food::AddItem(FoodItem item)
{
  _items.push_back(item);
}
FoodItem Food::GetByCoordinate(int y, int x)
{
  for (auto item = _items.begin(); item != _items.end(); item ++)
  {
    if((*item).GetPlace().y == y && (*item).GetPlace().x == x)
    {
      _items.erase(item);
      return *item;
    }
  }
  FoodItem item(-1,-1,FoodType::Normal);
  return item;
}
bool Food::CheckFoodAtCoordinate(int y, int x)
{
  for (FoodItem item : _items)
  {
    if(item.GetPlace().y == y && item.GetPlace().x == x)
      return true;
  }
  return false;
}