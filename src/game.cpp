#include "game.h"
#include <iostream>
#include <thread>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood(FoodType::Normal);
}

void Game::PlaceRandomFood()
{
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> distr(10, 20);
  int cycle_duration = distr(eng);
  auto last_update = std::chrono::system_clock::now();
  while(snake.alive && running)
  {
    long time_since_last_update = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - last_update).count();
    if (time_since_last_update >= cycle_duration)
    {
      std::cout << "PlaceRandomFood thread" << std::endl;
      food.get()->_items_mutex.lock();
      std::cout << "Food in the game " << food.get()->GetItems().size() << std::endl;
      FoodType new_type = static_cast<FoodType>(rand() % 4);
      PlaceFood(new_type);
      food.get()->RemoveOutdated();
      food.get()->_items_mutex.unlock();
      last_update = std::chrono::system_clock::now();
      cycle_duration = distr(eng);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  std::thread randomFood([this] { PlaceRandomFood(); });
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(*score, snake.speed, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  randomFood.join();
}

void Game::PlaceFood(FoodType type) {
  std::cout << "PlaceFodd called" << std::endl;
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && (food.get() == nullptr || !food.get()->CheckFoodAtCoordinate(y, x))) {
      FoodItem item(y,x,type);
      food.get()->AddItem(item);
      std::cout << "Food added at X: " << x << " - Y: " << y << " Type: " << item.ToString() << std::endl;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  food.get()->_items_mutex.lock();
  if (food.get()->CheckFoodAtCoordinate(new_y, new_x)) {
    FoodItem item = food.get()->GetByCoordinate(new_y, new_x);
    if(!item.valid)
      return;
      
    std::cout << "ate food of type " << item.ToString() << " X: " << item.GetPlace().x << "Y: " << item.GetPlace().y << std::endl;
    std::cout << "Snake at x: " << new_x << " y:" << new_y << std::endl;
    item.calculate(*score, &snake);
    if (item.GetType() == FoodType::Normal)
      PlaceFood(FoodType::Normal);

    food.get()->RemoveItem(item);
  }
  food.get()->_items_mutex.unlock();
}

int Game::GetScore() const { return *score; }
int Game::GetSize() const { return snake.size; }
