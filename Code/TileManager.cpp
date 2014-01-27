#include "TileManager.h"
#include "freeimage.h"
#include "TriggerManager.h"

TileManager::TileManager(void)
{
	m_pTileSurfaces.reserve(2048);
}

TileManager::~TileManager(void)
{
	instanceFlag = false;
	delete m_pBaseSprite;
}

bool TileManager::instanceFlag = false;
TileManager* TileManager::single = NULL;
TileManager* TileManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new TileManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void TileManager::LoadBaseSprite(char* a_sPath)
{
	m_pBaseSprite = new Tmpl8::Surface(a_sPath);
}


void TileManager::ProcessTileMap()
{
	int rows = m_pBaseSprite->GetHeight() / TILE_HEIGHT;
	int columns = m_pBaseSprite->GetWidth() / TILE_WIDTH;
	int idCounter = 0;
	
	int id = 0;

	int counter = 0;
	
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < columns; col++)
		{
			Tmpl8::Surface* surface = new Tmpl8::Surface(TILE_WIDTH, TILE_HEIGHT);
			m_pBaseSprite->CopyPartTo(surface, 0, 0, col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

			if(row == 0 && col == 0)
			{
				TileNode* tileNode = new TileNode(row, col, 0);
				m_pTiles[0] = tileNode;
				m_pTileSurfaces.push_back(new TileSurface(idCounter,surface));
				tileNode->SetSurface(tileNode->m_iTileId);
				counter++;
				idCounter++;
				continue;
			}
			bool isUnique = true;
			for(std::vector<TileSurface*>::iterator iter = m_pTileSurfaces.begin(); iter != m_pTileSurfaces.end();)
			{
				if(!(*iter)->CompareSurfaces(surface))
				{
					isUnique = false;
					id = (*iter)->m_iTileId;
					iter = m_pTileSurfaces.end();
				}
				else
				{
					iter++;
				}
			}

			if(isUnique)
			{
				m_pTileSurfaces.push_back(new TileSurface(idCounter,surface));
				id = idCounter;
				idCounter++;
			}
			else
			{
				delete surface;
			}
			TileNode* tileNode = new TileNode(row, col, id);
			m_pTiles[counter] = tileNode;
			tileNode->SetSurface(tileNode->m_iTileId);
			counter++;
		}
	}
	FIBITMAP* bitmap = FreeImage_Allocate(512, 1024, 24);
	int tilesInRow = 512 / TILE_WIDTH;
	int rowCounter = 0;
	int colCounter = 0;
	for(std::vector<TileSurface*>::iterator iter = m_pTileSurfaces.begin(); iter != m_pTileSurfaces.end(); iter++)
	{
		Tmpl8::Pixel* buffer = (*iter)->m_pTileSurface->GetBuffer();
		int pitch = (*iter)->m_pTileSurface->GetPitch();

		for(int x = 0; x < TILE_WIDTH; x++)
		{
			for(int y = 0; y < TILE_HEIGHT; y++)
			{
				RGBQUAD color;
				color.rgbRed = (buffer[x + y*pitch] & 0xFF0000) >> 16;
				color.rgbGreen = (buffer[x + y*pitch] & 0x00FF00) >> 8;
				color.rgbBlue = buffer[x + y*pitch] & 0x0000FF;
				FreeImage_SetPixelColor(bitmap, colCounter*TILE_WIDTH + x, 1023 - rowCounter*TILE_HEIGHT - y, &color);
			}
		}
		colCounter++;
		if(colCounter >= tilesInRow)
		{
			colCounter = 0;
			rowCounter++;
		}
	}
	FreeImage_Save(FIF_PNG, bitmap, "assets/tilesets/tileset.png", 0);
	delete m_pBaseSprite;

	std::string tileMap;
	std::stringstream ss;
			
	counter = 0;
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; col < columns; col++)
		{
			TileNode* currentNode = m_pTiles[counter];
			counter++;

			ss.str("");
			ss << currentNode->m_iTileId;
			tileMap += ss.str();

			if(col+1 != columns)
				tileMap += ",";
		}
		
		if(row+1 != rows)
			tileMap += "\n";
	}
	std::ofstream tilemapFile;
	tilemapFile.open ("assets/tilesets/tilemap.dat");
	tilemapFile << tileMap;
	tilemapFile.close();
	std::ofstream metaFile;
	metaFile.open ("assets/tilesets/metadata.dat");
	ss.str("");
	ss << m_pTileSurfaces.size() << "," << TILE_WIDTH << "," << TILE_HEIGHT << "," << 512 << "," << 1024;
	metaFile << ss.str();
	metaFile.close();
}

