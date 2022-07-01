#pragma once
#include <thread>
#include <atomic>

class Gui {
	public:
		Gui() = default;
		~Gui() = default;

		void runGui();
};
