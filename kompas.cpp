#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <time.h> 
LPSTR NazwaKlasy = "Klasa Okienna";
std::vector<double> roll, pitch, yaw;
int ile2;
double x = 1;
double y = 3;

MSG Komunikat;

#define idTimer 10
#define time_stamp 10
#define idTimer54 10

HWND hile;

int convertToInt(char a[3]){
    int i = 0;
    int num = 0;
    while (a[i] != 0)
    {
        num =  (a[i] - '0')  + (num * 10);
        i++;
    }
    return num;}
    
char ile[3];
    

void readRollAndPitchAndYaw(std::vector<double> &a, std::vector<double> &b, std::vector<double> &c)
{
    std::fstream myFile;
    myFile.open("outputCatapult01.log");
    if (!myFile)
    {
        throw "Could not open file";
    }
    std::string line;
    double rollValue, pitchValue, yawValue;
    while (std::getline(myFile, line))
    {
        myFile>>rollValue>>pitchValue>>yawValue;
        a.push_back(rollValue);
        b.push_back(pitchValue);
        c.push_back(yawValue);
    }
}

double  calc_angle(float px,int py)
{
	float angle;
	angle = atan2(-px, py);
	return angle;
}

LRESULT CALLBACK OkiennaProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );


//TWORZENIE PRZYCISKU
    HWND h54Przycisk;
    HWND h11Przycisk;
    HWND h12Przycisk;
    HWND h22Przycisk;
    HWND h21Przycisk;
  
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
   
    // WYPE£NIANIE STRUKTURY
    WNDCLASSEX okno;
   
    okno.cbSize = sizeof( WNDCLASSEX );
    okno.style = 0;
    okno.lpfnWndProc = OkiennaProc;
    okno.cbClsExtra = 0;
    okno.cbWndExtra = 0;
    okno.hInstance = hInstance;
    okno.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    okno.hCursor = LoadCursor( NULL, IDC_ARROW );
    okno.hbrBackground =( HBRUSH )( COLOR_WINDOW + 2 );
    okno.lpszMenuName = NULL;
    okno.lpszClassName = NazwaKlasy;
    okno.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
   
    	
    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & okno ) )
    {
        MessageBox( NULL, "B³¹d!", "Niestety...",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }
   
    // TWORZENIE OKNA
    HWND hwnd;   
   
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "Kompas", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, 820, 700, NULL, NULL, hInstance, NULL );
   
      
 	//TWORZENIE MIEJSCA DO TEKSTU STATYCZNEGO 
	HWND h5Static = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
	SS_CENTER , 50, 500, 300, 20, hwnd, NULL, hInstance, NULL );
	//WPISYWANIE TEKSTU
	SetWindowText( h5Static, "Ile pierwszych linijek nie wczytywac?" );
	
		hile =  CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE |
	SS_CENTER , 50, 550, 100, 30, hwnd, NULL, hInstance, NULL);  

	//WYŒWIETLANIE PRZYCISKÓW
  	h54Przycisk = CreateWindowEx( 0, "BUTTON", "WYGENERUJ", WS_CHILD | WS_VISIBLE,
		250, 550, 100, 30, hwnd, NULL, hInstance, NULL );
	
	h11Przycisk = CreateWindowEx( 0, "BUTTON", "+", WS_CHILD | WS_VISIBLE,
		30, 37, 50, 30, hwnd, NULL, hInstance, NULL );
		
	h12Przycisk = CreateWindowEx( 0, "BUTTON", "-", WS_CHILD | WS_VISIBLE,
		30, 70, 50, 30, hwnd, NULL, hInstance, NULL );
	
	h22Przycisk = CreateWindowEx( 0, "BUTTON", "-", WS_CHILD | WS_VISIBLE,
		30, 300, 50, 30, hwnd, NULL, hInstance, NULL );
		
	h21Przycisk = CreateWindowEx( 0, "BUTTON", "+", WS_CHILD | WS_VISIBLE,
		80, 300, 50, 30, hwnd, NULL, hInstance, NULL );	


    if( hwnd == NULL )
    {
        MessageBox( NULL, "B³¹d w generowaniu okna", "No có¿...", MB_ICONEXCLAMATION );
        return 1;
    }
   
    ShowWindow( hwnd, nCmdShow ); // Poka¿ okienko...
    UpdateWindow( hwnd );
   
    // Pêtla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

