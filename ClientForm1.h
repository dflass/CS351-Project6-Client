#pragma once

#include "CTetriMinoClient.h"

//David Lass & Chris Ebright
//114976970 & 11414871
//CS351
//Dr Hong

//A function to build 7 original 4 mino tetriminos. 
//The function duplicates and moves the duplicate tetrimino on left click
//The tetrimino rotates on right click and is deleted when dragged into the box at the bottom.


namespace Client6 {
	//imports namespaces from system
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::IO;


	public ref class Form1 : public System::Windows::Forms::Form
	//defines Form1 as a dependent class on Windows Forms
	{
	private:
		System::ComponentModel::Container ^components; //Required for system. Don't Delete
		ArrayList ^Originals; //ArrayList of Tetriminos Original and Duplicates
		ArrayList ^Duplicates;
		CTetriMino^ ShapeToBeMoved; //Defines ShapeToBeMoved as TetriMino
		int m_nOffsetX;	// difference between cursor and top-left corner
		int m_nOffsetY;
		Bitmap^ backBuffer; //Required for Drawing
		Graphics^ gBackBuffer;

		private: String ^serverHost; //string to hold IP

		private: NetworkStream ^clientStream; //stream over network
		private: BinaryWriter ^writer;
		private: BinaryReader ^reader;

		private: String ^message; //holds data

		private: Thread ^readThread;


	public:
		Form1(String^ host)
		{
			InitializeComponent();	//required function
			Duplicates = gcnew ArrayList();
			Originals = gcnew ArrayList(); //Initializes ArrayLists

			for (int i=0; i<7; i++) { 
				Originals->Add(gcnew CTetriMino(40+(i*100), 20, i));
			}
			ShapeToBeMoved=nullptr; 

			backBuffer = gcnew Bitmap(ClientSize.Width, ClientSize.Height); //Required for drawing
			gBackBuffer = Graphics::FromImage(backBuffer);
			this->SetStyle(ControlStyles::Opaque, true);
			serverHost=host;
			readThread = gcnew Thread( gcnew ThreadStart( this, &Form1::RunClient ) ); //thread for timing
			readThread->Start();
			
		}

	protected:
		~Form1() //Cleans up dont Delete
		{
			if (components)
			{
				delete components;
			}
		}

	

#pragma region Windows Form Designer generated code
		//Auto Generated
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(746, 421);
			this->Name = L"Form1";
			this->Text = L"Client";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				//Paint Events - Updates at beginning and whenever mouse drag
				gBackBuffer->Clear(Color::White);
				for (int i=0; i<Originals->Count; i++) {
					CTetriMino^ p=(CTetriMino^)Originals[i];	//Draws originals
					p->draw(gBackBuffer);
				}
				gBackBuffer->DrawLine(gcnew Pen(Color::Black,2.0f), Point(0,75), Point(ClientSize.Width, 75));	//draws line
				for (int i=0; i<Duplicates->Count; i++) {
					CTetriMino^ p=(CTetriMino^)Duplicates[i];	//draws duplicates
					p->draw(gBackBuffer);
				}
				gBackBuffer->DrawLine(gcnew Pen(Color::Black,2.0f), Point(0,(ClientSize.Height-(ClientSize.Height - 300))), Point(ClientSize.Width, (ClientSize.Height-(ClientSize.Height - 300))));	//draws line
				gBackBuffer->FillRectangle(gcnew SolidBrush(Color::Gray), 0, 300, ClientSize.Width, (ClientSize.Height-(ClientSize.Height - 300)));
				e->Graphics->DrawImageUnscaled(backBuffer, 0, 0);	//draws box at bottom 

				
			 }

