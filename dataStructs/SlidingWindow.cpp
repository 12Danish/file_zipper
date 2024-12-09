#include "SlidingWindow.h"


	slidingWindow::slidingWindow(size_t maxSize):size(maxSize),start(0),currentSize(0) {
		buffer.resize(size);
	}

	void slidingWindow::add(char c) {
		if (currentSize < size) {
			buffer[currentSize++] = c;
		}
		else {
			buffer[start] = c;
			start = (start + 1) % size;
		}
	}

	char slidingWindow::get(size_t pos) const {
		if (pos >= currentSize) throw out_of_range("Position out of range");
		return buffer[(start + pos)% size];
	}

	size_t slidingWindow::getCurrentSize() const {
		return currentSize;
	}

	void slidingWindow::printWindow() const {
		for (size_t i = 0; i < currentSize; ++i) {
			cout << get(i);
		}
		cout << endl;
	}