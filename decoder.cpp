#include<bits/stdc++.h>
#include<inttypes.h>
#include<stdint.h>
#include<SDL2/SDL.h>

using namespace std;

unsigned int buffInt(unsigned char* buffer)
{
	return (buffer[3]<<24|buffer[2]<<16|buffer[1]<<8|buffer[0]);
}

int main(int argc, char* argv[])
{
	//cout<<argv[1];
	ifstream instream(argv[1], ios::in|ios::binary);
	instream.seekg(0, ios::end);
	int sz=instream.tellg();
	instream.seekg(0, ios::beg);
	SDL_Window* window=NULL;
	SDL_Surface* screenSurface=NULL;
	SDL_Renderer* renderer=NULL;
	SDL_Init(SDL_INIT_VIDEO);
	window=SDL_CreateWindow("BMP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);
	screenSurface=SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0XFF));
	SDL_UpdateWindowSurface(window);
	//SDL_Delay(2000);
	renderer=SDL_CreateRenderer(window, -1,0);


   Uint8* fileContents=new Uint8[sz];

    for(int i=0; i<sz; i++)
    {
    	instream.read((char*)&fileContents[i], 1);
    }

    //why whole block doesn't work

	//instream.read((char*)fileContents, sizeof(fileContents));

	cout<<fileContents[0]<<fileContents[1]<<endl;
	fileContents+=10;
	//cout<<fileContents[2];

	// for(int i=0; i<sz; i++)
	// {
	// 	cout<<fileContents[i];
	// }

	//cout<<sz;
//	uint32_t address_offset;
	unsigned int address_offset;
	//sscanf((char*)fileContents, SCNu32, &address_offset);
	//cout<<(int)(fileContents[0]<<24|fileContents[1]<<16|fileContents[2]<<8|fileContents[3]);
	//sscanf((char*)fileContents, "%d", &address_offset);
	//cout<<(int)(fileContents[3]<<24| fileContents[2]<<16| fileContents[1]<<8| fileContents[0]);
	//cout<<fileContents[1];
	address_offset=buffInt(fileContents);
	//cout<<address_offset;
	

	unsigned width=buffInt(&fileContents[8]); 
	//hardcoded, will replace later
	unsigned height=buffInt(&fileContents[12]);
	// width=320;
	// height=240;
	unsigned int bitsPerPixel=24;
	unsigned rowSize=floor(((bitsPerPixel*width+31))/32)*4; //inbytes
	unsigned pixelArraySize=rowSize*abs(height);//in bytes
	unsigned colSize=pixelArraySize/rowSize;
	fileContents+=(address_offset-10);

//add support for other headers
	//cout<<fileContents[0];


	//SDL_RenderClear(renderer);
	int pixel=0;

	for(int i=0; i<colSize; i++)
	{
		pixel=0;
		for(int j=0; j<(rowSize-3); j+=3)
		{
			int index=(i*rowSize+j);

			int r, g, b;
			b=fileContents[index];
			g=fileContents[index+1];
			r=fileContents[index+2];

			if(pixel<width)
			{
			//SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer,r, g, b, 255);
			SDL_RenderDrawPoint(renderer,pixel,240-i);
//			SDL_Delay(1);
		//	cout<<i<<" "<<pixel<<" "<<(int)r<<" "<<g<<" "<<b<<" "<<endl;
			pixel++;
		}

		}
	}

	SDL_Event e;
	bool quit=false;
	SDL_RenderPresent(renderer);

	while(!quit)
	{
	
	while(SDL_PollEvent(&e)!=0)
	{
		if(e.type==SDL_QUIT)
		{
			quit=true;
		}
	}
	}

}