#pragma once
#include <queue>
#include <vector>
#include "raylib.h"

class InputSequence {
public:
	enum class KeyStatus { Pressed, Released };
	struct Input {
		KeyboardKey key;
		KeyStatus status;
		Input(KeyboardKey key, KeyStatus status) : key(key), status(status) {
		}
	};

	InputSequence(int maxElements);
	void add(KeyStatus status, KeyboardKey key);
	void clear();
	bool checkSequence(std::vector<Input>);
private:
	int maxElements;
	std::queue<Input> inputSequence;
};