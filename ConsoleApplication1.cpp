#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int PALLETE_LENGTH = 1000;
int PALLETE_WIDTH = 1000;

struct Point {
	int x;
	int y;

	Point() {
		x = 0;
		y = 0;
	}
	Point(int a, int b) {
		x = a;
		y = b;
	}
};

struct Box {
	Point point;
	int length;
	int width;
	int id;
	bool used;
	int amount; // nr of boxes left to pack

	Box(int x, int y, int len, int wid, bool id_) {
		point = Point(x, y);
		length = len;
		width = wid;
		used = true;
		id = id_;
		amount = 1;
	}
};

struct Pallete {
	std::vector<Box> boxes;
	std::vector<Point> cornerPoints;

	Pallete() {}
};

void printBox(Box box) {
	std::cout << "Box nr: " << box.id << std::endl;
	std::cout << "Length: " << box.length << " & Width: " << box.width << std::endl;
	if (box.used) {
		std::cout << "Box placed at: " << box.point.x << " " << box.point.y << std::endl;
	}
	else {
		std::cout << "Box not placed yet" << std::endl;
	}
}

void readFile(Box* boxes, std::string fileName) {};

bool compareCP(Point a, Point b) {
	return a.x < b.x;
}

void updateCornerPoints(std::vector<Point> currentCP, Box box) {
	//
}

void insertBoxIntoCornerPoint(Pallete pallete, int pointId, Box box) {
	pallete.boxes.push_back(box);
	Point currentCP = pallete.cornerPoints[pointId];
	pallete.cornerPoints.erase(pallete.cornerPoints.begin() + pointId);
	// TODO: edit corner points
	if (pallete.cornerPoints.size()) {
		updateCornerPoints(pallete.cornerPoints, box);
	}
	else {
		pallete.cornerPoints.push_back(Point(0, box.length));
		pallete.cornerPoints.push_back(Point(box.width, 0));
	}
	std::sort(pallete.cornerPoints.begin(), pallete.cornerPoints.end(), compareCP);
}

void findNextBoxAndCornerPoint(Pallete pallete, std::vector<Box> boxes) {
	int bestValue = -1;
	for (int i = 0; i < pallete.cornerPoints.size(); i++) {
		for (int j = 0; j < boxes.size(); j++) {
			Pallete temp = pallete;
			Box tempBox = boxes[j];
			if (temp.cornerPoints[i].x + boxes[j].length > PALLETE_LENGTH ||
				temp.cornerPoints[i].y + boxes[j].width > PALLETE_WIDTH) {
				// cannot insert this box into this CP
				continue;
			}
			tempBox.point.x = temp.cornerPoints[i].x;
			tempBox.point.y = temp.cornerPoints[i].y;
			insertBoxIntoCornerPoint(temp, j, tempBox);
		}
	}
}

std::vector<Box> solveTask(std::vector<Box> boxes) {
	std::vector<Box> result;
	Pallete pallete;

	// only for dev purposes
	for (auto& box : boxes) {
		printBox(box);
	}
	std::vector<Point> cornerPoints;
	cornerPoints.push_back(Point());
	pallete.cornerPoints = cornerPoints;

	while (boxes.size()) {
		findNextBoxAndCornerPoint(pallete, boxes);

	}

	return boxes;
}

int main() {
	std::cout << "Hello World!\n";
	std::vector<Box> boxes;
	for (int i = 0; i < 5; i++) {
		Box box = Box(0, 0, i, i, i);
		box.length = i;
		box.width = i;
		box.id = i;
		box.used = false;
		box.amount = i;
		boxes.push_back(box);
	}
	std::vector<Box> result = solveTask(boxes);
	return 0;
}

