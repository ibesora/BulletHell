#pragma once
#include <queue>
#include <vector>
#include <chrono>
#include "raylib.h"

class InputSequence {
public:
	enum class KeyStatus { Pressed, Released };
	struct Input {
		KeyboardKey key;
		KeyStatus status;
		std::chrono::milliseconds timestamp;
		Input(KeyboardKey key, KeyStatus status, std::chrono::milliseconds timestamp = std::chrono::milliseconds::zero()) : key(key), status(status), timestamp(timestamp) {
		}
	};

	InputSequence(int maxElements);
	void add(KeyStatus status, KeyboardKey key);
	int size();
	Input last();
	void clear();
	bool checkSequence(std::vector<Input>, std::chrono::milliseconds elapsedTime = std::chrono::milliseconds::zero());
private:
	int maxElements;
	std::queue<Input> inputSequence;
};