void rysowanie(double xx, double yy, HDC hdc,  int ile2  )
{
	       for(int a = 0; a<625-ile2; a++)
	   {
	   
        	MoveToEx(hdc,a*xx+32,200+ yy* pitch[a],0); 
			LineTo(hdc,(xx*(a+1)+32),200+yy* pitch[a+1]);
    	}
          for(int a = 0; a<625-ile2; a++)
	   {
        	MoveToEx(hdc,a*xx+32,200+ yy*( roll[a]),0); 
			LineTo(hdc,(xx*(a+1)+32),200+yy*( roll[a+1]));	
		}
}
void rysowanie2(double xx, double yy, HDC hdc,  int ile2, int a  )
{	
	HPEN PenBlue, PenGrey, PenBlack, PenNice;
    PenBlue = CreatePen( PS_SOLID, 2, 0xFF8000 );
    PenGrey = CreatePen( PS_SOLID, 2, 0x606060 );
    PenBlack = CreatePen( PS_SOLID, 2, 0x00000 );
    PenNice = CreatePen( PS_SOLID, 7, 0x654321 );
    HPEN hPenOld;
	HPEN hEllipsePen;
	COLORREF qEllipseColor;
	qEllipseColor = RGB(128,0,128);
	hEllipsePen = CreatePen (PS_SOLID, 5 , qEllipseColor);
	hPenOld = (HPEN) SelectObject (hdc,hEllipsePen);
    
	    for(int i = 0; i < 625 - ile2; i++)
		{
		  if(i<a)
		  {
		  	SelectObject( hdc, PenBlue );
		  }
		  else SelectObject( hdc, PenGrey );
		  
        	MoveToEx(hdc,i*xx+32,200+ yy*pitch[i],0); 
			LineTo(hdc,(xx*(i+1)+32),200+yy* pitch[i+1]);
    	
        
        	MoveToEx(hdc,i*xx+32,200+ yy*( roll[i]),0); 
			LineTo(hdc,(xx*(i+1)+32),200+yy*( roll[i+1]));	
			
			SelectObject( hdc, PenBlack );
				MoveToEx(hdc,0,200,0); 
			LineTo(hdc,800,200);
			SelectObject( hdc, PenNice );
        Arc(hdc, 590, 300,790, 500, 0, 0,0,0 );
		}
}

void rysowanie_wskazowki(HDC hdc, int ile2, int a)
{	
	
	MoveToEx(hdc,690,400,0); 
	LineTo(hdc, 690 + 90*sin(calc_angle(pitch[a], roll[a])),400-90*cos(calc_angle(pitch[a], roll[a]))); 
}

