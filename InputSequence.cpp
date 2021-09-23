#pragma once
#include "raylib.h"
#include "InputSequence.h"

InputSequence::InputSequence(int maxElements) : maxElements(maxElements) {

}

void InputSequence::add(KeyStatus status, KeyboardKey key) {
	this->inputSequence.push(Input(key, status));
	if (this->inputSequence.size() > this->maxElements) this->inputSequence.pop();
}

void InputSequence::clear() {
	while (!this->inputSequence.empty())
		this->inputSequence.pop();
}

bool InputSequence::checkSequence(std::vector<Input> sequence) {
	if (sequence.size() > this->inputSequence.size()) return false;
	
	std::queue<Input> temp = this->inputSequence;
	bool found = false;
	int index = 0;
	while (!found && !temp.empty()) {
		Input inputToCheck = temp.front();
		temp.pop();
		if (sequence[index].key == inputToCheck.key && sequence[index].status == inputToCheck.status) {
			index++;
			if (index == sequence.size()) found = true;
		}
		else break;
	}

	return found;
}