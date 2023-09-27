#pragma once
#include <chrono>
#include "Engine/Rendering/Graphics.h"
#include "Game/Game.h"
#include <chrono>

//took from jacco template
struct Timer
{
	using clock = std::chrono::system_clock;
	using ms = std::chrono::duration<float, std::milli>;
	typedef long long value_type;
	static double inv_freq;
	std::chrono::system_clock::time_point start;
	Timer() : start(get()) { }
	float elapsed() const
	{
		std::chrono::duration<float> elapsed_time = get() - start;
		return (elapsed_time.count());
	}
	static std::chrono::system_clock::time_point get()
	{
		return clock::now();
	}
	static double to_time(const value_type vt) { return double(vt); }
	void reset() { start = get(); }

};
class Application
{
public:
	void Run();

	static Application* Get();
	const Graphics& GetWin() const {return window;}

	void ResizeWindow(uint32_t w, uint32_t h)
	{
		window.ChangeWindowSize(w, h);
	}
	bool WindowOpen = false;
	
	void KeyPressEventCallBack(int key);
	void ButtonPressEventCallBack(int button);

	unsigned int getTime() 
	{
		auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(timer.get().time_since_epoch());
		unsigned int millisec = static_cast<unsigned int>(time.count());
		return  millisec;
	}
private:
	Application()
		: window("window", 1000, 800)
	{};

	static Application* app;

	void OpenGLSetUp();
	void CalculateDeltaTime();
	Timer timer;

	Graphics window;
	Game game;

	float deltaTime = 0.f;
};