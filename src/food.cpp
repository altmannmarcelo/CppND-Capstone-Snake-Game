#include "food.h"
#include <iostream>

FoodItem::FoodItem(int y, int x, FoodType type) : _type(type) {
  _place.y = y;
  _place.x = x;
  _timeAdded = std::chrono::system_clock::now();
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
bool FoodItem::operator== (FoodItem &source)
{
  return this->_type == source._type &&
    this->_place.x == source._place.x &&
    this->_place.y == source._place.y;
}
void FoodItem::calculate(int *score, Snake *snake)
{
  switch(_type)
  {
	  case FoodType::Normal:
		  score++;
		  // Grow snake and increase speed.
		  snake->GrowBody();
		  snake->speed += 0.02;
		  break;
	  case FoodType::Points_Only:
		  score++;
		  break;
	  case FoodType::Speed_Reducer:
		  if(snake->speed > 0.1)
			  snake->speed -= 0.01;
		  break;
	  case FoodType::Double:
		  score++;
		  score++;
		  // Grow snake and increase speed.
		  snake->GrowBody();
		  snake->GrowBody();
		  snake->speed += 0.02;
		  snake->speed += 0.02;
		  break;
  }
}
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
std::chrono::system_clock::time_point FoodItem::getTimeAdded()
{
  return _timeAdded;
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
      std::cout << "Going to return item: " << (*item).ToString() << " at X: " << (*item).GetPlace().x << " Y: " << (*item).GetPlace().y << std::endl ;
      return *item;
    }
  }
  FoodItem item(-1,-1,FoodType::Normal);
  return item;
}
void Food::RemoveItem(FoodItem &source)
{
  for (auto item = _items.begin(); item != _items.end(); item ++)
  {
    if((*item) == source)
    {
      _items.erase(item);
      return;
    }
  }
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
void Food::RemoveOutdated()
{
  for (auto item = _items.begin(); item != _items.end(); item ++)
  {
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - (*item).getTimeAdded());
    if((*item).GetType() != FoodType::Normal && diff.count() > 10)
    {
      std::cout << "Erase outadated is going to remove " << (*item).ToString() << " X: " << (*item).GetPlace().x << " Y: " << (*item).GetPlace().y << std::endl;
      _items.erase(item);
    }
  }
}
