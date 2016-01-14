using namespace System;
using namespace System::Collections;
using namespace System::Drawing;

//David Lass & Chris Ebright
//114976970 & 11414871
//CS351
//Dr Hong

//A function that defines an object known as the tetrimino.
//This object has a position, type, and arraylist of 4 Minos.

#include "CMinoClient.h"

public ref class CTetriMino{  //CTetriMino Class
public:
	int X_Tetri;
	int Y_Tetri;
	int type;
	ArrayList ^tetrigon;
	int offset;

	CTetriMino(int x, int y, int t){  //Constructor with inputs
		X_Tetri=x;
		Y_Tetri=y;
		type = t;
		int offset=25;
		tetrigon = gcnew ArrayList();
		switch (type){  //Adds Minos to tetri based on type
			case 0:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Yellow));
				break;
			case 1:
				tetrigon->Add(gcnew CMino(X_Tetri-2*offset, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri-offset, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri+offset, Y_Tetri, Color::Orange));
				break;
			case 2:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Blue));
				break;
			case 3:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri+offset, Color::Magenta));
				break;
			case 4:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Turquoise));
				break;
			case 5:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri+offset, Color::Green));
				break;
			case 6:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Red));
				break;
		}
	}

	CTetriMino(CTetriMino^ src) { //Copying constructor
		X_Tetri=src->X_Tetri;
		Y_Tetri=src->Y_Tetri;
		type = src->type;
		offset=25;
		tetrigon = gcnew ArrayList();
		switch (type){
			case 0:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Yellow));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Yellow));
				break;
			case 1:
				tetrigon->Add(gcnew CMino(X_Tetri-2*offset, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri-offset, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri, Y_Tetri, Color::Orange));
				tetrigon->Add(gcnew CMino(X_Tetri+offset, Y_Tetri, Color::Orange));
				break;
			case 2:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Blue));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Blue));
				break;
			case 3:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Magenta));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri+offset, Color::Magenta));
				break;
			case 4:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Turquoise));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Turquoise));
				break;
			case 5:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Green));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri+offset, Color::Green));
				break;
			case 6:
				tetrigon->Add(gcnew CMino((X_Tetri-offset), Y_Tetri+offset, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri+offset, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri), Y_Tetri, Color::Red));
				tetrigon->Add(gcnew CMino((X_Tetri+offset), Y_Tetri, Color::Red));
				break;
		}

	}

	int getX() {return X_Tetri;}
	int getY() {return Y_Tetri;}

	void setX(int x) {
		X_Tetri = x;
	}


	void setY(int y) {
		Y_Tetri = y;
	}


	int getTy() {return type;}

	ArrayList^ getT() {return tetrigon;}
	
	void draw(Graphics^ g) {  //Draw function, calls Mino draw function
		for(int i=0; i<4; i++){ 
				CMino^ p=(CMino^)tetrigon[i];
				p->draw(g);
		}
	}


	void rotate(int x, int y){  //Rotate function, based on rotate equation
		for(int i=0; i<4; i++){ 
				CMino^ p=(CMino^)tetrigon[i];
				int xcurrent= p->getX();
				int ycurrent = p->getY();
				p->setX(x-ycurrent+y);
				p->setY(y+xcurrent-x);
		}
	}

	void translate(int x, int y){  //Moving function
		for(int i=0;i<4;i++){
			CMino^ p = (CMino^)tetrigon[i];
			p->X_position+=x;
			p->Y_position+=y;
		}
	}

	bool containPoint(int x, int y){  //contain point, checks if any Mino contains a specific point.
		CMino^ p0=(CMino^)tetrigon[0];
		CMino^ p1=(CMino^)tetrigon[1];
		CMino^ p2=(CMino^)tetrigon[2];
		CMino^ p3=(CMino^)tetrigon[3];
		return(p0->containPoint(x, y) || p1->containPoint(x, y) || p2->containPoint(x, y) || p3->containPoint(x, y));
	}

};