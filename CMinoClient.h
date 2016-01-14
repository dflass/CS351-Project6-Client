using namespace System::Drawing;

//David Lass & Chris Ebright
//114976970 & 11414871
//CS351
//Dr Hong

//A class to define the mino
//The mino is a singular circle with position, color, and diameter.

public ref class CMino{  //defines CMino class
public:
	int X_position;
	int Y_position;
	Color Mino_color;
	int diameter;

	CMino(int x, int y, Color c){  //constructor
		X_position = x;
		Y_position = y;
		Mino_color = c;
		diameter = 25;
	}

	int getX() {return X_position;}
	int getY() {return Y_position;}
	void setX(int x) {X_position = x;}
	void setY(int y) {Y_position = y;}
	Color getC() {return Mino_color;}

	void draw (Graphics^ g){  //draws ellipse with boundry
		g->FillEllipse(gcnew SolidBrush(Mino_color), X_position, Y_position, diameter, diameter);
		g->DrawEllipse(gcnew Pen(Color::Black), X_position, Y_position, diameter, diameter);
	}

	bool containPoint(int x, int y){ //Function to determine if Mino contains a certain point.
		double a=diameter/2.0;
		double b=diameter/2.0;
		double xc=X_position+a;
		double yc=Y_position+b;
		return ((x-xc)*(x-xc)/(a*a)+(y-yc)*(y-yc)/(b*b)<=1.0);
		return false;
	}
		
};