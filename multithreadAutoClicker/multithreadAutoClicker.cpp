#include <Windows.h>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

using namespace std;

atomic<bool> running(true);
const int Latency = 10;
const int num_of_threads = 50;


void Click() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void ThreadLoop() {
	while (running)
	{
		Click();
		if (Latency != 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(Latency));
		}
	}
}

int main() {
	std::vector<thread> threads;
	std::cout << "F9 - start; F10 - stop" << std::endl;
	while (true)
	{
		if (GetAsyncKeyState(VK_F9) & 0x8000)
		{
			running = true;
			for (int i = 0; i < num_of_threads; i++)
			{
				threads.emplace_back(ThreadLoop);
			}
		}
		if (GetAsyncKeyState(VK_F10) & 0x8000)
		{
			running = false;
			for (auto& t : threads) {
				if (t.joinable())
				{
					t.join();
				}
			}
			threads.clear();
		}
	}
}