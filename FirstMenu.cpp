#include "FirstMenu.h"

void DrawMainFrame() {
	fullScreen(); //cua so console toan man hinh
	RemoveScroll(); //bo thanh keo tren console
	system("color f0"); // dat nen man hinh mau trang
	//SetBGColor(White);
	//SetColor(Red);
	DrawBorder(START_X_OF_MAIN_FRAME, START_Y_OF_MAIN_FRAME, MAX_X_OF_MAIN_FRAME, MAX_Y_OF_MAIN_FRAME);
}

void MainFirstMenu() {
	DrawMainFrame();
}