float transitionTimer = 0;
void TileManager::Update(float a_fDeltaTime)
{
	if(m_pWorld->m_state == IN_TRANSITION)
	{
		transitionTimer += a_fDeltaTime * SCROLL_SPEED;
	}
}


void TileManager::Draw(Tmpl8::Surface* a_screen)
{
	if(m_pWorld->m_state == IN_TRANSITION)
	{
		if(m_pWorld->m_iCurrentRoom + 1 == m_pWorld->m_iNextRoom) //Next screen is below current screen
		{
			m_pCurrentRoom->Draw(a_screen, Vector2(0,0 - transitionTimer * ROOM_HEIGHT));
			m_rooms[m_pWorld->m_iNextRoom]->Draw(a_screen, Vector2(0, ROOM_HEIGHT - transitionTimer * ROOM_HEIGHT));
		}
		else if(m_pWorld->m_iCurrentRoom - 1 == m_pWorld->m_iNextRoom) //Next screen is above current screen
		{
			m_pCurrentRoom->Draw(a_screen, Vector2(0,transitionTimer * ROOM_HEIGHT));
			m_rooms[m_pWorld->m_iNextRoom]->Draw(a_screen, Vector2(0, -ROOM_HEIGHT + transitionTimer * ROOM_HEIGHT));
		}
		else if(m_pWorld->m_iNextRoom > m_pWorld->m_iCurrentRoom) //Next screen is to the right of current screen
		{
			m_pCurrentRoom->Draw(a_screen, Vector2(0 - transitionTimer * ROOM_HEIGHT,0));
			m_rooms[m_pWorld->m_iNextRoom]->Draw(a_screen, Vector2(ROOM_HEIGHT - transitionTimer * ROOM_HEIGHT, 0));
		}
		else if(m_pWorld->m_iNextRoom < m_pWorld->m_iCurrentRoom) //Next screen is to the left of current screen
		{
			m_pCurrentRoom->Draw(a_screen, Vector2(transitionTimer * ROOM_WIDTH, 0));
			m_rooms[m_pWorld->m_iNextRoom]->Draw(a_screen, Vector2(-ROOM_WIDTH + transitionTimer * ROOM_WIDTH, 0));
		}

		if(transitionTimer > 1)
		{
			m_pWorld->SetState(NORMAL);
			transitionTimer = 0;
		}
	}
	else
	{
		m_pCurrentRoom->Draw(a_screen);
	}
	//m_rooms[0]->Draw(a_screen, Vector2(0, 0));s
	/*for(std::vector<TileSurface*>::iterator iter = m_pTileSurfaces.begin(); iter != m_pTileSurfaces.end(); iter++)
	{
		(*iter)->m_pTileSurface->CopyTo(a_screen, TILE_WIDTH * (counter % (SCRWIDTH/TILE_WIDTH)),counter / (SCRWIDTH/TILE_WIDTH) * TILE_HEIGHT);
		counter++;
	}*/
}


TileSurface* TileManager::GetTileSurface(int id)
{
	return m_pTileSurfaces[id];
}

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

void TileManager::LoadExistingMap()
{
	std::ifstream ifile("assets/tilesets/metadata.dat");
	std::string metadataRaw;
	std::vector<std::string> metadata;
	
	if (ifile) {
		getline (ifile,metadataRaw);
		ifile.close();
	}
	metadata = explode(metadataRaw, ',');

	LoadTileSurfaces(atoi(metadata[1].c_str()), atoi(metadata[2].c_str()), atoi(metadata[3].c_str()), atoi(metadata[4].c_str()), atoi(metadata[0].c_str()));
	ComposeMap();
}