void CALLBACK timer(HWND hwnd, UINT message, UINT timer_id, DWORD dwTime){
	
		HDC hdcWin = GetDC(hwnd);

	    PAINTSTRUCT ps;
		
	    static int a = 0;
		static int b = 1;	
		HPEN PenBlue, PenGrey;
    PenBlue = CreatePen( PS_SOLID, 2, 0xFF8000 );
    PenGrey = CreatePen( PS_SOLID, 2, 0x606060 );
	
		HBRUSH hGrey = CreateSolidBrush(RGB(100,100,100));
		
		HDC hdc;
		hdc = GetDC(hwnd);           
		
    switch(timer_id){
        case (idTimer54):
        	
        	a++;     	
        	b++;
    	        	
        	SelectObject( hdc, PenBlue );
		  	rysowanie2( x, y, hdc,  ile2, a );       
        	
        	SelectObject( hdc, PenGrey );
        	rysowanie_wskazowki(hdc, ile2, a);
        	
        	SelectObject( hdc, PenBlue );
        		rysowanie_wskazowki(hdc, ile2, b);
        	
			if(a>625-ile2)
			{
			  KillTimer(hwnd, idTimer54);
			  SelectObject( hdc, PenGrey );
			  rysowanie_wskazowki(hdc, ile2, a);}	 				    		        		
				  
	                  break;
    }
}
// OBS£UGA ZDARZEÑ
LRESULT CALLBACK OkiennaProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
	HDC hdcWin = GetDC(hwnd);
    PAINTSTRUCT ps;
  
  HPEN PenRed, PenGrey, PenBlack, PenNice;
    PenRed = CreatePen( PS_SOLID, 1, 0x0000FF );
    PenGrey = CreatePen( PS_SOLID, 2, 0x646464 );
    PenBlack = CreatePen( PS_SOLID, 1, 0x000000 );
    PenNice = CreatePen( PS_SOLID, 7, 0x654321 );
    
		hdc = GetDC(hwnd);
		
	HPEN hPenOld;
	HPEN hEllipsePen;
	COLORREF qEllipseColor;
	qEllipseColor = RGB(128,0,128);
	hEllipsePen = CreatePen (PS_SOLID, 5 , qEllipseColor);
	hPenOld = (HPEN) SelectObject (hdc,hEllipsePen);
	
	
	   
    switch( msg )
    {
        
	case WM_COMMAND:
		
			 
    	if(( HWND ) lParam == h54Przycisk )
    	{  	
		
    		
	   		readRollAndPitchAndYaw(roll,pitch,yaw); 
			GetWindowText(hile, ile, 625);  
				ile2= convertToInt(ile);
														  								 
			pitch.erase(pitch.begin(), pitch.begin()+ile2 );  	
   			roll.erase(roll.begin(), roll.begin() +ile2 );
   			
		SetTimer(hwnd, idTimer54, time_stamp , (TIMERPROC) timer);
    	}
    
    
    	if(( HWND ) lParam == h11Przycisk )
    {
    	
    	SelectObject( hdc, PenGrey );		    	
    	rysowanie( x, y, hdc,  ile2 );
    	y = 2*y;
    	SelectObject( hdc, PenBlack );
    
		
		SetTimer(hwnd, idTimer54, time_stamp , (TIMERPROC) timer);
		
			
    }
	
	if(( HWND ) lParam == h12Przycisk )
	{
		SelectObject( hdc, PenGrey );		    	
    	rysowanie( x, y, hdc,  ile2 );
    	y = y/2;
    	SelectObject( hdc, PenBlack );
    	
		SetTimer(hwnd, idTimer54, time_stamp , (TIMERPROC) timer);
		
		
}
	if(( HWND ) lParam == h22Przycisk )
	{
		SelectObject( hdc, PenGrey );		    	
    	rysowanie( x, y, hdc,  ile2);
    	x = x/2;
    	SelectObject( hdc, PenBlack );
    	
		SetTimer(hwnd, idTimer54, time_stamp , (TIMERPROC) timer);
	
	}
	if(( HWND ) lParam == h21Przycisk )
	{
		SelectObject( hdc, PenGrey );		    	
    	rysowanie( x, y, hdc,  ile2 );
    	x = x*2;
    	
    	SelectObject( hdc, PenBlack );
			SetTimer(hwnd, idTimer54, time_stamp , (TIMERPROC) timer);
		}
   	
    break;
    
    	case WM_TIMER:


		break; 
     case WM_PAINT:
     	 hdc = BeginPaint(hwnd,&ps);
     	 	SelectObject( hdc, PenNice );
         Arc(hdc, 590, 300,790, 500, 0, 0,0,0 );
               
        SelectObject( hdc, PenBlack );
			MoveToEx(hdc,30,100,0); //przeniesienie pozycji pióra na punkt (50,50)
			LineTo(hdc,30,300); //narysowanie linni do wspó³rzêdnej (100,100)
			//w efekcie wywo³añ tych funkcji, narysujemy liniê od punktu (50,50) do punktu (100,100)
			
			MoveToEx(hdc,0,200,0); 
			LineTo(hdc,800,200); 
			
      EndPaint(hwnd, &ps);
      break;	
    	
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
       
    case WM_DESTROY:
        PostQuitMessage( 0 );
       
        break;
        		       
        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }
   
    return 0;
}
    

