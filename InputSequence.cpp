#pragma once
#include "raylib.h"
#include "InputSequence.h"

InputSequence::InputSequence(int maxElements) : maxElements(maxElements) {

}

void InputSequence::add(KeyStatus status, KeyboardKey key) {
	std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);
	this->inputSequence.push(Input(key, status, now));
	if (this->inputSequence.size() > this->maxElements) this->inputSequence.pop();
}

int InputSequence::size() {
	return this->inputSequence.size();
}

InputSequence::Input InputSequence::last() {
	return this->inputSequence.back();
}

void InputSequence::clear() {
	while (!this->inputSequence.empty())
		this->inputSequence.pop();
}

bool InputSequence::checkSequence(std::vector<Input> sequence, std::chrono::milliseconds ellapsedTime) {
	if (sequence.size() > this->inputSequence.size()) return false;
	
	std::queue<Input> temp = this->inputSequence;
	bool found = false;
	int index = 0;
	std::chrono::milliseconds firstKeyPressed = std::chrono::milliseconds::zero();


	while (!found && !temp.empty()) {
		Input inputToCheck = temp.front();
		temp.pop();
		if (sequence[index].key == inputToCheck.key && sequence[index].status == inputToCheck.status) {
			// Get the timestamp of the first sequence key pressed
			if (firstKeyPressed == std::chrono::milliseconds::zero()) {
				firstKeyPressed = inputToCheck.timestamp;
			}

			index++;
			if (index == sequence.size()) {
				// Check the time if needed, otherwise return true
				if (ellapsedTime != std::chrono::milliseconds::zero() && (inputToCheck.timestamp - firstKeyPressed) <= ellapsedTime) {
					found = true;
				}
				else if(ellapsedTime == std::chrono::milliseconds::zero()) {
					found = true;
				}
			}
		}
		else break;
	}

	return found;
}