void TileManager::LoadTileSurfaces(int a_tileWidth, int a_tileHeight, int a_width, int a_height, int a_amountOfTiles)
{
	int counter = 0;
	Tmpl8::Surface* tileset = new Tmpl8::Surface("assets/tilesets/tileset.png");
	Tmpl8::Surface* collisionMap = new Tmpl8::Surface("assets/tilesets/tileset_collision.png");
	Tmpl8::Pixel* collisionBuffer = collisionMap->GetBuffer();
	
	for(int y = 0; y < a_height / a_tileHeight; y++)
	{
		for(int x = 0; x < a_width / a_tileWidth; x++)
		{
			Tmpl8::Surface* tile = new Tmpl8::Surface(a_tileWidth, a_tileHeight);
			tileset->CopyPartTo(tile, 0,0,x * a_tileWidth,
								y * a_tileHeight, 
								a_tileWidth, 
								a_tileHeight);
			TileSurface* tSurface = new TileSurface(counter, tile);
			m_pTileSurfaces.push_back(tSurface);
			switch(collisionBuffer[x + y*a_width/a_tileWidth])
			{
			case 0xFF000000:						//Black
				tSurface->m_collisionType = NONE;
				break;
			case 0xFFFFFFFF:						//White
				tSurface->m_collisionType = FULL;
				break;
			case 0xFF00FFFF:						//Cyan
				tSurface->m_collisionType = BOOMERANGABLE;
				break;
			case 0xFFFF0000:						//Red
				tSurface->m_collisionType = HALF_LEFT;
				break;
			case 0xFF00FF00:						//Green
				tSurface->m_collisionType = HALF_RIGHT;
				break;
			case 0xFF0000FF:						//Blue
				tSurface->m_collisionType = HALF_TOP;
				break;
			case 0xFFFFFF00:						//Yellow
				tSurface->m_collisionType = HALF_BOTTOM;
				break;
			default:
				tSurface->m_collisionType = NONE;
				break;
			}
			
			counter++;
			if(counter == a_amountOfTiles)
			{
				return;
			}
		}
	}
	delete tileset;
}


void TileManager::ComposeMap()
{
	std::ifstream ifile("assets/tilesets/tilemap.dat");
	std::vector<std::string> tileMapRaw;
	
	if (ifile) {
		std::string temp = "";
		while(getline(ifile,temp)){
			tileMapRaw.push_back(temp);
			std::string temp = "";
		}
		ifile.close();
	}

	int xCounter = 0;
	int yCounter = 0;
	
	int idMap[MAP_WIDTH / TILE_WIDTH][MAP_HEIGHT / TILE_HEIGHT];

	for(std::vector<std::string>::iterator iter = tileMapRaw.begin(); iter != tileMapRaw.end(); iter++)
	{
		std::vector<std::string> tileIds = explode(*iter, ',');
		for(std::vector<std::string>::iterator tileIter = tileIds.begin(); tileIter != tileIds.end(); tileIter++)
		{
			idMap[xCounter][yCounter] = std::atoi(tileIter->c_str());
			xCounter++;
		}
		xCounter = 0;
		yCounter++;
	}

	for(int roomX = 0; roomX < COLS_OF_ROOMS; roomX++)
	{
		for(int roomY = 0; roomY < ROWS_OF_ROOMS; roomY++)
		{
			m_rooms[roomY + roomX * ROWS_OF_ROOMS] = new Room(Vector2i(roomX,roomY), idMap);
			Entities->AddEntityVectorForRoom(m_rooms[roomY + roomX * ROWS_OF_ROOMS]);
		}
	}
}


void TileManager::SetRoom(int a_iIndex)
{
	m_pCurrentRoom = m_rooms[a_iIndex];
	m_pWorld->m_iCurrentRoom = a_iIndex;
	Entities->SetCurrentRoom(m_pCurrentRoom);
	Triggers->m_pCurrentRoom = m_pCurrentRoom;
}