	private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				if (e->Button == System::Windows::Forms::MouseButtons::Left) { //Left Click
					for (int i=Originals->Count-1; i>=0; i--) {
						CTetriMino^ p=(CTetriMino^)Originals[i];	
						if (p->containPoint(e->X, e->Y)) { //Checks if Original CTetriMino contains point
							CTetriMino^ p2=gcnew CTetriMino(p);		//makes copy of original
							Duplicates->Add(p2);	//adds TetriMino to Duplicates
							ShapeToBeMoved=p2;		//Makes that TetriMino shape to be moved
							m_nOffsetX=e->X;	
							m_nOffsetY=e->Y;
							try{writer->Write("MDL!" + Convert::ToString(e->X) + "!" +Convert::ToString(e->Y));}
							catch(Exception^) {}
							Invalidate();
							return;
						}
					}
					for (int i=Duplicates->Count-1; i>=0; i--) {
						CTetriMino^ p=(CTetriMino^)Duplicates[i];
						if (p->containPoint(e->X, e->Y)) {  //Checks if Duplicate CTetriMino contains point
							Duplicates->RemoveAt(i);	
							Duplicates->Add(p);		//Moves clicked Duplicate to top of Duplicate list
							ShapeToBeMoved=p;		//Sets Shape to be moved
							m_nOffsetX=e->X;
							m_nOffsetY=e->Y;
							try{writer->Write("MDL!" + Convert::ToString(e->X) + "!" +Convert::ToString(e->Y));}
							catch(Exception^) {}
							Invalidate();	
							Refresh();	//Reloads the screen
							return;
						}
					}
					
				}
				if (e->Button == System::Windows::Forms::MouseButtons::Right) { //programming rotate for right click
					int xrot;
					int yrot;	//initializes rotate varialbes
					for (int i=Duplicates->Count-1; i>=0; i--) {
						CTetriMino^ p=(CTetriMino^)Duplicates[i];
						if (p->containPoint(e->X, e->Y)) {  //Finds which tetrimino contains point
							for(int j=0; j<4;j++){
								CMino^q = (CMino^)p->tetrigon[j];
								if(q->containPoint(e->X, e->Y)){
									xrot = q->getX();	//sets rotate point to individual Mino location
									yrot = q->getY();
								}
							}
							try{writer->Write("MDR!" + Convert::ToString(e->X) + "!" +Convert::ToString(e->Y));}
							catch(Exception^){}
							p->rotate(xrot, yrot);	//Rotates shape
							Invalidate();
						}
					}
					

				}
			 }
	private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {  //moving tetri
				if (e->Button == System::Windows::Forms::MouseButtons::Left) {
					if (ShapeToBeMoved!=nullptr) {  //Checks that Tetrimino is clicked
						ShapeToBeMoved->translate( e->X - m_nOffsetX, e->Y-m_nOffsetY);  //moves tetrimino 
						m_nOffsetX=e->X;
						m_nOffsetY=e->Y;
						Invalidate();
					}
					try{writer->Write("MM!" + Convert::ToString(e->X) + "!" +Convert::ToString(e->Y));}
					catch(Exception^){}
				}
			 }
	private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {  //delete function
			for (int i=0; i<(Duplicates->Count); i++){
				CTetriMino^ p=(CTetriMino^)Duplicates[i];
				for(int j=0;j<4;j++){
					CMino^q = (CMino^)p->tetrigon[j];
					if((q->getY())>278){  //if y is below certain point, delete
						Duplicates->RemoveAt(i);
						break;
					}
				}
			}
			try{writer->Write("MU!" + Convert::ToString(e->X) + "!" +Convert::ToString(e->Y));}
			catch(Exception^){}
			ShapeToBeMoved=nullptr;// no shape selected
			Invalidate();
	}
	public:

      // allows a client to connect and displays the text it sends
      void RunClient()
      {
         TcpClient ^client;
		 
         // instantiate TcpClient for sending data to server
         try {
            
            // Step 1: create TcpClient and connect to server
            client = gcnew TcpClient();
            client->Connect( "130.160.6.51",  12345);
			System::Console::WriteLine("Connected");
            // Step 2: get NetworkStream associated with TcpClient
            clientStream = client->GetStream();

            // create objects for writing and reading across stream
            writer = gcnew BinaryWriter( clientStream );
            reader = gcnew BinaryReader( clientStream );

			while (true){
				  //TODO listen for input
				  String^ tmp = reader->ReadString();
				  array<String^>^ parts = tmp->Split('!', 3);
				  String^ type = parts[0];
				  String^ x_coord = parts[1];
				  String^ y_coord = parts[2];
				  handle(type, Convert::ToInt32(x_coord), Convert::ToInt32(y_coord));
				  //TODO handle input
			  }
           
            // loop until server signals termination
            do {

               // Step 3: processing phase
               try {

                  // read message from server
                  message = reader->ReadString();
                 
               } // end try

               // handle exception if error in reading server data
               catch ( Exception ^ ) {
                  System::Environment::Exit( 
                     System::Environment::ExitCode );
               } // end catch

            } while ( !message->Equals( L"CLIENT>>> TERMINATE" ) );

            //displayTextBox->Text = String::Concat( 
            //   displayTextBox->Text, 
            //   L"\r\nClosing connection->\r\n" );
           

            // Step 4: close connection
            writer->Close();
            reader->Close();
            clientStream->Close();
            client->Close();

            Application::Exit();
         } // end try

         // handle exception if error in establishing connection
         catch ( Exception ^error ) {
            MessageBox::Show( error->ToString() );

            Application::Exit();
         } // end catch
      } // end method RunClient

	  void handle(String^ data, int x, int y)
	  {
		  if(data=="MU"){
			  for (int i=0; i<(Duplicates->Count); i++){
				CTetriMino^ p=(CTetriMino^)Duplicates[i];
				for(int j=0;j<4;j++){
					CMino^q = (CMino^)p->tetrigon[j];
					if((q->getY())>278){  //if y is below certain point, delete
						Duplicates->RemoveAt(i);
						break;
					}
				}
			  }
			  ShapeToBeMoved=nullptr;// no shape selected
			  Invalidate();
		  }
		  else if(data=="MM"){
					if (ShapeToBeMoved!=nullptr) {  //Checks that Tetrimino is clicked
						ShapeToBeMoved->translate( x - m_nOffsetX, y-m_nOffsetY);  //moves tetrimino 
						m_nOffsetX=x;
						m_nOffsetY=y;
						Invalidate();
					}

			  Invalidate();
		  }
		  else if(data=="MDR"){
			  int xrot;
			  int yrot;	//initializes rotate varialbes
					for (int i=Duplicates->Count-1; i>=0; i--) {
						CTetriMino^ p=(CTetriMino^)Duplicates[i];
						if (p->containPoint(x, y)) {  //Finds which tetrimino contains point
							for(int j=0; j<4;j++){
								CMino^q = (CMino^)p->tetrigon[j];
								if(q->containPoint(x, y)){
									xrot = q->getX();	//sets rotate point to individual Mino location
									yrot = q->getY();
								}
							}
							p->rotate(xrot, yrot);	//Rotates shape
							Invalidate();
						}
					}
			  Invalidate();
		  }
		  else if(data=="MDL"){
				for (int i=Originals->Count-1; i>=0; i--) {
					CTetriMino^ p=(CTetriMino^)Originals[i];	
					if (p->containPoint(x, y)) { //Checks if Original CTetriMino contains point
							
							CTetriMino^ p2=gcnew CTetriMino(p);		//makes copy of original
							Duplicates->Add(p2);	//adds TetriMino to Duplicates
							ShapeToBeMoved=p2;		//Makes that TetriMino shape to be moved
							m_nOffsetX=x;	
							m_nOffsetY=y;
							Invalidate();
							return;
					}
				}
				for (int i=Duplicates->Count-1; i>=0; i--) {
						CTetriMino^ p=(CTetriMino^)Duplicates[i];
						if (p->containPoint(x, y)) {  //Checks if Duplicate CTetriMino contains point
							Duplicates->RemoveAt(i);	
							Duplicates->Add(p);		//Moves clicked Duplicate to top of Duplicate list
							ShapeToBeMoved=p;		//Sets Shape to be moved
							m_nOffsetX=x;
							m_nOffsetY=y;
							Invalidate();	
							Refresh();	//Reloads the screen
							return;
						}
					}

			  Invalidate();
		  }
		  else{
		  }

	  }


private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

